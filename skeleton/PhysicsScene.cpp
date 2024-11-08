#include "PhysicsScene.h"
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
	//Para la niebla, modificar aqui la gravedad a una mucho menor hasta que no se aplique rozamiento con el aire
	ParticlesSystem* systema = createNewParticlesSystem(initialPosition, speedSim, gravitySim, massSim, 9.8f, 0.0f, false, true, Fuente);
	systema->initSystem();

	Particle* proyectil = createNewParticle(initialPosition, initialVel, initialAcel, 0.98, true, false, 0.5f, 5, 9.8f, false, 10, 5);
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
		Particle* proyectil = createNewParticle(camera.p, initialVel, initialAcel, 0.98, true, false, 0.5f, 5, 9.8f, false, 100, 5);
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
		Particle* proyectil = createNewParticle(camera.p, initialVel, initialAcel, 0.98, true, false, 1, 20, 9.8f, false, 10, 5);
		break;
	}
	default:
		break;
	}

}
Particle* PhysicsScene::createNewParticle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel, bool CanHaveAccForce, float Radius, float Masa, float Gravedad,
	bool Simulado, float VelR, float VelS)
{
	Particle* part = new Particle(Pos, Vel, Acel, Damping, ConstantAcel, CanHaveAccForce, Radius, Masa, Gravedad, Simulado, VelR, VelS);
	addCreatedParticle(part);
	return part;
}

ParticlesSystem* PhysicsScene::createNewParticlesSystem(Vector3 Origin, float SpeedSim, float GravitySim, float MassSim, float Gravity, float TimeSpawn, bool Simulado, bool NormalDistribution, Sistema type) {
	ParticlesSystem* system = new ParticlesSystem(Origin, SpeedSim, GravitySim, MassSim, Gravity, TimeSpawn, Simulado, NormalDistribution, type);
	particlesSystems.push_back(system);
	return system;
}