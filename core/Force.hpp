#pragma once

#include "math_tools/Vector2.hpp"
#include "Body.hpp"

class Force {

	public:

	virtual ~Force() = default;
	virtual Vector2 compute (const Body& bodyA, const Body& bodyB) const = 0;
};


class Gravity : public Force {

	double G = 6.674e-11; //m^3 * kg^-1 * s^-2
	//double G = 1; //AU
    //TODO: softening is standard practice in N-body simulators

	public:

	Vector2 compute (const Body& bodyA, const Body& bodyB) const override {

		Vector2 delta = bodyB.getPosition() - bodyA.getPosition();
		double constFactor = G * bodyA.getMass() * bodyB.getMass();
		Vector2 deltaNormed = delta / delta.length(); //only keep the direction component

		return deltaNormed * (constFactor / delta.lengthSquared());
	}

};