#ifndef TESTDATASHADER_H
#define TESTDATASHADER_H

#include "testshader.h"

#include <mw/sprite.h>
#include <mw/text.h>
#include <mw/vertexdata.h>
#include <mw/vertexbufferobject.h>

#include <memory>

class TestShaderData : public mw::VertexData {
public:
	TestShaderData(const std::shared_ptr<TestShader>& testShader) : testShader_(testShader) {
	}

	unsigned int vertexSizeInFloat() const override {
		return testShader_->vertexSizeInFloat();
	}

	void setVertexAttribPointer() const override {
		testShader_->setVertexAttribPointer();
	}

	void useProgram() const override {
		testShader_->useProgram();
	}

	void setColor(const mw::Color& color) const {
		testShader_->setColorU(color);
	}

	void setColor(float red, float green, float blue, float alpha = 1) const {
		testShader_->setColorU(red, green, blue, alpha);
	}
	
	void setTexture(bool texture) const {
		testShader_->setTextureU(texture);
	}

	void drawTRIANGLES() {
		drawMode(GL_TRIANGLES);
	}

	void drawTRIANGLE_STRIP() {
		drawMode(GL_TRIANGLE_STRIP);
	}

	void addSquareTRIANGLES(float x1, float y1,
		float x2, float y2,
		float x3, float y3,
		float x4, float y4) {		

		// Left triangle |_
		addTriangleTRIANGLES(
			x1, y1,
			x2, y2,
			x4, y4,
			0, 0,
			0, 0,
			0, 0);
		//                _
		// Right triangle  |
		addTriangleTRIANGLES(
			x4, y4,
			x2, y2,
			x3, y3,
			0, 0,
			0, 0,
			0, 0);
	}

	void addSquareTRIANGLES(float x1, float y1,
		float x2, float y2,
		float x3, float y3,
		float x4, float y4,
		const mw::Sprite& sprite) {
		int textureW = sprite.getTexture().getWidth();
		int textureH = sprite.getTexture().getHeight();

		// Left triangle |_
		addTriangleTRIANGLES(
			x1, y1,
			x2, y2,
			x4, y4,
			sprite.getX() / textureW, sprite.getY() / textureH,
			(sprite.getX() + sprite.getWidth()) / textureW, sprite.getY() / textureH,
			sprite.getX() / textureW, (sprite.getY() + sprite.getHeight()) / textureH);
		//                _
		// Right triangle  |
		addTriangleTRIANGLES(
			x4, y4,
			x2, y2,
			x3, y3,
			sprite.getX() / textureW, (sprite.getY() + sprite.getHeight()) / textureH,
			(sprite.getX() + sprite.getWidth()) / textureW, sprite.getY() / textureH,
			(sprite.getX() + sprite.getWidth()) / textureW, (sprite.getY() + sprite.getHeight()) / textureH);
	}

	void addSquareTRIANGLE_STRIP(float x, float y, const mw::Text& text) {
		addVertex(x, y, 0, 0);
		addVertex(x + text.getWidth(), y, 1, 0);
		addVertex(x, text.getHeight() + y, 0, 1);
		addVertex(x + text.getWidth(), text.getHeight() + y, 1, 1);
	}

	void addTriangleTRIANGLES(
		float x1, float y1,
		float x2, float y2,
		float x3, float y3,
		float xTex1, float yTex1,
		float xTex2, float yTex2,
		float xTex3, float yTex3) {

		addVertex(x1, y1, xTex1, yTex1);
		addVertex(x2, y2, xTex2, yTex2);
		addVertex(x3, y3, xTex3, yTex3);
	}

	void addEmptySquareTRIANGLE_STRIP() {
		addEmptyVertexes<4>(4);
	}

	void addEmptySquareTRIANGLES() {
		addEmptyVertexes<4>(3);
		addEmptyVertexes<4>(3);
	}

	void addVertex(float x, float y, float xTex, float yTex) {
		VertexData::addVertex<4>({x, y, xTex, yTex});
	}

private:
	std::shared_ptr<TestShader> testShader_;
};

#endif // TESTDATASHADER_H
