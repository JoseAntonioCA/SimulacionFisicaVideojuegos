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
//		if (distance == 0) return;  // Evita la divisi�n por cero en el centro
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
    ExplosionForceGenerator(const Vector3& center, float K, float initialRadius, float decayRate)
        : center(center), K(K), initialK(K), radius(initialRadius), decayTime(decayRate), timeElapsed(0) {}

    virtual void applyForce(Particle* particle) override {
        Vector3 direction = particle->getPos() - center;
        float distance = direction.magnitude();
        if (distance < radius && distance > 0) { // Asegurarse de que est� dentro del radio y evitar divisi�n por cero
            float decayFactor = exp(-timeElapsed / decayTime);
            Vector3 force = (K / (distance * distance)) * direction * decayFactor;
            particle->addForce(force);
        }
        //K = initialK * exp(-timeElapsed / decayRate);
    }

    void update(float deltaTime) {
        timeElapsed += deltaTime;
        //radius += 2 * deltaTime; // Expansi�n del radio
    }

private:
    Vector3 center;
    float K; // Constante de intensidad de la explosi�n, actualizada
    float initialK; // Almacena el valor inicial de K
    float radius;
    float decayTime; // constante de tiempo de la explosi�n
    float timeElapsed; // Tiempo acumulado desde el inicio de la explosi�n

};
