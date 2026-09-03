
#include "Force.hpp"
#include "Body.hpp"
#include "Integrator.hpp"
#include "computeNetForce.hpp"
#include <iostream>


int main() {

	static Euler integrator;

	Vector2 obj1Pos = Vector2(0, 0);
	Vector2 obj1Vel = Vector2(0, 0);
	Vector2 obj2Pos = Vector2(1.495978707e11, 0);
	Vector2 obj2Vel = Vector2(0, 29.78e3);

	Body *obj1 = new Body(1.988416e30, 6.957e8, obj1Pos, obj1Vel);
	Body *obj2 = new Body(5.9722e24, 6.371e6, obj2Pos, obj2Vel);

	//note that objn will not change when bodies[] changes
	std::vector<Body> bodies;
	bodies.push_back(*obj1);
	bodies.push_back(*obj2);

	std::vector<std::unique_ptr<Force>> forces;
	forces.push_back(std::make_unique<Gravity>());

	//We must keep every step evaluate based on the same constant time(dt) in order to avoid errors due to CPU scheduling that
	//would appear in a while(runTime < simulationTime) approach. The update happens in the Integrator's step() method
	double dt = 0.00001;
	int numSteps = 10000;

	for (int step = 0; step < numSteps; step ++) {
		std::cout << "Object1: Position: " << bodies[0].getPosition().toString() << "Velocity: " << bodies[0].getVelocity().toString() << std::endl;
		std::cout << "Object2: Position: " << bodies[1].getPosition().toString() << "Velocity: " << bodies[1].getVelocity().toString() << std::endl;

		//Firstly compute every object's net force
		std::vector<Vector2> netForces = computeNetForces(bodies, forces);

		//Then execute the step
		integrator.step(bodies, netForces, dt);
	}
}
