#include "textureatlas.h"

#include <iostream>

namespace mw {

	void TextureAtlas::uploadSdlSurfaceToTexture(SDL_Surface* image, SDL_Rect dstRec, Texture& texture) {
		// In computer memory?
		if (texture.imageData_->texture_ == 0) {
			image = SDL_ConvertSurface(image, texture.imageData_->preLoadSurface_->format, 0);
			SDL_BlitSurface(image, 0, texture.imageData_->preLoadSurface_, &dstRec);
		} else { // In graphic memory.
			helper::flipVertical(image);
			SDL_Surface* surface = helper::createSurface(image->w, image->h);
			SDL_BlitSurface(image, 0, surface, &image->clip_rect);
			texture.bindTexture();
			glTexSubImage2D(GL_TEXTURE_2D, 0,
				dstRec.x, texture.height_ - image->h - dstRec.y, // Sdl uses upp-left, opengl uses down-left.
				image->w, image->h,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				surface->pixels);
			SDL_FreeSurface(surface);
		}
	}

	std::shared_ptr<TextureAtlas::Node> TextureAtlas::Node::createRoot(std::shared_ptr<Node>& root,
		int width, int height, SDL_Surface* image, int border) {
		
		// Image doesn't fit?
		if (image->w > width || image->h > height) {
			// Image to large!
			return 0;
		}
		root = std::make_shared<Node>(0, 0, width, height);
		return root->insert(image, border);
	}

	TextureAtlas::Node::Node(int x, int y, int w, int h) : image_(0) {
		rect_.x = x;
		rect_.y = y;
		rect_.w = w;
		rect_.h = h;
	}

	std::shared_ptr<TextureAtlas::Node> TextureAtlas::Node::insert(SDL_Surface* image, int border) {
		// Is not a leaf!
		if (left_ != 0 && right_ != 0) {
			auto node = left_->insert(image, border);
			if (node != 0) {
				// Image inserted.
				return node;
			}
			// Image didn't fit, try the other node.
			return right_->insert(image, border);
		} else {
			if (image_ != 0) {
				// Node is already filled!
				return 0;
			}
			
			if (image->w + 2 * border > rect_.w || image->h + 2 * border > rect_.h) {
				// Image to large!
				return 0;
			}

			// Fits perfectly?
			if (image->w + 2 * border == rect_.w && image->h + 2 * border == rect_.h) {
				image_ = image;
				return shared_from_this();
			}

			// Split the node in half.
			if (rect_.w - image->w < rect_.h - image->h) { // Split vertical.
				left_ = std::make_shared<Node>(rect_.x, rect_.y,
					rect_.w, image->h + 2 * border); // Up.

				right_ = std::make_shared<Node>(rect_.x, rect_.y + image->h + 2 * border,
					rect_.w, rect_.h - image->h - 2 * border); // Down.
			
			} else { // Split horizontal.
				left_ = std::make_shared<Node>(rect_.x, rect_.y,
					image->w + 2 * border, rect_.h); // Left.
				
				right_ = std::make_shared<Node>(rect_.x + image->w + 2 * border, rect_.y,
					rect_.w - image->w - 2 * border, rect_.h); // Right.
			}

			// Insert the image in the left node.
			return left_->insert(image, border);
		}
	}

	TextureAtlas::TextureAtlas(int width, int height, std::function<void()> filter)
		: root_(0), width_(width), height_(width) {

		texture_ = Texture(width, height, filter);
	}

	Sprite TextureAtlas::add(std::string filename, int border, std::string uniqueKey) {
		std::string key = filename + uniqueKey;
		auto it = images_.find(key);
		if (it == images_.end()) {
			SDL_Surface* image = IMG_Load(filename.c_str());
			if (image != 0) {
				mw::Sprite sprite = add(image, border, key);
				SDL_FreeSurface(image);
				return sprite;
			} else {
				std::cerr << "\nImage " << filename << " failed to load: " << IMG_GetError() << std::endl;
				return Sprite();
			}
		}
		return it->second;
	}

	Sprite TextureAtlas::add(SDL_Surface* image, int border, std::string key) {
		auto it = images_.find(key);
		if (key.empty() || it == images_.end()) {
			std::shared_ptr<Node> node = nullptr;
			if (texture_.isValid()) {
				if (root_) {
					node = root_->insert(image, border);
				} else {
					node = Node::createRoot(root_, width_, height_, image, border);
				}
				if (node) {
					// Only when atlas is not full.
					SDL_Rect rect = node->getRect();
					rect.w -= 2 * border;
					rect.h -= 2 * border;
					rect.x += border;
					rect.y += border;
					uploadSdlSurfaceToTexture(image, rect, texture_);
					// If key is empty, then the default sprite is overridden.
					Sprite& sprite = images_[key];
					sprite = Sprite(texture_,
						(float) rect.x, (float) (texture_.getHeight() - rect.y - image->h),
						(float) image->w, (float) image->h);
					return sprite;
				} else {
					std::cerr << "\nTextureAtlas: Not enough image space to insert image." << std::endl;
					return mw::Sprite();
				}
			} else {
				return mw::Sprite();
			}
		}
		return it->second; // Return already loaded sprite.
	}

	Sprite TextureAtlas::get(std::string key) const {
		auto it = images_.find(key);
		if (it != images_.end()) {
			return it->second;
		}
		return Sprite();
	}

} // Namespace mw.
