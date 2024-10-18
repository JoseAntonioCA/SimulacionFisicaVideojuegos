#include "ParticlesSystem.h"
#include "Particle.h"
#include "Proyectile.h"
#include "core.hpp"
#include <iostream>
ParticlesSystem::ParticlesSystem(Vector3 Origin, float SpeedSim, float GravitySim, float MassSim, float Gravity, float TimeSpawn, bool NormalDistribution) :
	origen(Origin), speedSim(SpeedSim), gravitySim(GravitySim), massSim(MassSim), gravity(Gravity), timeSpawn(TimeSpawn), normalDistribution(NormalDistribution), canCreateParticle(true)
{
	//initialTimeSpawn = timeSpawn;
	initialTimeSpawn = high_resolution_clock::now();
}
ParticlesSystem::~ParticlesSystem()
{
	for (auto p : particles) {
		delete p;
	}
}

void ParticlesSystem::initSystem()
{
}

void ParticlesSystem::updateSystem(double dt)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// Definimos una distribución uniforme de enteros entre 1 y 100 (inclusive)
	std::uniform_int_distribution<> dis(1, 100);

	// Generamos un número aleatorio
	int random_number = dis(gen);
	int rand = std::rand();
	if (random_number <= 75) {
		double velX = 0.5f;
		double velY = 3;
		double velZ = 0.5f;
		if (!normalDistribution) {
			velX *= (_u(_mt) - 0.5);
			velY *= (_u(_mt) - 0.5);
			velZ *= (_u(_mt) - 0.5);
		}
		else {
			velX *= (_n(_mt));
			velY *= (_n(_mt));
			velZ *= (_n(_mt));
		}
		Vector3 initialVel(velX, velY, velZ);
		Vector3 initialAcel(0, gravity, 0);
		Proyectile* proyectil = createNewProyectile(origen, initialVel, initialAcel, 0.98, true, false, 5, gravity, 10, 5);
		std::cout << "creado" << std::endl;
		
	}
	/*if (canCreateParticle) {
		double velX = 1;
		double velY = 5;
		double velZ = 0;
		if (!normalDistribution) {
			velX *= (_u(_mt) - 0.5);
			velY *= (_u(_mt) - 0.5);
			velZ *= (_u(_mt) - 0.5);
		}
		else {
			velX *= (_n(_mt) - 0.5);
			velY *= (_n(_mt) - 0.5);
			velZ *= (_n(_mt) - 0.5);
		}
		Vector3 initialVel(velX, velY, velZ);
		Vector3 initialAcel(0, gravity, 0);
		Proyectile* proyectil = createNewProyectile(origen, initialVel, initialAcel, 0.98, true, false, 5, 9.8f, 10, 5);
		canCreateParticle = false;
		initialTimeSpawn = high_resolution_clock::now();
	}
	else {
		auto currentTime = high_resolution_clock::now();
		duration<float> deltaTime = duration_cast<duration<float>>(currentTime - (initialTimeSpawn + 5));
		if (currentTime == initialTimeSpawn + )
	}*/

	for (auto it = particles.begin(); it != particles.end(); ) {
		Particle* particle = *it;  // Obtener el puntero de la partícula

		if (particle != nullptr) {  // Verifica que la partícula no sea nula
			particle->integrateAcelerated(dt);  // Actualiza la partícula
			if (particle->getPos().y <= 0.0f || particle->toErase()) {
				delete particle;  // Elimina la memoria de la partícula
				it = particles.erase(it);  // Elimina la partícula del vector y actualiza el iterador
			}
			else {
				++it;  // Solo avanza al siguiente elemento si no eliminaste el actual
			}
		}
		else {
			it = particles.erase(it);  // Si el puntero es nulo, lo eliminamos también
		}
	}
}

void ParticlesSystem::pressKey(char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	switch (toupper(key))
	{
	case '1':
	{
		//Bala pistola
		PxVec3 cameraDirection = camera.q.getBasisVector2();

		Vector3 initialVel(cameraDirection.x * -3,
			cameraDirection.y * -3,
			cameraDirection.z * -3);
		Vector3 initialAcel(0, 1.0001, 0);
		Proyectile* proyectil = createNewProyectile(camera.p, initialVel, initialAcel, 0.98, true, false, 5, 9.8f, 100, 5);
		break;
	}
	case '2':
	{
		//Bala canyon
		PxVec3 cameraDirection = camera.q.getBasisVector2();

		Vector3 initialVel(cameraDirection.x * -3,
			cameraDirection.y * -3,
			cameraDirection.z * -3);
		Vector3 initialAcel(0, 1.0001, 0);
		Proyectile* proyectil = createNewProyectile(camera.p, initialVel, initialAcel, 0.98, true, false, 20, 9.8f, 10, 5);
		break;
	}
	default:
		break;
	}

}
void ParticlesSystem::createParticle(Vector3 pos, double damping)
{
	particles.push_back(new Particle(pos, Vector3(1, 1, 0), Vector3(0, 1.0001, 0), 0.98f, true));
}

Proyectile* ParticlesSystem::createNewProyectile(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel,
	bool Simulado, float Masa, float Gravedad, float VelR, float VelS)
{
	Proyectile* proj = new Proyectile(Pos, Vel, Acel, Damping, ConstantAcel, Simulado, Masa, Gravedad, VelR, VelS);
	addCreatedParticle(proj);
	return proj;
}
