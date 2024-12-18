#pragma once

#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <list>
#include "SolidoRigido.h"
#include "Player.h"
#include "ParticlesSystem.h"
#include "SolidoRigidoSystem.h"

#include "ForceGenerator.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "SpringForceGenerator.h"


#include "ForceRegistrySD.h"
#include <random>

using namespace std;

class Nivel1Juego
{
public:
	Nivel1Juego() {};
	Nivel1Juego(Vector3 Origin, physx::PxPhysics* Px, physx::PxScene* Scene, physx::PxMaterial* MGMaterial, float Gravity, bool Simulado);
	~Nivel1Juego();

	void initLevel();

	void updateLevel(double dt);

	void pressKey(char key, const physx::PxTransform& camera);

	void addCreatedSD(SolidoRigido* sd) {
		solidosRigidos.push_back(sd);
	}

	void addCreatedForceGenerator(ForceGenerator* forceGenerator) {
		forceGenerators.push_back(forceGenerator);
	}

	SolidoRigido* createNewSD(Vector3 Pos, Vector3 Geo, Vector3 LinVel, Vector3 AngVel, FormaSolidoDinamico Type,
		physx::PxPhysics* Px, physx::PxScene* Scene, float Mass, double LifeTime, Vector4 Color, bool CanDie, bool ManualConfigLinVel, bool ManualConfigAngVel);

	Player* createNewPlayer(Vector3 Pos, Vector3 Geo, Vector3 LinVel, Vector3 AngVel, FormaSolidoDinamico Type,
		physx::PxPhysics* Px, physx::PxScene* Scene, float Mass, Vector4 Color, bool ManualConfigLinVel, bool ManualConfigAngVel);

	ParticlesSystem* createNewParticlesSystem(Vector3 Origin, float Gravity, float TimeSpawn, bool Simulado, bool NormalDistribution, Sistema type);


private:
	physx::PxPhysics* mPx;
	physx::PxScene* mScene;
	physx::PxMaterial* mGMaterial;

	vector<SpringForceGenerator*> muelles;

	vector<PxRigidStatic*> puntosAnclaje;
	vector<RenderItem*> rendersAnclaje;


	vector<SolidoRigidoSystem*> systemasSolidosRigidos;
	vector<SolidoRigido*> solidosRigidos;
	vector<ForceGenerator*> forceGenerators;

	vector<ParticlesSystem*> particlesSystems;
	
	GravityForceGenerator* gravedadG;

	Player* player;

	ForceRegistrySD forceRegistriesSD;
	ForceRegistrySD forceRegistriesSDMuelles;

	bool simulado;

	float gravity;

	Vector3 origen;

	string _name;
};

