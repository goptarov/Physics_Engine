#pragma once

#include "Vector2.hpp"
#include "Body.hpp"

class Force {

	public:

	virtual ~Force() = default;
	virtual Vector2 compute (const Body& bodyA, const Body& bodyB) const;
};


class Gravity : public Force {

	double G = 6.674e-11;

	public:

	Gravity() = default;

	Vector2 compute (const Body& bodyA, const Body& bodyB) const override {
		Vector2 delta = bodyB.getPosition() - bodyA.getPosition();
		double constFactor = G * bodyA.getMass() * bodyB.getMass();

		return delta * (constFactor / delta.lengthSquared());
	}

};