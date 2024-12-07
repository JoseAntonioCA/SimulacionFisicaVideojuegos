#pragma once
#include "ForceGenerator.h"


class WhirlwindForceGenerator : public ForceGenerator
{
public:
	WhirlwindForceGenerator() {}
	WhirlwindForceGenerator(Vector3 Center, float K) : center(Center), k(K) {}

	virtual void applyForce(Particle* particle) override {
		Vector3 direction = particle->getPos() - center;
		float distance = direction.magnitude();
		if (distance == 0) return;  // Evita la división por cero en el centro
		Vector3 tangentialVel = Vector3(-direction.z, 0, direction.x).getNormalized() * k * distance;
		Vector3 force = tangentialVel - particle->getVel();
		particle->addForce(force);
	}
	virtual void applyForce(SolidoRigido* sd) override {
		Vector3 direction = sd->getPos() - center;
		float distance = direction.magnitude();
		if (distance == 0) return;  // Evita la división por cero en el centro
		Vector3 tangentialVel = Vector3(-direction.z, 0, direction.x).getNormalized() * k * distance;
		Vector3 force = tangentialVel - sd->getVel();
		sd->getRigidDynamic()->addForce(force);
	}
	void update(double deltaTime) {}
	void update2(Vector3 v, float f) {}
private:
	Vector3 center;
	float k;
};

