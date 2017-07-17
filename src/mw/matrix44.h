#ifndef MW_MATRIX44_H
#define MW_MATRIX44_H

#include <cmath>
#include <array>

namespace mw {

	// A 4x4 matrix saved internally saved as an column-major order.
	template <typename T>
	class Matrix44 {
	public:		
		static const Matrix44<T> ZERO;
		static const Matrix44<T> I;

		// An empty matrix with undefined values.
		Matrix44() = default;

		// Defines a matrix. The matrix is internally saved as an column-major order.
		Matrix44(
			T m00, T m01, T m02, T m03,
			T m10, T m11, T m12, T m13,
			T m20, T m21, T m22, T m23,
			T m30, T m31, T m32, T m33);

		// Create a matrix based on an array in column-major order.
		Matrix44(const std::array<T, 16>& data);

		Matrix44<T> operator*(const Matrix44<T>& m) const;

		Matrix44<T> operator+(const Matrix44<T>& matrix) const;

		T& operator()(int row, int column);

		T operator()(int row, int column) const;

		const T* data() const;

		T& operator[](int index);

		T operator[](int index) const;

		size_t size() const;

		typename std::array<T, 16>::iterator begin();

		typename std::array<T, 16>::iterator end();

		typename std::array<T, 16>::const_iterator begin() const;
		
		typename std::array<T, 16>::const_iterator end() const;

		Matrix44<T> transpose() const;

		Matrix44<T> inverse() const;

		T determinant() const;

	private:
		std::array<T, 16> data_;
	};

	template <typename T>
	const Matrix44<T> Matrix44<T>::I(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	template <typename T>
	const Matrix44<T> Matrix44<T>::ZERO(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);

	// Return the translation matrix.
	template <typename T>
	Matrix44<T> getTranslateMatrix44(T x, T y, T z = 0) {
		return Matrix44<T>(
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1);
	}

	// Return the rotation matrix.
	template <typename T>
	Matrix44<T> getRotateMatrix44(T angle, T x, T y, T z) {
		T s = std::sin(angle);
		T c = std::cos(angle);

		return Matrix44<T>(
			x*x*(1 - c) + c, x*y*(1 - c) - z*s, x*z*(1 - c) + y*s, 0,
			y*x*(1 - c) + z*s, y*y*(1 - c) + c, y*z*(1 - c) - x*s, 0,
			z*x*(1 - c) - y*s, y*z*(1 - c) + x*s, z*z*(1 - c) + c, 0,
			0, 0, 0, 1);
	}

	// Return the scale matrix.
	template <typename T>
	Matrix44<T> getScaleMatrix44(T x, T y, T z = 1) {
		return Matrix44<T>(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1);
	}

	// Defines the 2d orthogonal projection matrix.
	template <typename T>
	Matrix44<T> getOrtho2D(T left, T right, T bottom, T top) {
		return Matrix44<T>(
			2 / (right - left), 0, 0, -(right + left) / (right - left),
			0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
			0, 0, 1, 0,
			0, 0, 0, 1);
	}

	// Return the orthogonal projection matrix.
	template <typename T>
	Matrix44<T> getOrthoProjectionMatrix44(T left, T right, T bottom, T top,
		T nearVal = -1, T farVal = 1) {
		return Matrix44<T>(
			2 / (right - left), 0, 0, -(right + left) / (right - left),
			0, 2 / (top - bottom), 0, -(top + bottom) / (top - bottom),
			0, 0, -2 / (farVal - nearVal), -(farVal + nearVal) / (farVal - nearVal),
			0, 0, 0, 1);
	}

	// Return the orthogonal projection matrix. 
	template <typename T>
	Matrix44<T> getFrustrumProjectionMatrix44(T left, T right,
		T bottom, T top,
		T nearVal = -1, T farVal = 1) {

		return Matrix44<T>(2 * nearVal / (right - left), 0, (right + left) / (right - left), 0,
			0, 2 * nearVal / (top - bottom), (top + bottom) / (top - bottom), 0,
			0, 0, -(farVal + nearVal) / (farVal - nearVal), -2 * farVal * nearVal / (farVal - nearVal),
			0, 0, -1, 0);
	}

	// Translate the matrix in the xy-plane. Multiplies the matrix provided with the translate matrix from the right.
	template <typename T>
	void translate2D(Matrix44<T>& matrix, T x, T y) {
		matrix(0, 3) = matrix(0, 0) * x + matrix(0, 1) * y + matrix(0, 3);
		matrix(1, 3) = matrix(1, 0) * x + matrix(1, 1) * y + matrix(1, 3);
		matrix(2, 3) = matrix(2, 0) * x + matrix(2, 1) * y + matrix(2, 3);
		matrix(3, 3) = matrix(3, 0) * x + matrix(3, 1) * y + matrix(3, 3);
	}

	// Rotate the matrix in the xy-plane. Multiplies the matrix provided with the rotation matrix from the right.
	template <typename T>
	void rotate2D(Matrix44<T>& matrix, T angle) {
		T s = std::sin(angle);
		T c = std::cos(angle);

		matrix = matrix * Matrix44<T>(
			c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}

	// Scale the matrix in the xy-plane. Multiplies the matrix provided with the scale matrix from the right.
	template <typename T>
	void scale2D(Matrix44<T>& matrix, T sx, T sy) {
		matrix[0] *= sx;
		matrix[1] *= sx;
		matrix[2] *= sx;
		matrix[3] *= sx;
		matrix[4] *= sy;
		matrix[5] *= sy;
		matrix[6] *= sy;
		matrix[7] *= sy;
	}

	template <typename T>
	Matrix44<T>::Matrix44(
		T m00, T m01, T m02, T m03,
		T m10, T m11, T m12, T m13,
		T m20, T m21, T m22, T m23,
		T m30, T m31, T m32, T m33)
		: data_({
		m00, m10, m20, m30,
		m01, m11, m21, m31,
		m02, m12, m22, m32,
		m03, m13, m23, m33}) {
	}

	template <typename T>
	Matrix44<T>::Matrix44(const std::array<T, 16>& data) : data_(data) {
	}

	template <typename T>
	Matrix44<T> Matrix44<T>::operator*(const Matrix44<T>& m) const {
		Matrix44<T> matrix;
		const Matrix44<T>& m2 = *this;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				matrix(i, j) = m2(i, 0) * m(0, j) + m2(i, 1) * m(1, j) + m2(i, 2) * m(2, j) + m2(i, 3) * m(3, j);
			}
		}
		return matrix;
	}

	template <typename T>
	Matrix44<T> Matrix44<T>::operator+(const Matrix44<T>& matrix) const {
		Matrix44<T> m;
		for (int i = 0; i < 16; ++i) {
			m[i] = data_[i] + matrix.data_[i];
		}
		return m;
	}

	template <typename T>
	T& Matrix44<T>::operator()(int row, int column) {
		return data_[row + column * 4];
	}

	template <typename T>
	T Matrix44<T>::operator()(int row, int column) const {
		return data_[row + column * 4];
	}

	template <typename T>
	const T* Matrix44<T>::data() const {
		return data_.data();
	}

	template <typename T>
	T& Matrix44<T>::operator[](int index) {
		return data_[index];
	}

	template <typename T>
	T Matrix44<T>::operator[](int index) const {
		return data_[index];
	}

	template <typename T>
	size_t Matrix44<T>::size() const {
		return data_.size();
	}

	template <typename T>
	typename std::array<T, 16>::iterator Matrix44<T>::begin() {
		return data_.begin();
	}

	template <typename T>
	typename std::array<T, 16>::iterator Matrix44<T>::end() {
		return data_.end();
	}

	template <typename T>
	typename std::array<T, 16>::const_iterator Matrix44<T>::begin() const {
		return data_.cbegin();
	}

	template <typename T>
	typename std::array<T, 16>::const_iterator Matrix44<T>::end() const {
		return data_.cend();
	}

	template <typename T>
	Matrix44<T> Matrix44<T>::transpose() const {
		Matrix44<T> m;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				m(i, j) = Matrix44<T>::operator()(j, i);
			}
		}
		return m;
	}

	template <typename T>
	Matrix44<T> Matrix44<T>::inverse() const {
		Matrix44<T> tmp;
		const Matrix44<T>& m = *this;
		T scale = 1 / determinant();
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

	template <typename T>
	T Matrix44<T>::determinant() const {
		const Matrix44<T>& m = *this;
		return
			m(0, 3)*m(1, 2)*m(2, 1)*m(3, 0) - m(0, 2)*m(1, 3)*m(2, 1)*m(3, 0) - m(0, 3)*m(1, 1)*m(2, 2)*m(3, 0) + m(0, 1)*m(1, 3)*m(2, 2)*m(3, 0) +
			m(0, 2)*m(1, 1)*m(2, 3)*m(3, 0) - m(0, 1)*m(1, 2)*m(2, 3)*m(3, 0) - m(0, 3)*m(1, 2)*m(2, 0)*m(3, 1) + m(0, 2)*m(1, 3)*m(2, 0)*m(3, 1) +
			m(0, 3)*m(1, 0)*m(2, 2)*m(3, 1) - m(0, 0)*m(1, 3)*m(2, 2)*m(3, 1) - m(0, 2)*m(1, 0)*m(2, 3)*m(3, 1) + m(0, 0)*m(1, 2)*m(2, 3)*m(3, 1) +
			m(0, 3)*m(1, 1)*m(2, 0)*m(3, 2) - m(0, 1)*m(1, 3)*m(2, 0)*m(3, 2) - m(0, 3)*m(1, 0)*m(2, 1)*m(3, 2) + m(0, 0)*m(1, 3)*m(2, 1)*m(3, 2) +
			m(0, 1)*m(1, 0)*m(2, 3)*m(3, 2) - m(0, 0)*m(1, 1)*m(2, 3)*m(3, 2) - m(0, 2)*m(1, 1)*m(2, 0)*m(3, 3) + m(0, 1)*m(1, 2)*m(2, 0)*m(3, 3) +
			m(0, 2)*m(1, 0)*m(2, 1)*m(3, 3) - m(0, 0)*m(1, 2)*m(2, 1)*m(3, 3) - m(0, 1)*m(1, 0)*m(2, 2)*m(3, 3) + m(0, 0)*m(1, 1)*m(2, 2)*m(3, 3);
	}

} // Namespace mw.

#endif // MW_MATRIX44_H
