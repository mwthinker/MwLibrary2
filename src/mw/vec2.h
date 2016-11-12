#ifndef MW_VEC2_H
#define MW_VEC2_H

#include <cmath>

namespace mw {	

	template <typename T>
	class Vec2 {
	public:
		T x_, y_;

		Vec2() {
		}
		
		Vec2(T x, T y) : x_(x), y_(y) {
		}

		Vec2 operator*(T scale) const {
			return Vec2(x_*scale, y_*scale);
		}

		Vec2 operator/(T scale) const {
			return Vec2(x_ / scale, y_ / scale);
		}

		Vec2 operator+(Vec2 other) const {
			return Vec2(x_ + other.x_, y_ + other.y_);
		}

		Vec2 operator-(Vec2 other) const {
			return Vec2(x_ - other.x_, y_ - other.y_);
		}

		Vec2 operator-() const {
			return Vec2(-x_, -y_);
		}

		const Vec2& operator*=(T scale) {
			x_ *= scale;
			y_ *= scale;
			return *this;
		}

		const Vec2& operator/=(T scale) {
			x_ /= scale;
			y_ /= scale;
			return *this;
		}

		const Vec2& operator+=(Vec2 v) {
			x_ += v.x_;
			y_ += v.y_;
			return *this;
		}

		const Vec2& operator-=(Vec2 v) {
			x_ -= v.x_;
			y_ -= v.y_;
			return *this;
		}

		T operator*(Vec2 v) const {
			return x_*v.x_ + y_*v.y_;
		}

		T operator[](unsigned int nbr) const {
			switch (nbr) {
				case 0:
					return x_;
				default:
					return y_;
			}
		}

		T& operator[](unsigned int nbr) {
			switch (nbr) {
				case 0:
					return x_;
				default:
					return y_;
			}
		}

		T magnitude() const {
			return std::sqrt(x_*x_ + y_*y_);
		}

		T magnitudeSquared() const {
			return x_*x_ + y_*y_;
		}

		Vec2 normalize() const {
			return Vec2(x_, y_) / magnitude();
		}

		T angle() const {
			return std::atan2(y_, x_);
		}

		Vec2 rotate(T angle) const {
			return Vec2(x_ * std::cos(angle) - y_ * std::sin(angle), y_ * std::cos(angle) + x_ * std::sin(angle));
		}

		Vec2 projectOn(Vec2 v) const {
			return *(this)*v / (v*v)*v;
		}
	};

	template <typename T>
	Vec2<T> operator*(T scale, Vec2<T> v) {
		return v * scale;
	}

} // mw.
	
#endif // MW_VEC2_H
