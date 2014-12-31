#ifndef MW_TEXTUREATLAS_H
#define MW_TEXTUREATLAS_H

#include "opengl.h"
#include "texture.h"

#include <string>
#include <map>

namespace mw {

	class TextureAtlas {
	public:
		// Empty texture. Does nothing.
		TextureAtlas();

		TextureAtlas(int width, int height);

		void add(std::string filename) {
			SDL_Surface* surface = IMG_Load(filename.c_str());
			if (surface != 0) {
				images_[filename] = surface;
			} else {
				//std::cerr << "\nImage " << filename << " failed to load: " << IMG_GetError() << std::endl;
			}
		}

		// Add the image to the texture atlas. Return true if sucsessfull, 
		// else it return false.
		bool add(SDL_Surface* image);

	private:
		class Node {
		public:
			// Create a new root node with plane, dimension defined by width and height, and 
			// a first image added at the top left corner of the defined plane.
			// Return the node containing the image if sucsessfull, else null
			// is returned.
			static Node* createRoot(int width, int height, SDL_Surface* image);

			// Insert an image on the plane, dimensions defined by the root node.
			// Should only be called by the root node.
			// Return the node containing the image if sucsessfull, else null
			// is returned.
			Node* insert(SDL_Surface* image);

		private:
			Node(int size, int x, int y, int w, int h);

			Node* insert(int currentDepth, SDL_Surface* image);

			SDL_Surface* image_;
			Node* left_;
			Node* right_;
			int x_, y_;
			int w_, h_;
			int size_;
		};

		std::map<std::string, SDL_Surface*> images_;
		Node* root_;
		int width_, height_;
	};

} // Namespace mw.

#endif // MW_TEXTUREATLAS_H
