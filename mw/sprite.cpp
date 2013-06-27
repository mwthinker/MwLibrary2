#include "sprite.h"

#include <string>

#include <SDL.h>
#include <SDL_opengl.h>

namespace mw {

    Sprite::Sprite() {
		drawPixelSize_ = false;
    }

	Sprite::Sprite(std::string image) {
		texture_ = TexturePtr(new mw::Texture(image));
		drawPixelSize_ = false;
    }

    Sprite::Sprite(const TexturePtr& texture) {
        texture_ = texture;
		drawPixelSize_ = false;
    }

    void Sprite::setTexture(TexturePtr& texture) {
        texture_ = texture;
    }

    TexturePtr Sprite::getTexture() const {
        return texture_;
    }

    void Sprite::draw() {
        if (texture_ != 0) {
            texture_->bind();

            glEnable(GL_BLEND);
            glEnable(GL_TEXTURE_2D);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glPushMatrix();
			
			if (drawPixelSize_) {
				glScaled(texture_->getWidth(),texture_->getHeight(),1);
			}

			// Inverts the image. Y-is "up" for the window and x is "right".
            glScaled(1,-1, 1);

            glNormal3d(0,0,1);
            glBegin(GL_QUADS);
            glTexCoord2d(0,0);
            glVertex2d(-0.5, -0.5);

            glTexCoord2d(1,0);
            glVertex2d(0.5, -0.5);

            glTexCoord2d(1,1);
            glVertex2d(0.5, 0.5);

            glTexCoord2d(0,1);
            glVertex2d(-0.5, 0.5);
            glEnd();

            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
        }
    }

	void Sprite::setDrawPixelSize(bool drawPixelSize) {
		drawPixelSize_ = drawPixelSize;
	}

	bool Sprite::isDrawingPixelSize() {
		return drawPixelSize_;
	}

} // Namespace mw.
