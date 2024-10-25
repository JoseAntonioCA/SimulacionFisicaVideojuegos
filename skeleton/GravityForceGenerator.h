#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <list>
#include <random>
#include "ForceGenerator.h"
#include "Particle.h"


class GravityForceGenerator : public ForceGenerator
{
public:
	GravityForceGenerator() {}
	GravityForceGenerator(float Gravity) : gravity(0, Gravity, 0) {}

	virtual void applyForce(Particle* particle, Vector3 gravity) override {
		Vector3 force = gravity * particle->getMasa();
		particle->addForce(gravity);
	}

	virtual void applyForce(Particle* particle) override {
		Vector3 force = gravity * particle->getMasa();
		particle->addForce(gravity);
	}
private:
	Vector3 gravity;
};

