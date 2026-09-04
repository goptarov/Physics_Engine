#include "core/Force.hpp"
#include "core/Body.hpp"
#include "Integrators/Integrator.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

#define SCALE_FACTOR 2e-9
#define centerX 600.f
#define centerY 400.f

int main(int argc, char *argv[]) {

	static Euler integrator;

	//RenderWindow is a special window for rendering (derived from the Window class)
	sf::RenderWindow window(sf::VideoMode({1200, 800}), "Physics engine");;
	window.setFramerateLimit(140);

	Vector2 obj1Pos = Vector2(0, 0);
	Vector2 obj1Vel = Vector2(0, 0);
	Vector2 obj2Pos = Vector2(1.495978707e11, 0);
	Vector2 obj2Vel = Vector2(0, 29.78e3);
	//Vector2 obj2Vel = Vector2(0, 0);

	Body *obj1 = new Body(1.988416e30, 6.957e8, obj1Pos, obj1Vel);
	Body *obj2 = new Body(5.9722e24, 6.371e6, obj2Pos, obj2Vel);

	//note that objn will not change when bodies[] changes
	std::vector<Body> bodies;
	bodies.push_back(*obj1);
	bodies.push_back(*obj2);

	std::vector<std::unique_ptr<Force>> forces;
	forces.push_back(std::make_unique<Gravity>());



	sf::CircleShape sun(bodies[0].getRadius() / 2e7);
	sf::CircleShape earth(bodies[1].getRadius() / 1e6);

	sun.setOrigin(bodies[0].getRadius() / 2e7, bodies[0].getRadius() / 2e7);
	earth.setOrigin(bodies[1].getRadius() / 1e6, bodies[1].getRadius() / 1e6);

	sun.setFillColor(sf::Color::Yellow);
	earth.setFillColor(sf::Color::Blue);


	//We must keep every step evaluate based on the same constant time(dt) in order to avoid errors due to CPU scheduling that
	//would appear in a while(runTime < simulationTime) approach. The update happens in the Integrator's step() method
	double dt = 3600.0;
	int numSteps = 8760;

	sleep(1);

	for (int step = 0; step < numSteps && window.isOpen(); ++step) {

		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}

		std::cout << "Object1: Position: " << bodies[0].getPosition().toString() << "Velocity: " << bodies[0].getVelocity().toString() << std::endl;
		std::cout << "Object2: Position: " << bodies[1].getPosition().toString() << "Velocity: " << bodies[1].getVelocity().toString() << std::endl;

		//Firstly compute every object's net force
		std::vector<Vector2> netForces = computeNetForces(bodies, forces);
		//Then execute the step
		integrator.step(bodies, netForces, dt);


		window.clear(sf::Color::Black);

		sun.setPosition({
			centerX + static_cast<float>(bodies[0].getPosition().x * SCALE_FACTOR),
			centerY + static_cast<float>(bodies[0].getPosition().y * SCALE_FACTOR)});
		earth.setPosition({
			centerX + static_cast<float>(bodies[1].getPosition().x * SCALE_FACTOR),
			centerY + static_cast<float>(bodies[1].getPosition().y * SCALE_FACTOR)});


		window.draw(sun);
		window.draw(earth);

		window.display();
	}
}
