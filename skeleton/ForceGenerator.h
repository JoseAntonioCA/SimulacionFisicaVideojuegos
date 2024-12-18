#pragma once
//
//#include "Particle.h"
//#include "SolidoRigido.h"

//class Particle;
//class SolidoRigido;
#include "Particle.h"
#include "SolidoRigido.h"

class ForceGenerator
{
public:
	ForceGenerator() : enabeled(true) {}

	~ForceGenerator() {
		delete this;
	}

	virtual void applyForce(Particle* particle) = 0;
	virtual void applyForce(SolidoRigido* sd) = 0;
	virtual void update(double deltaTime) = 0;
	virtual void update2(Vector3 v, float f) = 0;

	void SwitchOnOff() {
		enabeled = !enabeled;
	}

	void setEnabeled(bool E) {
		enabeled = E;
	}

protected:
	bool enabeled; //variable que determina si en unos sistemas determinados se aplican las fuerzas o no.

};

