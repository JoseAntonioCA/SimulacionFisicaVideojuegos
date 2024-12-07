#pragma once
#include "ForceGenerator.h"

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

    virtual void applyForce(SolidoRigido* sd) override {

        Vector3 direction = sd->getPos() - center;
        float r = direction.magnitude();

        Vector3 force = Vector3(0, 0, 0);
        if (r < radius) {
            force = (K / pow(r, 2)) * direction * exp(-(timeElapsed / T));
        }

        sd->getRigidDynamic()->addForce(force);
    }

    void update(double deltaTime) {
        timeElapsed += (deltaTime/100);
        radius += speedRange * timeElapsed; //Aqui se supone que la explosion se expande por el aumento del radio de alcance
    }
    void update2(Vector3 v, float f) {}

private:
    Vector3 center;
    float K; // Constante de intensidad de la explosión, actualizada
    float radius; //Radio de alcance de la explosion
    float T; // Constante de tiempo de la explosión
    float speedRange; // Velocidad que aumenta el radio de alcance
    float timeElapsed; // Tiempo que ha pasado desde el inicio de la explosion

};
