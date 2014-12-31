#include "textureatlas.h"

#include <vector>

namespace mw {

	TextureAtlas::Node* TextureAtlas::Node::createRoot(int width, int height, SDL_Surface* image) {
		// Image doesn't fit?
		if (image->w > width || image->h > height) {
			// Image to large!
			return 0;
		}
		Node* root = new Node(image->h, 0, 0, width, height);
		root->insert(image);
		return root;
	}

	TextureAtlas::Node* TextureAtlas::Node::insert(SDL_Surface* image) {
		return insert(0, image);
	}

	TextureAtlas::Node::Node(int size, int x, int y, int w, int h) {
		size_ = size;
		left_ = 0;
		right_ = 0;
		x_ = x;
		y_ = y;
		w_ = w;
		h_ = h;
		image_ = 0;
	}

	TextureAtlas::Node* TextureAtlas::Node::insert(int currentDepth, SDL_Surface* image) {
		// Is not a leaf!
		if (left_ != 0 && right_ != 0) {
			Node* node = left_->insert(currentDepth + 1, image);
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
			
			if (image->w > w_ || image->h > h_) {
				// Image to large!
				return 0;
			}

			// Fits perfectly?
			if (image->w == w_ && image->h == h_) {
				image_ = image;
			}

			// Must split the node in half.
			if (currentDepth % 2 == 0) { // Split vertical.
				left_ = new Node(image->w, x_, h_ - size_ + y_, w_, size_);
				right_ = new Node(image->w, x_, y_, w_, h_ - size_);
			} else { // Split horizontal.
				left_ = new Node(image->h, x_, y_, size_, h_);
				right_ = new Node(image->h, x_ + size_, y_, w_ - size_, h_);
			}

			// Insert the image in the left node.
			left_->image_ = image;
			return left_;
		}
	}

	TextureAtlas::TextureAtlas() : root_(0), width_(0), height_(0) {
	}

	TextureAtlas::TextureAtlas(int width, int height) : root_(0), width_(width), height_(width) {
	}

	bool TextureAtlas::add(SDL_Surface* image) {
		if (root_ == 0) {
			root_ = TextureAtlas::Node::createRoot(width_, height_, image);
			return root_ != 0;
		} else {
			Node* node = root_->insert(image);
			return node != 0;
		}
	}

} // Namespace mw.
