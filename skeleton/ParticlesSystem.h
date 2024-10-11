#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <list>
#include "Particle.h"
#include <random>

class Proyectile;

using namespace std;

class ParticlesSystem
{
public:
	ParticlesSystem() {};
	ParticlesSystem(Vector3 Origin, float SpeedSim, float GravitySim, float MassSim, float gravity);
	~ParticlesSystem();

	void initSystem();

	void updateSystem(double dt);

	void pressKey(char key, const physx::PxTransform& camera);

	void createParticle(Vector3 pos, double damping);
	void addCreatedParticle(Particle* particle) {
		particles.push_back(particle);
	}

	Proyectile* createNewProyectile(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel,
		bool Simulado, float Masa, float Gravedad, float VelR, float VelS);
private:

	vector<Particle*> particles;

	float gravity;

	float gravitySim;
	float massSim;
	float speedSim;

	Vector3 origen;

	mt19937 _mt;
	uniform_real_distribution<double> _u{ 0,1 };

	string _name;
};

