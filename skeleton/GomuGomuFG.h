#pragma once
#include "ForceGenerator.h"


class GomuGomuFG : public ForceGenerator
{
public:
	GomuGomuFG() {}
	GomuGomuFG(Vector3 Origen, Particle* Other, SolidoRigido* OtherSD, double Kf, double Resting_length) : origen(Origen), K(Kf), resting_length(Resting_length), other(Other), otherSD(OtherSD) {}

	virtual void applyForce(Particle* particle) override {
		Vector3 relative_pos_vector;
		if (other != nullptr) {
			relative_pos_vector = other->getPos() - particle->getPos();

		}
		else
			relative_pos_vector = particle->getPos() - origen;

		const float length = relative_pos_vector.normalize();

		if (length > resting_length) {
			Vector3 force;

			const float delta_x = length - resting_length;

			force = K * delta_x * relative_pos_vector;
			particle->addForce(force);
		}
	}
	virtual void applyForce(SolidoRigido* sd) override {
		Vector3 relative_pos_vector;
		if (other != nullptr) {
			relative_pos_vector = other->getPos() - sd->getPos();

		}
		else
			relative_pos_vector = sd->getPos() - origen;

		const float length = relative_pos_vector.normalize();

		if (length > resting_length) {
			Vector3 force;

			const float delta_x = length - resting_length;

			force = K * delta_x * relative_pos_vector;
			sd->getRigidDynamic()->addForce(force);
		}
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
	SolidoRigido* otherSD;
};
