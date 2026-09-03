#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "math_tools/Vector2.hpp"
#include "core/Body.hpp"
#include "core/Force.hpp"

//Since Force is an abstract class we need to send a vector of unique pointers to Force (otherwise each force will be an empty Force instead of Gravity for example).
std::vector<Vector2> computeNetForces(const std::vector<Body> &bodies, const std::vector<std::unique_ptr<Force>> &forces) {

	std::vector<Vector2> netForces(bodies.size());

	for (size_t i = 0; i < bodies.size(); i++) {
		for (size_t j = i + 1; j < bodies.size(); j++) {
			for (const auto& force : forces) {
				Vector2 f = force->compute(bodies[i], bodies[j]);
				//Newton's third law states that if 2 bodies exert forces on each other, these forces have equal magnitudes but opposite directions
				netForces[i] += f;
				netForces[j] -= f;
			}
		}
	}

	return netForces;
};