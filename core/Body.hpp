#pragma once

#include "math_tools/Vector2.hpp"

class Body {

	double mass;
	double radius; //all objects are circles for now
	Vector2 position;
	Vector2 velocity;

	public:

	Body() = default;
	Body(double _mass, double _radius, Vector2 _position, Vector2 _velocity) : mass(_mass), radius(_radius), position(_position), velocity(_velocity) {}

	void setMass(double mass) {
		this->mass = mass;
	}
	void setRadius(double radius) {
		this->radius = radius;
	}
	void setPosition(Vector2 position) {
		this->position = position;
	}
	void setVelocity(Vector2 velocity) {
		this->velocity = velocity;
	}


	double getMass() const {
		return mass;
	}
	double getRadius() const {
		return radius;
	}
	Vector2 getPosition() const {
		return position;
	}
	Vector2 getVelocity() const {
		return velocity;
	}
};
