#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "ForceGenerator.h"
#include "SolidoRigido.h"

class ForceRegistrySD
{
public:
	ForceRegistrySD() {}
	void addRegistry(SolidoRigido* sd, ForceGenerator* fg) {
		registries.push_back({ sd, fg });
	}

	void updateForces(double dt) {
		for (ForceRegistrationSD& r : registries) {
			r.fg->applyForce(r.sd);
			r.fg->update(dt);
		}
	}

private:
	struct ForceRegistrationSD {
		SolidoRigido* sd;
		ForceGenerator* fg;
	};
	std::vector<ForceRegistrationSD> registries;
};