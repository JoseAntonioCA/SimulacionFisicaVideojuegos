#pragma once

#include <cassert>
#include <cmath>
#include <ostream>

class Vector3D {
public:

	float x_;  // first coordinate
	float y_;  // second coordinate
	float z_;  // third coordinate

	Vector3D(const Vector3D& v) noexcept :
		x_(v.getX()), y_(v.getY()), z_(v.getZ()) {
	}

	Vector3D(Vector3D&& v) noexcept :
		x_(v.getX()), y_(v.getY()), z_(v.getZ()) {
	}

	Vector3D(float x, float y, float z) noexcept :
		x_(x), y_(y), z_(z) {
	}

	~Vector3D() {
	}

	// various getters
	inline float getX() const {
		return x_;
	}

	inline float getY() const {
		return y_;
	}

	inline float getZ() const {
		return z_;
	}

	// various setters
	inline void setX(float x) {
		x_ = x;
	}

	inline void setY(float y) {
		y_ = y;
	}

	inline void setZ(float z) {
		z_ = z;
	}

	inline void set(float x, float y, float z) {
		x_ = x;
		y_ = y;
		z_ = z;
	}

	inline void set(const Vector3D& v) {
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
	}

	// copy assignment
	inline Vector3D& operator=(const Vector3D& v) noexcept {
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
		return *this;
	}



	// length of the vector
	inline float magnitude() const {
		return sqrtf(powf(x_, 2) + powf(y_, 2) + powf(z_, 2));
	}

	// vector in the same direction of length 1
	inline Vector3D normalize() const {
		return *this / magnitude();
	}

	// counter clockwise rotation in a normal coordinate system, and
	// it is clockwise rotation if we work with a coordinate system
	// in which the vertical axe is flipped (it is like a mirror over
	// the horizontal axe) -- which the case when working with SDL.
	//
	Vector3D rotate(float degrees) const;

	// Computes the angle between 'this' and 'v'. The result is
	// between -180 and 180, and is such that the following holds:
	//
	//   this->rotate(angle).normalize() == v.normalize()
	//
	float angle(const Vector3D& v) const;

	// vector subtraction
	inline Vector3D operator-(const Vector3D& v) const {
		return Vector3D(x_ - v.x_, y_ - v.y_, z_ - v.z_);
	}

	// vector addition
	inline Vector3D operator+(const Vector3D& v) const {
		return Vector3D(x_ + v.x_, y_ + v.y_, z_ + v.z_);
	}

	// multiplication by constant (scaling)
	inline Vector3D operator*(float d) const {
		return Vector3D(x_ * d, y_ * d, z_ * d);
	}

	// division by constant (scaling)
	inline Vector3D operator/(float d) const {
		return Vector3D(x_ / d, y_ / d, z_ / d);
	}

	// scalar multiplication
	inline float operator *(const Vector3D& d) const {
		return d.x_ * x_ + d.y_ * y_ + d.z_ + z_;
	}

	inline bool inRange(float x0, float x2, float y0, float y1) {
		return x_ >= x0 && x_ <= x2 && y_ >= y0 && y_ <= y1;
	}
};

// needed for printing a value of type Vector2D with std::cout.
// The definition is in .cpp
std::ostream& operator<<(std::ostream& os, const Vector3D& v);
