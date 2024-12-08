#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "ForceGenerator.h"
#include "Particle.h"

class ForceRegistry
{
public:
	ForceRegistry(){}
	void addRegistry(Particle* p, ForceGenerator* fg) {
		registries.push_back({ p, fg });
	}

	void updateForces(double dt) {
		for (ForceRegistration & r: registries) {
			r.fg->applyForce(r.p);
			r.fg->update(dt);
		}
	}

private:
	struct ForceRegistration {
		Particle* p;
		ForceGenerator* fg;
	};
	std::vector<ForceRegistration> registries;
};

