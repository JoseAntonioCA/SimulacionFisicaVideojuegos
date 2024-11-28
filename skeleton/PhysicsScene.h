#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <list>
#include "Particle.h"
#include "ParticlesSystem.h"

#include "ForceGenerator.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"
#include "GomuGomuFG.h"
#include "BuoyancyForceGenerator.h"

#include "ForceRegistry.h"

using namespace std;

//enum GeneradorFuerzas { Gravedad, Viento, Torbellino, Explosion, Muelle };

class PhysicsScene
{
public:
	PhysicsScene() {};
	PhysicsScene(bool simulado, float gravity);
	~PhysicsScene();

	void initScene();

	void updateScene(double dt);

	void pressKey(char key, const physx::PxTransform& camera);

	Particle* createNewParticle(Vector3 Pos, Vector3 Vel, Vector3 Acel, bool ConstantAcel, bool CanHaveAccForce, bool Simulado,
		float Radius, float Masa, float Gravedad, double Damping, double LifeTime, float VelR, float VelS);
	void addCreatedParticle(Particle* particle) {
		sceneParticles.push_back(particle);
	}

	ParticlesSystem* createNewParticlesSystem(Vector3 Origin, float Gravity, float TimeSpawn, bool Simulado, bool NormalDistribution, Sistema type);

	ForceGenerator* createNewForceGenerator(GeneradorFuerzas type);

	void addCreatedForceGenerator(ForceGenerator* forceGenerator) {
		forceGenerators.push_back(forceGenerator);
	}

private:

	vector<Particle*> sceneParticles;
	vector<ParticlesSystem*> particlesSystems;

	vector<ForceGenerator*> forceGenerators;
	ForceRegistry forceRegistries;

	float gravity;

	bool simulado;
};

