#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <list>
#include "Particle.h"

#include "ForceGenerator.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
#include <random>

using namespace std;

enum Sistema{Fuente, Lluvia, Niebla};
enum GeneradorFuerzas { Gravedad, Viento, Torbellino, Explosion };

class ParticlesSystem
{
public:
	ParticlesSystem() {};
	ParticlesSystem(Vector3 Origin, float Gravity, float TimeSpawn, bool Simulado, bool NormalDistribution, Sistema type);
	~ParticlesSystem();

	void initSystem();

	void updateSystem(double dt);

	void pressKey(char key, const physx::PxTransform& camera);

	void particlesGenerator();
	void generateParticleFuente();
	void generateParticleLluvia();
	void generateParticleNiebla();

	void addCreatedParticle(Particle* particle) {
		particles.push_back(particle);
	}

	void addCreatedForceGenerator(ForceGenerator* forceGenerator) {
		forceGenerators.push_back(forceGenerator);
	}

	Particle* createNewParticle(Vector3 Pos, Vector3 Vel, Vector3 Acel, bool ConstantAcel, bool CanHaveAccForce, bool Simulado,
		float Radius, float Masa, float Gravedad, double Damping, double LifeTime, float VelR, float VelS);


	ForceGenerator* createNewForceGenerator(GeneradorFuerzas type);
private:

	vector<Particle*> particles;
	vector<ForceGenerator*> forceGenerators;
	ForceGenerator* forceGenerator;

	bool canCreateParticle;

	bool normalDistribution;

	bool simulado;

	float timeSpawn;

	float gravity;

	Vector3 origen;
	Sistema tipoSistema;

	mt19937 _mt;
	uniform_real_distribution<double> _u{ 0,1 };
	normal_distribution<double> _n{ 0, 0.5f };

	// parametros para modificar el origen en la niebla
	uniform_real_distribution<double> _uNiebla{ 0,10 };
	normal_distribution<double> _nNiebla{ 0, 10 };

	string _name;
};

