#pragma once
#include "ForceGenerator.h"
#include "core.hpp"


class BuoyancyForceGenerator : public ForceGenerator {
public:
    BuoyancyForceGenerator(float h, float V, float d, float g, Vector3 liquidSurfacePos)
        : height(h), volume(V), liquid_density(d), gravity(g), surfaceHeight(liquidSurfacePos.y) {
        		Vector3 initialPosition(0, surfaceHeight, 0);
        		Vector3 initialVel(0, 0, 0);
        		Vector3 initialAcel(0, 0, 0);
        
        
        		float masa = 0;
        		float velReal = 1;
        		float velSim = 1;
        		liquid_particle = new Particle(Plano, initialPosition, initialVel, initialAcel, true, false, false, 10, masa, 0, 0.98, 100, velReal, velSim);
    }

    // Método que aplica la fuerza de flotación a una partícula
    virtual void applyForce(Particle* p) override {
        float h = p->getPos().y; // Posición actual de la partícula
        float immersed = 0.0f;
        Vector3 buoyancyForce(0, 0, 0);

        if (h - surfaceHeight >= height * 0.5f) {
            immersed = 0.0f; // Totalmente fuera del agua
        }
        else if (surfaceHeight - h >= height * 0.5f) {
            immersed = 1.0f; // Totalmente sumergido
        }
        else {
            immersed = (surfaceHeight - h) / height + 0.5f; // Parcialmente sumergido
        }

        buoyancyForce.y = liquid_density * volume * immersed * gravity;

        /*if (p->getPos().y <= 30) {
            std::cout << buoyancyForce.y << std::endl;
        }*/
        // Aplica la fuerza de flotación a la partícula
        p->addForce(buoyancyForce);
    }


    virtual void applyForce(SolidoRigido* sd) override {
        float h = sd->getPos().y; // Posición actual de la partícula
        float immersed = 0.0f;
        Vector3 buoyancyForce(0, 0, 0);

        if (h - surfaceHeight >= height * 0.5f) {
            immersed = 0.0f; // Totalmente fuera del agua
        }
        else if (surfaceHeight - h >= height * 0.5f) {
            immersed = 1.0f; // Totalmente sumergido
        }
        else {
            immersed = (surfaceHeight - h) / height + 0.5f; // Parcialmente sumergido
        }

        buoyancyForce.y = liquid_density * volume * immersed * gravity;

        /*if (sd->getPos().y <= 30) {
            std::cout << buoyancyForce.y << std::endl;
        }*/
        // Aplica la fuerza de flotación a la partícula
        sd->getRigidDynamic()->addForce(buoyancyForce);
    }

    	void update(double deltaTime) {}
    	void update2(Vector3 v, float Kplus) {}
protected:
    float height;            // Altura del objeto flotante (dimensión en Y)
    float volume;            // Volumen del objeto flotante
    float liquid_density;    // Densidad del líquido
    float gravity;           // Gravedad externa
    float surfaceHeight;     // Altura del nivel del líquido

    Particle* liquid_particle;
};

