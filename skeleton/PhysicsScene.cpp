#include "PhysicsScene.h"
#include "Particle.h"
#include "Proyectile.h"
#include "core.hpp"
#include <iostream>
PhysicsScene::PhysicsScene(float VelR, float VelS, float Gravity)
{
	gravity = Gravity;
	speedSim = VelS / VelR;
	gravitySim = pow(speedSim, 2);
	massSim = pow((VelR / VelS), 2);

	gravity *= gravitySim;
}
PhysicsScene::~PhysicsScene()
{

	for (auto p : sceneParticles) {
		delete p;
	}

	for (auto s : particlesSystems) {
		delete s;
	}
}

void PhysicsScene::initScene()
{
	Vector3 initialPosition(0, 1, 0);
	Vector3 initialVel(1, 1, 0);
	Vector3 initialAcel(0, 1.0001, 0);
	ParticlesSystem* systema = createNewParticlesSystem(initialPosition, speedSim, gravitySim, massSim, 9.8f, 0.0f, true, Fuente);
	systema->initSystem();

	Proyectile* proyectil = createNewProyectile(initialPosition, initialVel, initialAcel, 0.98, true, 0.5f, 5, 9.8f, false, 10, 5);
	std::cout << "particula generada";
}

void PhysicsScene::updateScene(double dt)
{
	for (auto it : particlesSystems) {
		it->updateSystem(dt);
	}
	for (auto it : sceneParticles) {
		it->integrate(dt);
		//std::cout << "lista llena" << std::endl;
		if (it->getPos().y <= 0.0f) {
			delete it;

			auto ref = find(sceneParticles.begin(), sceneParticles.end(), it);
			sceneParticles.erase(ref);
		}
		else {
			it++;
		}
	}
}

void PhysicsScene::pressKey(char key, const PxTransform& camera)
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
		Proyectile* proyectil = createNewProyectile(camera.p, initialVel, initialAcel, 0.98, true, 0.5f, 5, 9.8f, false, 100, 5);
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
		Proyectile* proyectil = createNewProyectile(camera.p, initialVel, initialAcel, 0.98, true, 1, 20, 9.8f, false, 10, 5);
		break;
	}
	default:
		break;
	}

}
void PhysicsScene::createParticle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel, float Radius, float Masa, float Gravedad)
{
	sceneParticles.push_back(new Particle(Pos, Vector3(1,1,0), Vector3(0, 1.0001, 0), 0.98f, true, Radius, Masa, Gravedad));
}

Proyectile* PhysicsScene::createNewProyectile(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel, float Radius, float Masa, float Gravedad,
	bool Simulado, float VelR, float VelS)
{
	Proyectile* proj = new Proyectile(Pos, Vel, Acel, Damping, ConstantAcel, Radius, Masa, Gravedad, Simulado, VelR, VelS);
	addCreatedParticle(proj);
	return proj;
}

ParticlesSystem* PhysicsScene::createNewParticlesSystem(Vector3 Origin, float SpeedSim, float GravitySim, float MassSim, float Gravity, float TimeSpawn, bool NormalDistribution, Sistema type) {
	ParticlesSystem* system = new ParticlesSystem(Origin, SpeedSim, GravitySim, MassSim, Gravity, TimeSpawn, NormalDistribution, type);
	particlesSystems.push_back(system);
	return system;
}