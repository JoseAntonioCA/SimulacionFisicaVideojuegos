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
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel) :
		pose(physx::PxTransform(Pos.x, Pos.y, Pos.z)), vel(Vel), acel(Acel), damping(Damping), constantAcel(ConstantAcel), toerase(false) {
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(0.5f)), &pose, Vector4(1, 0, 0, 1));
		RegisterRenderItem(renderItem);
	}
	~Particle() {
		if (renderItem) {
			DeregisterRenderItem(renderItem);
			delete renderItem;
			renderItem = nullptr;

		}
	}

	void setAcelY(float acelY) {
		acel.y = acelY;
	}

	Vector3 getPos() {
		return pose.p;
	}
	// Método para marcar la partícula para eliminación
	void setToErase(bool value) {
		toerase = value;
	}

	// Método para comprobar si la partícula está marcada para eliminación
	bool toErase() const {
		return toerase;
	}

	virtual void integrate(double time) {
		//actualizar pos y vel de la particula de forma constante
		pose.p = pose.p + (vel * time);
	}
	virtual void integrateAcelerated(double time) {
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
protected:
	Vector3 vel;
	Vector3 acel;
	bool constantAcel;
	double damping;
	physx::PxTransform pose;
	RenderItem* renderItem;

	bool toerase;

	//para el damping poner 0.98 para evitar problemas de desaceleracion brusca
};

