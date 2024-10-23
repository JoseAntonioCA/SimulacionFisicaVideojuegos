#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include <list>
#include "Particle.h"
#include <random>
#include <chrono>

class Proyectile;

using namespace std;
using namespace std::chrono;

enum Sistema{Fuente, Lluvia, Niebla};

class ParticlesSystem
{
public:
	ParticlesSystem() {};
	ParticlesSystem(Vector3 Origin, float SpeedSim, float GravitySim, float MassSim, float Gravity, float TimeSpawn, bool NormalDistribution, Sistema type);
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

	Proyectile* createNewProyectile(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel, float Radius,
		bool Simulado, float Masa, float Gravedad, float VelR, float VelS);

	Particle* createNewParticle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel, float Radius);
private:

	vector<Particle*> particles;

	bool canCreateParticle;

	bool normalDistribution;

	float timeSpawn;

	time_point<high_resolution_clock> initialTimeSpawn;

	float gravity;

	float gravitySim;
	float massSim;
	float speedSim;

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

