#include "matrix.h"

namespace mw {
	
	Matrix44 Matrix44::operator*(const Matrix44& matrix) const {
		Matrix44 m(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
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

} // Namespace mw.
