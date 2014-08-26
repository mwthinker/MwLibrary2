#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <cmath>

namespace mw {

	class Matrix44 {
	public:
		inline Matrix44() {
		}

		inline Matrix44(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33
			) : data_({
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33}) {
		}

		inline Matrix44(const std::array<float, 16>& matrix) {
			data_ = matrix;
		}

		Matrix44 operator*(const Matrix44& matrix) const;

		Matrix44 operator+(const Matrix44& matrix) const;

		inline float& operator()(int row, int column) {
			return data_[column + row * 4];
		}

		inline float operator()(int row, int column) const {
			return data_[column + row * 4];
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

	private:
		std::array<float, 16> data_;
	};

	static const Matrix44 ZERO_44(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	static const Matrix44 I_44(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

} // Namespace mw.

#endif // MATRIX_H
