#include <cmath>

struct Vector2 {
	double x = 0, y = 0;

	Vector2() : x(0), y(0) {};
	Vector2(const double _x, const double _y) : x(_x), y(_y) {};

	//Vector operations
	Vector2 operator+(const Vector2 &other) const { return {x + other.x, y + other.y}; }
	Vector2 operator-(const Vector2 &other) const { return {x - other.x, y - other.y}; }
	Vector2 operator*(const double scalar) const { return {x * scalar, y * scalar}; }
	Vector2 operator*(const double scalar, const Vector2 &v) const { return v * scalar; } //Offers commutability
	Vector2 operator/(const double scalar) const { return {x / scalar, y / scalar}; }

	//Update operators
	Vector2& operator+=(const Vector2 &other) { return *this = *this + other; }
	Vector2& operator-=(const Vector2 &other) { return *this = *this - other; }

	double length() const { return std::sqrt(x * x + y * y); }
	//Scalar product
	double operator*(const Vector2 &other) const { return x * other.x + y * other.y; }

	//TODO?: Vector product

};