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
	ForceGenerator(){}

	~ForceGenerator() {
		delete this;
	}

	virtual void applyForce(Particle* particle) = 0;
	virtual void applyForce(SolidoRigido* sd) = 0;
	virtual void update(double deltaTime) = 0;
	virtual void update2(Vector3 v, float f) = 0;

};

