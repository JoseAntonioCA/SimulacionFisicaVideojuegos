#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <list>
#include <random>
#include "ForceGenerator.h"
#include "Particle.h"


//class ExplosionForceGenerator : public ForceGenerator
//{
//public:
//	ExplosionForceGenerator() {}
//	ExplosionForceGenerator(Vector3 Center, float K) : center(Center), k(K) {}
//
//	virtual void applyForce(Particle* particle) override {
//		Vector3 direction = particle->getPos() - center;
//		float distance = direction.magnitude();
//		if (distance == 0) return;  // Evita la división por cero en el centro
//		Vector3 tangentialVel = Vector3(-direction.z, 0, direction.x).getNormalized() * k * distance;
//		Vector3 force = tangentialVel - particle->getVel();
//		particle->addForce(force);
//	}
//private:
//	Vector3 center; //Centro Explosion
//	float k; //Intensidad Explosion
//	float t; //Constante tiempo de la explosion
//	float initRadius; //Radio inicial de la explosion
//	float expSpeed; //Velocidad explosion
//	float startTime; //Tiempo inicio explosion
//};




class ExplosionForceGenerator : public ForceGenerator
{
public:
    ExplosionForceGenerator(const Vector3& center, float K, float initialRadius, float T)
        : center(center), K(K), radius(initialRadius), T(T), timeElapsed(0), speedRange(300) {}

    virtual void applyForce(Particle* particle) override {

        Vector3 direction = particle->getPos() - center;
        float r = direction.magnitude();

        Vector3 force = Vector3(0, 0, 0);
        if (r < radius) {
            force = (K / pow(r, 2)) * direction * exp(-(timeElapsed / T));
        }

        particle->addForce(force);
    }

    void update(double deltaTime) {
        timeElapsed += (deltaTime/100);
        radius += speedRange; //Aqui se supone que la explosion se expande por el aumento del radio de alcance
    }

private:
    Vector3 center;
    float K; // Constante de intensidad de la explosión, actualizada
    float radius; //Radio de alcance de la explosion
    float T; // Constante de tiempo de la explosión
    float speedRange; // Velocidad que aumenta el radio de alcance
    float timeElapsed; // Tiempo que ha pasado desde el inicio de la explosion

};
