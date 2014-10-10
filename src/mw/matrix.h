#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <cmath>

namespace mw {

	// An 4x4 matrix saved internally saved as an column-major order.
	class Matrix44 {
	public:
		// An empty matrix with undefined values.
		inline Matrix44() {
		}

		// Defines a matrix. The matrix is internally saved as an column-major order.
		inline Matrix44(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
			: data_({
			m00, m10, m20, m30,
			m01, m11, m21, m31,
			m02, m12, m22, m32,
			m03, m13, m23, m33}) {
		}

		// Create a matrix based on an array in column-major order.
		inline Matrix44(const std::array<float, 16>& matrix) {
			data_ = matrix;
		}

		Matrix44 operator*(const Matrix44& matrix) const;

		Matrix44 operator+(const Matrix44& matrix) const;

		inline float& operator()(int row, int column) {
			return data_[row + column * 4];
		}

		inline float operator()(int row, int column) const {
			return data_[row + column * 4];
		}

		inline const float* data() const {
			return data_.data();
		}

		inline float& operator[](int index) {
			return data_[index];
		}

		inline float operator[](int index) const {
			return data_[index];
		}

		inline int size() const {
			return data_.size();
		}

		inline std::array<float, 16>::iterator begin() {
			return data_.begin();
		}

		inline std::array<float, 16>::iterator end() {
			return data_.end();
		}

		Matrix44 transpose() const;

		Matrix44 inverse() const;

		float determinant() const;

	private:
		std::array<float, 16> data_;
	};

	static const Matrix44 ZERO_44(0, 0, 0, 0,
								  0, 0, 0, 0,
								  0, 0, 0, 0,
								  0, 0, 0, 0);

	static const Matrix44 I_44(1, 0, 0, 0,
							   0, 1, 0, 0,
							   0, 0, 1, 0,
							   0, 0, 0, 1);

} // Namespace mw.

#endif // MATRIX_H
