#pragma once
#include <cmath>
#include <iostream>

struct Vector2 {
	double x = 0, y = 0;

	Vector2() = default;
	Vector2(const double _x, const double _y) : x(_x), y(_y) {}

	std::string toString() {
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}

	//Vector operations
	Vector2 operator+(const Vector2 &other) const { return {x + other.x, y + other.y}; }
	Vector2 operator-(const Vector2 &other) const { return {x - other.x, y - other.y}; }
	Vector2 operator*(const double scalar) const { return {x * scalar, y * scalar}; }
	Vector2 operator/(const double scalar) const { return {x / scalar, y / scalar}; }

	//Update operators
	Vector2& operator+=(const Vector2 &other) { return *this = *this + other; }
	Vector2& operator-=(const Vector2 &other) { return *this = *this - other; }

	double length() const { return std::sqrt(x * x + y * y); }
	double lengthSquared() const { return x * x + y * y; }
	//Scalar product
	double operator*(const Vector2 &other) const { return x * other.x + y * other.y; }

	//TODO?: Vector product

};
