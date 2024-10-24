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
	Proyectile(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel, float Radius, bool Simulado, float Masa, float Gravedad, float VelR, float VelS) :
		simulado(Simulado), masa(Masa), gravedad(Gravedad), velReal(VelR), velSim(VelS),
		Particle(Pos, Vel, Acel,Damping, ConstantAcel, Radius) {

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

	virtual void integrate(double time) override {
		//actualizar pos y vel de la particula de forma constante
		pose.p = pose.p + (vel * time);
	}

	virtual void integrateAcelerated(double time) override {
		lifeTime -= time;
		if (lifeTime <= 0.0f)
		{
			toerase = true;
		}
		if (constantAcel) {
			vel = vel + (time * acel);
			//actualizar acel de la particula de forma constante
			pose.p = pose.p + (vel * time);
		}
		else {
			vel = vel * powf(damping, time);
			//actualizar acel de la particula de forma no constante
			pose.p = pose.p + (vel * time);
		}
	}
private:
	bool simulado;

	float velReal;
	float velSim;
	float masa;
	float gravedad;
};