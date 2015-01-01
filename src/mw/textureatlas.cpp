#include "textureatlas.h"

#include <iostream>

namespace mw {

	void TextureAtlas::uploadSdlSurfaceToTexture(SDL_Surface* image, SDL_Rect dstRec, Texture& texture) {
		// In computer memory?
		if (texture.imageData_->texture_ == 0) {
			image = SDL_ConvertSurface(image, texture.imageData_->preLoadSurface_->format, 0);
			SDL_BlitSurface(image, 0, texture.imageData_->preLoadSurface_, &dstRec);
		} else { // In graphic memory.
			image = SDL_ConvertSurface(image, texture.imageData_->preLoadSurface_->format, 0);
			helper::invert<4>(image);
#if MW_OPENGLES2
			mw::glTexSubImage2D(GL_TEXTURE_2D, 0,
				dstRec.x, texture.height_ - dstRec.y - 1, // Sdl uses upp-left, opengl uses down-left.
				dstRec.w, dstRec.h,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				image->pixels);
#else // MW_OPENGLES2
			glTexSubImage2D(GL_TEXTURE_2D, 0,
				dstRec.x, texture.height_ - dstRec.y - 1, // Sdl uses upp-left, opengl uses down-left.
				dstRec.w, dstRec.h,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				image->pixels);
#endif // MW_OPENGLES2
		}
	}

	std::shared_ptr<TextureAtlas::Node> TextureAtlas::Node::createRoot(std::shared_ptr<Node>& root, int width, int height, SDL_Surface* image) {
		// Image doesn't fit?
		if (image->w > width || image->h > height) {
			// Image to large!
			return 0;
		}
		root = std::make_shared<Node>(0, 0, width, height);
		return root->insert(image);;
	}

	std::shared_ptr<TextureAtlas::Node> TextureAtlas::Node::insert(SDL_Surface* image) {
		return insert(0, image);
	}

	TextureAtlas::Node::Node(int x, int y, int w, int h) : image_(0) {
		rect_.x = x;
		rect_.y = y;
		rect_.w = w;
		rect_.h = h;
	}

	std::shared_ptr<TextureAtlas::Node> TextureAtlas::Node::insert(int currentDepth, SDL_Surface* image) {
		// Is not a leaf!
		if (left_ != 0 && right_ != 0) {
			auto node = left_->insert(currentDepth + 1, image);
			if (node != 0) {
				// Image inserted.
				return node;
			}
			// Image didn't fit, try the other node.
			return right_->insert(currentDepth + 1, image);
		} else {
			if (image_ != 0) {
				// Node is already filled!
				return 0;
			}
			
			if (image->w > rect_.w || image->h > rect_.h) {
				// Image to large!
				return 0;
			}

			// Fits perfectly?
			if (image->w == rect_.w && image->h == rect_.h) {
				image_ = image;
			}

			// Must split the node in half.
			if (currentDepth % 2 == 0) { // Split vertical.
				left_ = std::make_shared<Node>(rect_.x, rect_.y, rect_.w, image->h); // Up.
				right_ = std::make_shared<Node>(rect_.x, rect_.y + image->h, rect_.w, rect_.h - image->h); // Down.
			} else { // Split horizontal.
				left_ = std::make_shared<Node>(rect_.x, rect_.y, image->w, rect_.h); // Left.
				right_ = std::make_shared<Node>(rect_.x + image->w, rect_.y, rect_.w - image->w, rect_.h); // Right.
			}

			// Insert the image in the left node.
			left_->image_ = image;
			return left_;
		}
	}

	TextureAtlas::TextureAtlas() : root_(0), width_(0), height_(0) {
	}

	TextureAtlas::TextureAtlas(int width, int height, std::function<void()> filter) : root_(0), width_(width), height_(width) {
		texture_ = Texture(width, height, filter);
	}

	Sprite TextureAtlas::add(std::string filename, std::string uniqueKey) {
		int size = images_.size();
		Sprite& sprite = images_[filename + uniqueKey];

		if (size != images_.size()) {
			SDL_Surface* image = IMG_Load(filename.c_str());
			if (image != 0) {
				sprite = add(image);
				SDL_FreeSurface(image);
			} else {
				images_.erase(filename + uniqueKey);
				std::cerr << "\nImage " << filename << " failed to load: " << IMG_GetError() << std::endl;
			}
		}

		return sprite;
	}

	Sprite TextureAtlas::add(SDL_Surface* image) {
		std::shared_ptr<Node> node;
		if (texture_.isValid()) {
			if (root_ == 0) {
				node = Node::createRoot(root_, width_, height_, image);
			} else {
				node = root_->insert(image);
			}
		}
		if (node != 0) {
			SDL_Rect rect = node->getRect();
			uploadSdlSurfaceToTexture(image, rect, texture_);
			return Sprite(texture_, (float) rect.x, (float) (texture_.getHeight() - rect.y), (float) rect.w, (float) rect.h);
		}
		return Sprite();
	}

} // Namespace mw.
