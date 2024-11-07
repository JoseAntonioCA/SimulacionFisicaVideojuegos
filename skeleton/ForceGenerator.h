#pragma once

#include "Particle.h"

class ForceGenerator
{
public:
	ForceGenerator(){}

	~ForceGenerator() {
		delete this;
	}

	//virtual void applyForce(Particle* particle, Vector3 force) = 0;
	virtual void applyForce(Particle* particle) = 0;
	virtual void update(float deltaTime) = 0;

};

