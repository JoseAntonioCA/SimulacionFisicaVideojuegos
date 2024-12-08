#pragma once
#include "ForceGenerator.h"


class GravityForceGenerator : public ForceGenerator
{
public:
	GravityForceGenerator() {}
	GravityForceGenerator(float Gravity, bool Simulado) : gravity(0, -Gravity, 0), simulado(Simulado) {}

	virtual void applyForce(Particle* particle) override {
		if (simulado) {
			gravity = gravity * powf(particle->getVelS() / particle->getVelR(), 2);
		}
		Vector3 force;
		force = gravity * particle->getMasa();
		particle->addForce(force);
	}
	virtual void applyForce(SolidoRigido* sd) override {
		Vector3 force;
		force = gravity * sd->getMasa();
		sd->getRigidDynamic()->addForce(force, physx::PxForceMode::eFORCE);
	}
	void update(double deltaTime) {}
	void update2(Vector3 v, float f) {}
private:
	Vector3 gravity;
	bool simulado;
};

