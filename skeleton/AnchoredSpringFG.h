#pragma once
#include "SpringForceGenerator.h"
#include "core.hpp"

class AnchoredSpringFG : public SpringForceGenerator
{
public:
	AnchoredSpringFG(double K, double Resting, const Vector3& Anchor_pos) : SpringForceGenerator(Vector3(0,0,0), nullptr, K, Resting){

	}

	~AnchoredSpringFG() {

	}


};

