#include "matrix.h"

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

	Matrix33 Matrix33::operator*(const Matrix33& matrix) const {
		Matrix33 m = ZERO_33;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				for (int k = 0; k < 3; ++k) {
					m(i, j) += Matrix33::operator()(i, k)*matrix(k, j);
				}
			}
		}
		return m;
	}

	Matrix33 Matrix33::operator+(const Matrix33& matrix) const {
		Matrix33 m;
		for (int i = 0; i < 9; ++i) {
			m[i] = data_[i] + matrix.data_[i];
		}
		return m;
	}

	Matrix33 Matrix33::transpose() const {
		Matrix33 m;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				m(i, j) = Matrix33::operator()(j, i);
			}
		}
		return m;
	}

	float Matrix33::determinant() const {
		const mw::Matrix33& m = *this;
		return m(0, 0) * (m(1, 1)*m(2, 2) - m(2, 1)*m(1, 2)) -
			   m(0, 1) * (m(1, 0)*m(2, 2) - m(1, 2)*m(2, 0)) +
			   m(0, 2) * (m(1, 0)*m(2, 1) - m(1, 1)*m(2, 0));
	}

	mw::Matrix33 Matrix33::inverse() const {
		const mw::Matrix33& m = *this;
		float scale = 1.f / determinant();
		return mw::Matrix33(scale*(m(1, 1)*m(2, 2) - m(1, 2)*m(2, 1)), scale*(m(0, 2)*m(2, 1) - m(0, 1)*m(2, 2)), scale*(m(0, 1)*m(1, 2) - m(0, 2)*m(1, 1)),
							scale*(m(1, 2)*m(2, 0) - m(1, 0)*m(2, 2)), scale*(m(0, 0)*m(2, 2) - m(0, 2)*m(2, 0)), scale*(m(0, 2)*m(1, 0) - m(0, 0)*m(1, 2)),
							scale*(m(1, 0)*m(2, 1) - m(1, 1)*m(2, 0)), scale*(m(0, 1)*m(2, 0) - m(0, 0)*m(2, 1)), scale*(m(0, 0)*m(1, 1) - m(0, 1)*m(1, 0)));
	}

} // Namespace mw.
