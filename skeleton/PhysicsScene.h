#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <list>
#include "Particle.h"
#include "ParticlesSystem.h"
class Proyectile;

using namespace std;
class PhysicsScene
{
public:
	PhysicsScene() {};
	PhysicsScene(float VelR, float VelS, float gravity);
	~PhysicsScene();

	void initScene();

	void updateScene(double dt);

	void pressKey(char key, const physx::PxTransform& camera);

	void createParticle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel, float Radius);
	void addCreatedParticle(Particle* particle) {
		sceneParticles.push_back(particle);
	}

	Proyectile* createNewProyectile(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel, float Radius,
		bool Simulado, float Masa, float Gravedad, float VelR, float VelS);
	ParticlesSystem* createNewParticlesSystem(Vector3 Origin, float SpeedSim, float GravitySim, float MassSim, float Gravity, float TimeSpawn, bool NormalDistribution, Sistema type);
private:

	vector<Particle*> sceneParticles;
	vector<ParticlesSystem*> particlesSystems;

	float gravity;

	float gravitySim;
	float massSim;
	float speedSim;
};

