#pragma once

#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <list>
#include "SolidoRigido.h"

#include "ForceGenerator.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include "SpringForceGenerator.h"


#include "ForceRegistry.h"
#include <random>

using namespace std;

enum SistemaSD { FuenteSD, LluviaSD};
enum GeneradorFuerzasSD { GravedadSD, VientoSD, TorbellinoSD, ExplosionSD, MuelleSD };

class SolidoRigidoSystem
{
public:
	SolidoRigidoSystem() {};
	SolidoRigidoSystem(Vector3 Origin, physx::PxPhysics* Px, physx::PxScene* Scene, physx::PxMaterial* MGMaterial, float Gravity, bool Simulado, bool NormalDistribution, SistemaSD type);
	~SolidoRigidoSystem();

	void initSystem();

	void updateSystem(double dt);

	void pressKey(char key, const physx::PxTransform& camera);

	void sdGenerator();
	void generateSDFuente();
	void generateSDLluvia();

	void addCreatedSD(SolidoRigido* sd) {
		solidosRigidos.push_back(sd);
	}

	void addCreatedForceGenerator(ForceGenerator* forceGenerator) {
		forceGenerators.push_back(forceGenerator);
	}

	SolidoRigido* createNewSD(Vector3 Pos, Vector3 Geo, Vector3 LinVel, Vector3 AngVel, FormaSolidoDinamico Type,
		physx::PxPhysics* Px, physx::PxScene* Scene, float Mass, Vector4 Color, bool ManualConfigLinVel, bool ManualConfigAngVel);


	ForceGenerator* createNewForceGenerator(GeneradorFuerzasSD type);
private:
	physx::PxPhysics* mPx;
	physx::PxScene* mScene;
	physx::PxMaterial* mGMaterial;

	vector<SolidoRigido*> solidosRigidos;
	vector<ForceGenerator*> forceGenerators;
	ForceGenerator* forceGenerator;
	ForceRegistry forceRegistries;

	bool normalDistribution;

	bool simulado;

	float gravity;

	Vector3 origen;
	SistemaSD tipoSistema;

	mt19937 _mt;
	uniform_real_distribution<double> _u{ 0,1 };
	normal_distribution<double> _n{ 0, 0.5f };

	// parametros para modificar el origen en la niebla
	uniform_real_distribution<double> _uNiebla{ 0,10 };
	normal_distribution<double> _nNiebla{ 0, 10 };

	string _name;
};

