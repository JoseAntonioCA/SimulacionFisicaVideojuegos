#pragma once
#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

using namespace physx;

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel, bool Simulado, float Masa, float Gravedad, float VelR, float VelS) :
		pose(physx::PxTransform(Pos.x, Pos.y, Pos.z)), vel(Vel), acel(Acel), damping(Damping), constantAcel(ConstantAcel),
		simulado(Simulado), masa(Masa), gravedad(Gravedad), velReal(VelR), velSim(VelS) {
		
		if (simulado) {
			masa = masa * powf(velReal / velSim, 2);
			gravedad = gravedad * powf(velSim / velReal, 2);
			vel = vel * velSim;
		}
		else {
			vel = vel * velReal;
		}
		acel.y = gravedad * -1;
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(1)), &pose, Vector4(1, 0, 0, 1));
		RegisterRenderItem(renderItem);
	}
	~Particle() {
		DeregisterRenderItem(renderItem);
		delete renderItem;
	}
	void integrate(double time) {
		//actualizar pos y vel de la particula de forma constante
		pose.p = pose.p + (vel * time);
	}
	void integrateAcelerated(double time) {
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
		/*if (pose.p.y <= 0) {
			DeregisterRenderItem(renderItem);
			delete renderItem;
		}*/
	}
private:
	Vector3 vel;
	Vector3 acel;
	bool constantAcel;
	double damping;
	physx::PxTransform pose;
	RenderItem* renderItem;
	bool simulado;

	float velReal;
	float velSim;
	float masa;
	float gravedad;

	//para el damping poner 0.98 para evitar problemas de desaceleracion brusca
};

