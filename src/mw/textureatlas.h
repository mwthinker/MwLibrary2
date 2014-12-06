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

		void add(std::string filename) {
			SDL_Surface* surface = IMG_Load(filename.c_str());
			if (surface != 0) {
				images_[filename] = surface;
			} else {
				//std::cerr << "\nImage " << filename << " failed to load: " << IMG_GetError() << std::endl;
			}
		}

		void generateAtlas();

	private:
		std::map<std::string, SDL_Surface*> images_;
	};

} // Namespace mw.

#endif // MW_TEXTUREATLAS_H
