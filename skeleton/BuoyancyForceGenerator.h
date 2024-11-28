#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class BuoyancyForceGenerator : public ForceGenerator
{
public:
	BuoyancyForceGenerator(float h, float V, float d) : height(h), volume(V), liquid_density(d) {

	}

	virtual void applyForce(Particle* particle) {
		float h = particle->getPos().y;
		//float h0 = liquid_particle->getPos().y;
		float h0 = 30.0f;


		Vector3 force(0, 0, 0);
		float immersed = 0.0f;

		if (h - h0 > height * 0.5f) {
			immersed = 0.0f;
		}
		else if (h0 - h > height * 0.5f) {
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

