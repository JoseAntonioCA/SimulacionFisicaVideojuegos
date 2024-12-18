#pragma once
#include "ForceGenerator.h"


class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator() {}
	SpringForceGenerator(Vector3 Origen, Particle* Other, SolidoRigido* OtherSD, double Kf, double Resting_length) : origen(Origen), otherSD(OtherSD), K(Kf), resting_length(Resting_length), other(Other) {}

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
	virtual void applyForce(SolidoRigido* sd) override {
		Vector3 relative_pos_vector;
		if (otherSD != nullptr) {
			relative_pos_vector = otherSD->getPos() - sd->getPos();
		}
		else
			relative_pos_vector = origen - sd->getPos();


		Vector3 force;

		const float length = relative_pos_vector.normalize();
		const float delta_x = length - resting_length;

		force = K * delta_x * relative_pos_vector;
		sd->getRigidDynamic()->addForce(force);
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