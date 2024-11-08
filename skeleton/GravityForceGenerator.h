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
	GravityForceGenerator(float Gravity, bool Simulado) : gravity(0, -Gravity, 0), simulado(Simulado) {}

	virtual void applyForce(Particle* particle) override {
		if (simulado) {
			gravity = gravity * powf(particle->getVelS() / particle->getVelR(), 2);
		}
		Vector3 force = gravity * particle->getMasa();
		particle->addForce(force);
	}
	void update(float deltaTime) {}
private:
	Vector3 gravity;
	bool simulado;
};

