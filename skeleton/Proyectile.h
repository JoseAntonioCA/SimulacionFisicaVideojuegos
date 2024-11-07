#pragma once
#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>
#include "Particle.h"

using namespace physx;
class Proyectile : public Particle
{
public:
	Proyectile(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel, float Radius, float Masa, float Gravedad, bool Simulado, float VelR, float VelS) :
		simulado(Simulado), velReal(VelR), velSim(VelS),
		Particle(Pos, Vel, Acel,Damping, ConstantAcel, Radius, Masa, Gravedad) {

		if (simulado) {
			masa = masa * powf(velReal / velSim, 2);
			gravedad = gravedad * powf(velSim / velReal, 2);
			vel = vel * velSim;
		}
		else {
			vel = vel * velReal;
		}
		setAcelY(gravedad * -1);
	}
	~Proyectile() {
		if (renderItem) {
			DeregisterRenderItem(renderItem);
		}
	}
private:
	bool simulado;

	float velReal;
	float velSim;
};