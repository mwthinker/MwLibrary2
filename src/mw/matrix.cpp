#include "matrix.h"

#include <cmath>

namespace mw {

	Matrix44 Matrix44::operator*(const Matrix44& matrix) const {
		Matrix44 m = ZERO_44;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				for (int k = 0; k < 4; ++k) {
					m(i, j) += Matrix44::operator()(i, k)*matrix(k, j);
				}
			}
		}
		return m;
	}

	Matrix44 Matrix44::operator+(const Matrix44& matrix) const {
		Matrix44 m;
		for (int i = 0; i < 16; ++i) {
			m[i] = data_[i] + matrix.data_[i];
		}
		return m;
	}

	Matrix44 Matrix44::transpose() const {
		Matrix44 m;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				m(i, j) = Matrix44::operator()(j, i);
			}
		}
		return m;
	}

	float Matrix44::determinant() const {
		const mw::Matrix44& m = *this;
		return
			m(0, 3)*m(1, 2)*m(2, 1)*m(3, 0) - m(0, 2)*m(1, 3)*m(2, 1)*m(3, 0) - m(0, 3)*m(1, 1)*m(2, 2)*m(3, 0) + m(0, 1)*m(1, 3)*m(2, 2)*m(3, 0) +
			m(0, 2)*m(1, 1)*m(2, 3)*m(3, 0) - m(0, 1)*m(1, 2)*m(2, 3)*m(3, 0) - m(0, 3)*m(1, 2)*m(2, 0)*m(3, 1) + m(0, 2)*m(1, 3)*m(2, 0)*m(3, 1) +
			m(0, 3)*m(1, 0)*m(2, 2)*m(3, 1) - m(0, 0)*m(1, 3)*m(2, 2)*m(3, 1) - m(0, 2)*m(1, 0)*m(2, 3)*m(3, 1) + m(0, 0)*m(1, 2)*m(2, 3)*m(3, 1) +
			m(0, 3)*m(1, 1)*m(2, 0)*m(3, 2) - m(0, 1)*m(1, 3)*m(2, 0)*m(3, 2) - m(0, 3)*m(1, 0)*m(2, 1)*m(3, 2) + m(0, 0)*m(1, 3)*m(2, 1)*m(3, 2) +
			m(0, 1)*m(1, 0)*m(2, 3)*m(3, 2) - m(0, 0)*m(1, 1)*m(2, 3)*m(3, 2) - m(0, 2)*m(1, 1)*m(2, 0)*m(3, 3) + m(0, 1)*m(1, 2)*m(2, 0)*m(3, 3) +
			m(0, 2)*m(1, 0)*m(2, 1)*m(3, 3) - m(0, 0)*m(1, 2)*m(2, 1)*m(3, 3) - m(0, 1)*m(1, 0)*m(2, 2)*m(3, 3) + m(0, 0)*m(1, 1)*m(2, 2)*m(3, 3);
	}

	mw::Matrix44 Matrix44::inverse() const {
		mw::Matrix44 tmp;
		const mw::Matrix44& m = *this;
		float scale = 1.f / determinant();
		tmp(0, 0) = scale*(m(1, 2)*m(2, 3)*m(3, 1) - m(1, 3)*m(2, 2)*m(3, 1) + m(1, 3)*m(2, 1)*m(3, 2) - m(1, 1)*m(2, 3)*m(3, 2) - m(1, 2)*m(2, 1)*m(3, 3) + m(1, 1)*m(2, 2)*m(3, 3));
		tmp(0, 1) = scale*(m(0, 3)*m(2, 2)*m(3, 1) - m(0, 2)*m(2, 3)*m(3, 1) - m(0, 3)*m(2, 1)*m(3, 2) + m(0, 1)*m(2, 3)*m(3, 2) + m(0, 2)*m(2, 1)*m(3, 3) - m(0, 1)*m(2, 2)*m(3, 3));
		tmp(0, 2) = scale*(m(0, 2)*m(1, 3)*m(3, 1) - m(0, 3)*m(1, 2)*m(3, 1) + m(0, 3)*m(1, 1)*m(3, 2) - m(0, 1)*m(1, 3)*m(3, 2) - m(0, 2)*m(1, 1)*m(3, 3) + m(0, 1)*m(1, 2)*m(3, 3));
		tmp(0, 3) = scale*(m(0, 3)*m(1, 2)*m(2, 1) - m(0, 2)*m(1, 3)*m(2, 1) - m(0, 3)*m(1, 1)*m(2, 2) + m(0, 1)*m(1, 3)*m(2, 2) + m(0, 2)*m(1, 1)*m(2, 3) - m(0, 1)*m(1, 2)*m(2, 3));
		tmp(1, 0) = scale*(m(1, 3)*m(2, 2)*m(3, 0) - m(1, 2)*m(2, 3)*m(3, 0) - m(1, 3)*m(2, 0)*m(3, 2) + m(1, 0)*m(2, 3)*m(3, 2) + m(1, 2)*m(2, 0)*m(3, 3) - m(1, 0)*m(2, 2)*m(3, 3));
		tmp(1, 1) = scale*(m(0, 2)*m(2, 3)*m(3, 0) - m(0, 3)*m(2, 2)*m(3, 0) + m(0, 3)*m(2, 0)*m(3, 2) - m(0, 0)*m(2, 3)*m(3, 2) - m(0, 2)*m(2, 0)*m(3, 3) + m(0, 0)*m(2, 2)*m(3, 3));
		tmp(1, 2) = scale*(m(0, 3)*m(1, 2)*m(3, 0) - m(0, 2)*m(1, 3)*m(3, 0) - m(0, 3)*m(1, 0)*m(3, 2) + m(0, 0)*m(1, 3)*m(3, 2) + m(0, 2)*m(1, 0)*m(3, 3) - m(0, 0)*m(1, 2)*m(3, 3));
		tmp(1, 3) = scale*(m(0, 2)*m(1, 3)*m(2, 0) - m(0, 3)*m(1, 2)*m(2, 0) + m(0, 3)*m(1, 0)*m(2, 2) - m(0, 0)*m(1, 3)*m(2, 2) - m(0, 2)*m(1, 0)*m(2, 3) + m(0, 0)*m(1, 2)*m(2, 3));
		tmp(2, 0) = scale*(m(1, 1)*m(2, 3)*m(3, 0) - m(1, 3)*m(2, 1)*m(3, 0) + m(1, 3)*m(2, 0)*m(3, 1) - m(1, 0)*m(2, 3)*m(3, 1) - m(1, 1)*m(2, 0)*m(3, 3) + m(1, 0)*m(2, 1)*m(3, 3));
		tmp(2, 1) = scale*(m(0, 3)*m(2, 1)*m(3, 0) - m(0, 1)*m(2, 3)*m(3, 0) - m(0, 3)*m(2, 0)*m(3, 1) + m(0, 0)*m(2, 3)*m(3, 1) + m(0, 1)*m(2, 0)*m(3, 3) - m(0, 0)*m(2, 1)*m(3, 3));
		tmp(2, 2) = scale*(m(0, 1)*m(1, 3)*m(3, 0) - m(0, 3)*m(1, 1)*m(3, 0) + m(0, 3)*m(1, 0)*m(3, 1) - m(0, 0)*m(1, 3)*m(3, 1) - m(0, 1)*m(1, 0)*m(3, 3) + m(0, 0)*m(1, 1)*m(3, 3));
		tmp(2, 3) = scale*(m(0, 3)*m(1, 1)*m(2, 0) - m(0, 1)*m(1, 3)*m(2, 0) - m(0, 3)*m(1, 0)*m(2, 1) + m(0, 0)*m(1, 3)*m(2, 1) + m(0, 1)*m(1, 0)*m(2, 3) - m(0, 0)*m(1, 1)*m(2, 3));
		tmp(3, 0) = scale*(m(1, 2)*m(2, 1)*m(3, 0) - m(1, 1)*m(2, 2)*m(3, 0) - m(1, 2)*m(2, 0)*m(3, 1) + m(1, 0)*m(2, 2)*m(3, 1) + m(1, 1)*m(2, 0)*m(3, 2) - m(1, 0)*m(2, 1)*m(3, 2));
		tmp(3, 1) = scale*(m(0, 1)*m(2, 2)*m(3, 0) - m(0, 2)*m(2, 1)*m(3, 0) + m(0, 2)*m(2, 0)*m(3, 1) - m(0, 0)*m(2, 2)*m(3, 1) - m(0, 1)*m(2, 0)*m(3, 2) + m(0, 0)*m(2, 1)*m(3, 2));
		tmp(3, 2) = scale*(m(0, 2)*m(1, 1)*m(3, 0) - m(0, 1)*m(1, 2)*m(3, 0) - m(0, 2)*m(1, 0)*m(3, 1) + m(0, 0)*m(1, 2)*m(3, 1) + m(0, 1)*m(1, 0)*m(3, 2) - m(0, 0)*m(1, 1)*m(3, 2));
		tmp(3, 3) = scale*(m(0, 1)*m(1, 2)*m(2, 0) - m(0, 2)*m(1, 1)*m(2, 0) + m(0, 2)*m(1, 0)*m(2, 1) - m(0, 0)*m(1, 2)*m(2, 1) - m(0, 1)*m(1, 0)*m(2, 2) + m(0, 0)*m(1, 1)*m(2, 2));
		return tmp;
	}

	Matrix44 getTranslateMatrix44(float x, float y, float z) {
		return mw::Matrix44(
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1);
	}

	Matrix44 getRotateMatrix44(float angle, float x, float y, float z) {
		float s = std::sin(angle);
		float c = std::cos(angle);

		return mw::Matrix44(
			x*x*(1 - c) + c,   x*y*(1 - c) - z*s, x*z*(1 - c) + y*s, 0,
			y*x*(1 - c) + z*s, y*y*(1 - c) + c,   y*z*(1 - c) - x*s, 0,
			z*x*(1 - c) - y*s, y*z*(1 - c) + x*s, z*z*(1 - c) + c,   0,
			0,                 0,                 0,                 1);
	}

	Matrix44 getScaleMatrix44(float x, float y, float z) {
		return mw::Matrix44(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1);
	}

	Matrix44 getOrthoProjectionMatrix44(float left, float right, float bottom, float top,
		float nearVal, float farVal) {

		return mw::Matrix44(
			2 / (right - left), 0, 0, -(right + left) / (right - left),
			0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
			0, 0, -2 / (farVal - nearVal), -(farVal + nearVal) / (farVal - nearVal),
			0, 0, 0, 1);
	}

	Matrix44 getFrustrumProjectionMatrix44(float left, float right,
		float bottom, float top,
		float nearVal, float farVal) {

		return mw::Matrix44(2 * nearVal / (right - left), 0, (right + left) / (right - left), 0,
			0, 2 * nearVal / (top - bottom), (top + bottom) / (top - bottom), 0,
			0, 0, -(farVal + nearVal) / (farVal - nearVal), -2 * farVal * nearVal / (farVal - nearVal),
			0, 0, -1, 0);
	}

	// Translate the matrix in the xy-plane.
	void translate2D(Matrix44& matrix, float x, float y) {
		matrix(0, 3) = matrix(0, 0) * x + matrix(0, 1) * y + matrix(0, 3);
		matrix(1, 3) = matrix(1, 0) * x + matrix(1, 1) * y + matrix(1, 3);
		matrix(2, 3) = matrix(2, 0) * x + matrix(2, 1) * y + matrix(2, 3);
		matrix(3, 3) = matrix(3, 0) * x + matrix(3, 1) * y + matrix(3, 3);
	}

	void rotate2D(Matrix44& matrix, float angle) {
		float s = std::sin(angle);
		float c = std::cos(angle);

        matrix = matrix * Matrix44(c, -s, 0, 0,
                                   s,  c, 0, 0,
                                   0,  0, 1, 0,
                                   0,  0, 0, 1);
    }

	void scale2D(Matrix44& matrix, float sx, float sy) {
		matrix[0] *= sx;
		matrix[1] *= sx;
        matrix[2] *= sx;
        matrix[3] *= sx;
		matrix[4] *= sy;
		matrix[5] *= sy;
		matrix[6] *= sy;
		matrix[7] *= sy;
	}

	void ortho2D(Matrix44& matrix, float left, float right, float bottom, float top) {
		matrix = Matrix44(
			2 / (right - left), 0, 0, -(right + left) / (right - left),
			0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
			0, 0, 1, 0,
			0, 0, 0, 1);
	}

} // Namespace mw.
