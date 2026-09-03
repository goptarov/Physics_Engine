#pragma once

#include <vector>
#include "Force.hpp"
#include "computeNetForce.hpp"

//The integrator updates every object based on its net force at every step.
class Integrator {

	public:

	virtual ~Integrator() = default;
	virtual void step(std::vector<Body> &bodies, std::vector<Vector2> &netForces, double dt) = 0;
};

class Euler : public Integrator {

	public:

	void step(std::vector<Body> &bodies, std::vector<Vector2> &netForces, double dt) override {

		for (int i = 0; i < bodies.size(); i++) {
			std::cout << "NetForce " << i << netForces[i].toString() <<std::endl;
			Vector2 acceleration = netForces[i] / bodies[i].getMass();

			bodies[i].setVelocity(bodies[i].getVelocity() + acceleration * dt);
			bodies[i].setPosition(bodies[i].getPosition() + bodies[i].getVelocity() * dt);
		}
	}
};
