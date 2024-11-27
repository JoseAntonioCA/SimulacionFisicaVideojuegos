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
	SpringForceGenerator(Vector3 Origen, Particle* Other, double Kf, double Resting_length) : origen(Origen), K(Kf), resting_length(Resting_length), other(Other) {}

	virtual void applyForce(Particle* particle) override {
		Vector3 relative_pos_vector;
		if (other != nullptr) {
			relative_pos_vector = other->getPos() - particle->getPos();
			
		}
		else
			relative_pos_vector = particle->getPos() - origen;


		Vector3 force;

		const float length = relative_pos_vector.normalize();
		const float delta_x = length - resting_length;

		force = K * delta_x * relative_pos_vector;
		particle->addForce(force);
	}

	void update(double deltaTime) {}
	void update2(Vector3 v, float Kplus) {
		K += Kplus;
	}
protected:
	Vector3 origen;
	double K;
	double resting_length;
	Particle* other;
};