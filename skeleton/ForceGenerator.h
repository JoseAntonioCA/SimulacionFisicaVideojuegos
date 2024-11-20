#pragma once

#include "Particle.h"

class ForceGenerator
{
public:
	ForceGenerator(){}

	~ForceGenerator() {
		delete this;
	}

	virtual void applyForce(Particle* particle) = 0;
	virtual void update(double deltaTime) = 0;

};
