
#include "Force.hpp"
#include "Body.hpp"
#include "Integrator.hpp"
#include "computeNetForce.hpp"
#include <iostream>


int main() {

	static Euler integrator;

	Vector2 obj1Pos = Vector2(10, 10);
	Vector2 obj1Vel = Vector2(0, 0);
	Vector2 obj2Pos = Vector2(-10, -10);
	Vector2 obj2Vel = Vector2(0, 0);

	Body *obj1 = new Body(4, 2, obj1Pos, obj1Vel);
	Body *obj2 = new Body(4, 2, obj2Pos, obj2Vel);

	std::vector<Body> bodies;
	bodies.push_back(*obj1);
	bodies.push_back(*obj2);

	std::vector<Force*> forces;

	forces.push_back(new Gravity());

	//We must keep every step evaluate based on the same constant time(dt) in order to avoid errors due to CPU scheduling that
	//would appear in a while(runTime < simulationTime) approach. The update happens in the Integrator's step() method
	double dt = 0.01;
	int numSteps = 400;

	for (int step = 0; step < numSteps; step += dt) {
		std::cout << "Object1: Position: " << obj1Pos.toString() << "Velocity: " << obj1Vel.toString() << std::endl;
		std::cout << "Object2: Position: " << obj2Pos.toString() << "Velocity: " << obj2Vel.toString() << std::endl;

		//Firstly compute every object's net force
		std::vector<Vector2> netForces = computeNetForces(bodies, forces);

		//Then execute the step
		integrator.step(bodies, netForces, dt);
	}
}
