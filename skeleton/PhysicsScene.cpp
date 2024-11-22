#include "PhysicsScene.h"
#include "core.hpp"
#include <iostream>
PhysicsScene::PhysicsScene(bool Simulado, float Gravity) : simulado(Simulado), gravity(Simulado)
{
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
	//Para la niebla, modificar aqui la gravedad a una mucho menor hasta que no se aplique rozamiento con el aire
	ParticlesSystem* systema = createNewParticlesSystem(initialPosition, 9.8f * 0.000000001f, 0.0f, false, true, Niebla);
	systema->initSystem();

	Particle* proyectil = createNewParticle(initialPosition, initialVel, initialAcel, true, false, false, 0.5f, 5, 9.8f, 0.98, 2, 10, 5);
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
	for (auto it : particlesSystems) {
		it->pressKey(key, camera);
	}
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
		Particle* proyectil = createNewParticle(camera.p, initialVel, initialAcel, true, false, false, 0.5f, 5, 9.8f, 0.98, 2, 100, 5);
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
		Particle* proyectil = createNewParticle(camera.p, initialVel, initialAcel, true, false, false, 0.5f, 5, 9.8f, 0.98, 2, 10, 5);
		break;
	}
	default:
		break;
	}

}
Particle* PhysicsScene::createNewParticle(Vector3 Pos, Vector3 Vel, Vector3 Acel, bool ConstantAcel, bool CanHaveAccForce, bool Simulado,
	float Radius, float Masa, float Gravedad, double Damping, double LifeTime, float VelR, float VelS)
{
	Particle* part = new Particle(Pos, Vel, Acel, ConstantAcel, CanHaveAccForce, Simulado, Radius, Masa, Gravedad, Damping, LifeTime , VelR, VelS);
	addCreatedParticle(part);
	return part;
}

ParticlesSystem* PhysicsScene::createNewParticlesSystem(Vector3 Origin, float Gravity, float TimeSpawn, bool Simulado, bool NormalDistribution, Sistema type) {
	ParticlesSystem* system = new ParticlesSystem(Origin, Gravity, TimeSpawn, Simulado, NormalDistribution, type);
	particlesSystems.push_back(system);
	return system;
}