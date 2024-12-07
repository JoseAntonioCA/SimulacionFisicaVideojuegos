#pragma once
#include "ForceGenerator.h"


class WindForceGenerator : public ForceGenerator
{
public:
	WindForceGenerator() {}
	WindForceGenerator(Vector3 Velocity, float K1, float K2) : velocity(Velocity), k1(K1), k2(K2) {}

	virtual void applyForce(Particle* particle) override {
		Vector3 relativeVel = velocity - particle->getVel();
		Vector3 force = k1* relativeVel + k2 * relativeVel.magnitude() * relativeVel;
		particle->addForce(force);
	}
	virtual void applyForce(SolidoRigido* sd) override {
		Vector3 relativeVel = velocity - sd->getVel();
		Vector3 force = k1 * relativeVel + k2 * relativeVel.magnitude() * relativeVel;
		sd->getRigidDynamic()->addForce(force);
	}
	void update(double deltaTime) {}
	void update2(Vector3 v, float f) {}
private:
	Vector3 velocity;
	float k1;
	float k2;
};

