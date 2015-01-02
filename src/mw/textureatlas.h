#ifndef MW_TEXTUREATLAS_H
#define MW_TEXTUREATLAS_H

#include "opengl.h"
#include "texture.h"
#include "sprite.h"

#include <string>
#include <memory>
#include <map>

namespace mw {

	class TextureAtlas {
	public:
		TextureAtlas(int width, int height, std::function<void()> filter = []() {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		});
		
		TextureAtlas(const TextureAtlas&) = delete;
		TextureAtlas& operator=(const TextureAtlas&) = delete;

		Sprite add(std::string filename, std::string uniqueKey = "");

		// Add the image to the texture atlas. Return true if sucsessfull, 
		// else it return false.
		Sprite add(SDL_Surface* image, std::string uniqueKey = "");

		inline const Texture& getTexture() const {
			return texture_;
		}

		Sprite get(std::string key) const;

	private:
		static void uploadSdlSurfaceToTexture(SDL_Surface* image, SDL_Rect dstRec, Texture& texture);

		class Node {
		public:
			// Create a new root node with plane, dimension defined by width and height, and 
			// a first image added at the top left corner of the defined plane.
			// Return the node containing the image if sucsessfull, else null
			// is returned.
			static std::shared_ptr<Node> createRoot(std::shared_ptr<Node>& root, int width, int height, SDL_Surface* image);

			// Insert an image on the plane, dimensions defined by the root node.
			// Should only be called by the root node.
			// Return the node containing the image if sucsessfull, else null
			// is returned.
			std::shared_ptr<Node> insert(SDL_Surface* image);

			Node(int x, int y, int w, int h);

			// Return the coordinate for the node. (x,y) represents the
			// up-left coordinate of the rectangle.
			inline SDL_Rect getRect() const {
				return rect_;
			}

		private:
			std::shared_ptr<Node> insert(int currentDepth, SDL_Surface* image);

			SDL_Surface* image_;
			std::shared_ptr<Node> left_;
			std::shared_ptr<Node> right_;
			SDL_Rect rect_;
		};

		Texture texture_;
		std::map<std::string, Sprite> images_;
		std::shared_ptr<Node> root_;
		int width_, height_;
	};

} // Namespace mw.

#endif // MW_TEXTUREATLAS_H
