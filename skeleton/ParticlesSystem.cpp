#include "ParticlesSystem.h"
#include "Particle.h"
#include "Proyectile.h"
#include "core.hpp"
#include <iostream>
ParticlesSystem::ParticlesSystem(Vector3 Origin, float SpeedSim, float GravitySim, float MassSim, float Gravity) :
	origen(Origin), speedSim(SpeedSim), gravitySim(GravitySim), massSim(MassSim), gravity(Gravity)
{
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
	Vector3 initialVel(1, 1, 0);
	Vector3 initialAcel(0, 1.0001, 0);
	Proyectile* proyectil = createNewProyectile(origen, initialVel, initialAcel, 0.98, true, false, 5, 9.8f, 10, 5);

	for (auto it : particles) {
		it->integrateAcelerated(dt);
		std::cout << "lista llena" << std::endl;
		if (it->getPos().y <= 0.0f) {
			delete it;

			auto ref = find(particles.begin(), particles.end(), it);
			particles.erase(ref);
		}
		else {
			it++;
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
