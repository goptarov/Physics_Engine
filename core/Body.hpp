#pragma once

#include <SFML/Graphics.hpp>
#include <utility>
#include "math_tools/Vector2.hpp"

class Body {

	double mass;
	double radius; //all objects are circles for now
	Vector2 position;
	Vector2 velocity;

	//worth noting that shape has its own coordinates that live inside the window
	//making these two positions automatically sync would be a good design choice
	sf::CircleShape shape;

	public:

	Body() = default;
	Body(double _mass, double _radius, Vector2 _position, Vector2 _velocity, sf::CircleShape _shape) :
	mass(_mass), radius(_radius), position(_position), velocity(_velocity), shape(_shape) {}

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
	void setShape(sf::CircleShape shape) {
		this->shape = shape;
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
	sf::CircleShape& getShape() {
		return shape;
	}
};
