#pragma once
#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>


using namespace physx;

enum FormaParticula {Cubo, Esfera, Plano};

class Particle
{
public:
	Particle(FormaParticula Forma, Vector3 Pos, Vector3 Vel, Vector3 Acel, bool ConstantAcel, bool CanHaveAccForce, bool Simulado, float Radius, float Masa, float Gravedad, double Damping, double LifeTime, float VelR, float VelS) :
		pose(physx::PxTransform(Pos.x, Pos.y, Pos.z)), vel(Vel), acel(Acel), constantAcel(ConstantAcel), canHaveAccForce(CanHaveAccForce), simulado(Simulado),
		radius(Radius), masa(Masa), gravedad(Gravedad), damping(Damping), lifeTime(LifeTime), velReal(VelR), velSim(VelS),
		accumulatedForce(Vector3 (0,0,0)), toerase(false) {

		if (simulado) {
			masa = masa * powf(velReal / velSim, 2);
			gravedad = gravedad * powf(velSim / velReal, 2);
			vel = vel * velSim;
		}
		else {
			vel = vel * velReal;
		}

		switch (Forma)
		{
		case Cubo:
			renderItem = new RenderItem(CreateShape(PxBoxGeometry(radius, radius, radius)), &pose, Vector4(1, 0, 0, 1));
			break;
		case Esfera:
			renderItem = new RenderItem(CreateShape(PxSphereGeometry(radius)), &pose, Vector4(1, 0, 0, 1));
			break;
		case Plano:
			//renderItem = new RenderItem(CreateShape(PxPlaneGeometry()), &pose, Vector4(1, 0, 0, 1));
			renderItem = new RenderItem(CreateShape(PxBoxGeometry(radius, 0.001, radius)), &pose, Vector4(1, 0, 0, 1));

			break;
		default:
			break;
		}


		setAcelY(gravedad * -1);
		//std::cout << "particula creada";
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

	Vector3 getVel() {
		return vel;
	}

	float getVelR() {
		return velReal;
	}

	float getVelS() {
		return velSim;
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

		if (canHaveAccForce)
			acel = accumulatedForce / masa;

		lifeTime -= time;
		if (lifeTime <= 0.0f)
		{
			toerase = true;
		}
		if (constantAcel) {
			vel = (vel /** powf(damping, time)*/ + (time * acel))/** powf(damping, time)*/;
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
	Vector3 vel; //Velocidad de la particula
	Vector3 acel; //Aceleracion de la particula, si se aplican fuerzas acumuladas, esta se ve modificada por la formula a = F*m
	Vector3 accumulatedForce; //Fuerza acumulada de la particula
	bool constantAcel; //Determina si se puede usar aceleracion constante o en cambio se usara el Damping

	bool canHaveAccForce; //Determina si se pueden usar fuerzas acumuladas o no

	//para el damping poner 0.98 para evitar problemas de desaceleracion brusca
	double damping; //Variable que hace que la particula frene/desacelere de manera mas realista
	float radius; //Radio del tamanyo de la particula (De momento son todas esferas
	float masa; //Masa de la particula
	float gravedad; //Gravedad que le aplicamos a la particula y que afecta al eje Y de la aceleracion, si no se usan fuerzas acumuladas

	physx::PxTransform pose; //Posicion de la particula
	RenderItem* renderItem; //Render de la particula

	bool toerase; //Determina si la particula debe ser eliminada o no

	double lifeTime; //Tiempo de vida de la particula

	//Variables para la simulacion
	bool simulado; //Determina si la velocidad y la gravedad deberan de ser simuladas o no

	float velReal; //Velocidad real
	float velSim; //Velocidad simulada

};

