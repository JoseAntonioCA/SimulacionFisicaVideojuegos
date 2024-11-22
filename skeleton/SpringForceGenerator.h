#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <list>
#include <random>
#include "ForceGenerator.h"
#include "Particle.h"


class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator() {}
	SpringForceGenerator(Vector3 Origen, float Kf) : origen(Origen), K(Kf) {}

	virtual void applyForce(Particle* particle) override {
		Vector3 direction = particle->getPos() - origen;

		Vector3 force = -K * direction;
		particle->addForce(force);
	}

	void update(double deltaTime) {}
private:
	Vector3 origen;
	float K;
};