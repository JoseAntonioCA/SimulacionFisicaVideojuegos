#pragma once
#include "SpringForceGenerator.h"
#include "core.hpp"

class AnchoredSpringFG : public SpringForceGenerator
{
public:
	AnchoredSpringFG(double K, double Resting, const Vector3& Anchor_pos) : SpringForceGenerator(Vector3(0,0,0), nullptr, nullptr, K, Resting){
		float masa = 15.0f;
		float velReal = 10.0f;
		float velSim = 5.0f;
		other = new Particle(Esfera, Anchor_pos, Vector3(0, -1, 0), Vector3(0, 0, 0), true, true, false, 1.5f, masa, 9.8f, 0.98, 100, velReal, velSim);
	}

	~AnchoredSpringFG() {
		delete other;
	}

	Particle* returnOther() {
		return other;
	}
};

