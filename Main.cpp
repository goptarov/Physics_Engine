#include "core/Force.hpp"
#include "core/Body.hpp"
#include "Integrators/Integrator.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

#define SCALE_FACTOR 1
#define CENTERX 600.f
#define CENTERY 400.f
#define PARTICLE_MASS 1000000
#define PARTICLE_SIZE 5

int main(int argc, char *argv[]) {

	static Euler integrator;

	//RenderWindow is a special window for rendering (derived from the Window class)
	sf::RenderWindow window(sf::VideoMode({1200, 800}), "Physics engine");;
	window.setFramerateLimit(140);

	//note that objn will not change when bodies[] changes
	std::vector<Body> bodies;

	//forces are held in a vector in order to simplify adding new functions in the future
	std::vector<std::unique_ptr<Force>> forces;
	forces.push_back(std::make_unique<Gravity>());

	//We must keep every step evaluate based on the same constant time(dt) in order to avoid errors due to CPU scheduling that
	//would appear in a while(runTime < simulationTime) approach. The update happens in the Integrator's step() method
	double dt = 100;
	int numSteps = 100000;

	double particleCount = 0;

	for (int step = 0; step < numSteps && window.isOpen(); ++step) {

		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::MouseButtonPressed) {

				Vector2 newBodyPos = Vector2((sf::Mouse::getPosition(window).x - CENTERX) / SCALE_FACTOR , (sf::Mouse::getPosition(window).y - CENTERY) / SCALE_FACTOR);
				Vector2 newBodyVel = Vector2(0, 0); // Initially give no v0 to the created objects

				sf::CircleShape *particle = new sf::CircleShape(PARTICLE_SIZE / SCALE_FACTOR);

				particle->setOrigin(PARTICLE_SIZE, PARTICLE_SIZE); // sets the origin at the center of the particle instead of the top-left corner
				particle->setFillColor(sf::Color::Magenta);

				Body *newBody = new Body(PARTICLE_MASS, PARTICLE_SIZE, newBodyPos, newBodyVel, *particle);
				bodies.push_back(*newBody);

				particleCount++;
				std::cout << particleCount << " particles" << std::endl;
			}
		}

		//Firstly compute every object's net force
		std::vector<Vector2> netForces = computeNetForces(bodies, forces);
		//Then execute the step
		integrator.step(bodies, netForces, dt);

		window.clear(sf::Color::Black);

		for (size_t i = 0; i < bodies.size(); ++i) {
			bodies[i].getShape().setPosition({
				CENTERX + static_cast<float>(bodies[i].getPosition().x * SCALE_FACTOR),
				CENTERY + static_cast<float>(bodies[i].getPosition().y * SCALE_FACTOR)});
			window.draw(bodies[i].getShape());
		}

		window.display();
	}
}
