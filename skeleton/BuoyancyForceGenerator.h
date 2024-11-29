#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class BuoyancyForceGenerator : public ForceGenerator
{
public:
	BuoyancyForceGenerator(float h, float V, float d) : height(h), volume(V), liquid_density(d) {
		Vector3 initialPosition(0, 30, 0);
		Vector3 initialVel(0, 0, 0);
		Vector3 initialAcel(0, 0, 0);


		float masa = 0;
		float velReal = 1;
		float velSim = 1;
		liquid_particle = new Particle(Plano, initialPosition, initialVel, initialAcel, true, false, false, 10, masa, 0, 0.98, 100, velReal, velSim);
	}

	virtual void applyForce(Particle* particle) {
		float h = particle->getPos().y;
		float h0 = liquid_particle->getPos().y;


		Vector3 force(0, 0, 0);
		float immersed = 0.0f;

		if (h - h0 > height * 0.5f) {
			immersed = 0.0f;
		}
		else if (h0 - h > height * 0.5f) {
			//Totally immersed
			immersed = 1.0f;
		}
		else {
			immersed = (h0 - h) / height + 0.5f;
		}
		force.y = liquid_density * volume * immersed * 9.8f;

		particle->addForce(force);
	}

	void update(double deltaTime) {}
	void update2(Vector3 v, float Kplus) {}
protected:
	float height;
	float volume;
	float liquid_density;
	float gravity = 9.8f;

	Particle* liquid_particle;
};

