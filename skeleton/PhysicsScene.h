#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <list>
#include "Particle.h"
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

	void createParticle(Vector3 pos, double damping);
	void addCreatedParticle(Particle* particle) {
		sceneParticles.push_back(particle);
	}

	Proyectile* createNewProyectile(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel,
		bool Simulado, float Masa, float Gravedad, float VelR, float VelS);

	void eraseAllParticlesToErase();
private:

	vector<Particle*> sceneParticles;

	list<std::vector<Particle*>::iterator> particlesToErase;

	float gravity;

	float gravitySim;
	float massSim;
	float speedSim;
};

