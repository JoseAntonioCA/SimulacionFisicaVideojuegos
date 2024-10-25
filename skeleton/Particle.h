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
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel, float Radius, float Masa, float Gravedad) :
		pose(physx::PxTransform(Pos.x, Pos.y, Pos.z)), vel(Vel), acel(Acel), damping(Damping), constantAcel(ConstantAcel), radius(Radius), masa(Masa), gravedad(Gravedad),
		accumulatedForce(Vector3 (0,0,0)), toerase(false), lifeTime(2) {
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(radius)), &pose, Vector4(1, 0, 0, 1));

		setAcelY(gravedad * -1);
		std::cout << "particula creada";
	}
	~Particle() {
		if (renderItem) {
			DeregisterRenderItem(renderItem);
		}
	}

	void addForce(Vector3 force) {
		accumulatedForce += force;
	}

	void setAcelY(float acelY) {
		acel.y = acelY;
	}

	float getMasa() {
		return masa;
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
		if (masa <= 0.0f) return;

		//acel = accumulatedForce / masa;

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
		accumulatedForce = Vector3(0, 0, 0);
	}
protected:
	Vector3 vel;
	Vector3 acel;
	Vector3 accumulatedForce;
	bool constantAcel;
	double damping;
	float radius;
	float masa;
	float gravedad;

	physx::PxTransform pose;
	RenderItem* renderItem;

	bool toerase;

	double lifeTime;

	//para el damping poner 0.98 para evitar problemas de desaceleracion brusca
};

