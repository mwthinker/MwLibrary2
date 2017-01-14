#ifndef TESTSHADER_H
#define TESTSHADER_H

#include <mw/opengl.h>
#include <mw/vertexarrayobject.h>
#include <mw/matrix44.h>
#include <mw/shader.h>
#include <mw/color.h>

#include <string>

using Mat44 = mw::Matrix44<GLfloat>;
using Color = mw::Color<GLfloat>;

class TestShader {
public:
    TestShader();
    TestShader(std::string vShader, std::string fShader);

	inline static constexpr unsigned int vertexSizeInBytes() {
		return vertexSizeInFloat() * sizeof(GLfloat);
	}

	inline static constexpr unsigned int vertexSizeInFloat() {
		return 4;
	}

	void useProgram() const;
    void setVertexAttribPointer() const;

    // Uniforms. -------------------------------------------

    void setProjectionMatrixU(const Mat44& matrix) const;
    void setModelMatrixU(const Mat44& matrix) const;

    void setColorU(float red, float green, float blue, float alpha = 1) const;
    void setColorU(const Color& color) const;
    void setTextureU(bool texture) const;

private:
    mw::Shader shader_;

    int aPosIndex_;
    int aTexIndex_;

    int uProjIndex_;
    int uModelIndex_;

    int uColorIndex_;
    int uIsTexIndex_;
};

#endif // TESTSHADER_H
