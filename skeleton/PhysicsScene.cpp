#include "PhysicsScene.h"
#include "core.hpp"
#include <iostream>
PhysicsScene::PhysicsScene(bool Simulado, float Gravity) : simulado(Simulado), gravity(Gravity)
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

	Vector3 initialPosition(0, 40, 0);
	/*Vector3 initialAcel(0, 1.0001, 0);*/
	Vector3 initialVel(0, -1, 0);
	Vector3 initialAcel(0, gravity, 0);

	////Para la niebla, modificar aqui la gravedad a una mucho menor hasta que no se aplique rozamiento con el aire
	/*ParticlesSystem* systema = createNewParticlesSystem(initialPosition, 9.8f  * 0.000000001f, 0.0f, false, true, Niebla);
	systema->initSystem();*/

	Particle* proyectil = createNewParticle(Esfera, Vector3(0,50,0), Vector3(0, 0, 0), Vector3(0, 0, 0), true, false, false, 0.5f, 5, 0, 0.98, 100, 10, 5);
	std::cout << "particula generada";

	float masa = 800.0f;
	float velReal = 10.0f;
	float velSim = 5.0f;
	Particle* proyectil2 = createNewParticle(Esfera, initialPosition, initialVel, initialAcel, true, true, simulado, 1, masa, gravity, 0.8, 100, velReal, velSim);
	std::cout << "particula 'proyectil2' generada";

	Particle* proyectil3 = createNewParticle(Esfera, Vector3(0, 20, 0), initialVel, initialAcel, true, true, simulado, 1.5f, masa * 2, gravity, 0.98, 100, velReal, velSim);
	std::cout << "particula generada";

	GravityForceGenerator *gfg = new GravityForceGenerator(gravity, simulado);
	addCreatedForceGenerator(gfg);

	float height = 10.0f;          // Altura del cubo
	float volume = 1.0f;           // Volumen de la particula (simplificado)
	float liquid_density = 1000.0f; // Densidad del agua
	float gravity = 9.8f;
	Vector3 surfacePosition(0, 30, 0);  // Nivel de la superficie del agua

	BuoyancyForceGenerator* bfg = new BuoyancyForceGenerator(height, volume, liquid_density, gravity, surfacePosition);
	addCreatedForceGenerator(bfg);
	forceRegistries.addRegistry(proyectil2, bfg);

	forceRegistries.addRegistry(proyectil2, gfg);
		/*
	//forceRegistries.addRegistry(proyectil3, gfg);
	//forceRegistries.addRegistry(proyectil2, gfg);
	//	forceRegistries.addRegistry(proyectil3, gfg);
	//SpringForceGenerator* sfg = new SpringForceGenerator(Vector3(0, 0, 0), proyectil2, nullptr, 50, 10);
	//addCreatedForceGenerator(sfg);
	//SpringForceGenerator* sfg2 = new SpringForceGenerator(Vector3(0, 0, 0), proyectil, nullptr, 50, 10);
	//addCreatedForceGenerator(sfg2);
	//SpringForceGenerator* sfg3 = new SpringForceGenerator(Vector3(0, 0, 0), proyectil2, nullptr, 50, 10);
	//addCreatedForceGenerator(sfg3);
	//SpringForceGenerator* sfg4 = new SpringForceGenerator(Vector3(0, 0, 0), proyectil3, nullptr, 50, 10);
	//addCreatedForceGenerator(sfg4);


	/*GomuGomuFG* sfg = new GomuGomuFG(Vector3(0, 0, 0), proyectil2, 50, 10);
	addCreatedForceGenerator(sfg);
	GomuGomuFG* sfg2 = new GomuGomuFG(Vector3(0, 0, 0), proyectil, 50, 10);
	addCreatedForceGenerator(sfg2);
	GomuGomuFG* sfg3 = new GomuGomuFG(Vector3(0, 0, 0), proyectil2, 50, 10);
	addCreatedForceGenerator(sfg3);
	GomuGomuFG* sfg4 = new GomuGomuFG(Vector3(0, 0, 0), proyectil3, 50, 10);
	addCreatedForceGenerator(sfg4);*/

	//forceRegistries.addRegistry(proyectil, sfg);
	//forceRegistries.addRegistry(proyectil2, sfg2);
	//forceRegistries.addRegistry(proyectil3, sfg3);
	//forceRegistries.addRegistry(proyectil2, sfg4);
	
	
}

void PhysicsScene::updateScene(double dt)
{
	for (auto it : particlesSystems) {
		it->updateSystem(dt);
	}
	forceRegistries.updateForces(dt);
	for (auto it = sceneParticles.begin(); it != sceneParticles.end(); ) {
		Particle* particle = *it;
		if (particle != nullptr) {  // Verifica que la part�cula no sea nula

			//for (auto it2 = forceGenerators.begin(); it2 != forceGenerators.end(); ) {
			//	ForceGenerator* fG = *it2;  // Obtener el puntero del generador de fuerzas
			//	fG->applyForce(particle);
			//	fG->update(dt);
			//	it2++;
			//}

			particle->integrate(dt);  // Actualiza la part�cula
			if (/*particle->getPos().y <= 0.0f || */ particle->toErase()) {
				delete particle;  // Elimina la memoria de la part�cula
				it = sceneParticles.erase(it);  // Elimina la part�cula del vector y actualiza el iterador
			}
			else {
				++it;  // Solo avanza al siguiente elemento si no eliminaste el actual
			}
		}
		else {
			it = sceneParticles.erase(it);  // Si el puntero es nulo, lo eliminamos tambi�n
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
		Particle* proyectil = createNewParticle(Esfera, camera.p, initialVel, initialAcel, true, false, false, 0.5f, 5, 9.8f, 0.98, 2, 100, 5);
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
		Particle* proyectil = createNewParticle(Esfera, camera.p, initialVel, initialAcel, true, false, false, 0.5f, 5, 9.8f, 0.98, 2, 10, 5);
		break;
	}
	case '3':
	{
		for (auto it2 = forceGenerators.begin(); it2 != forceGenerators.end(); ) {
			ForceGenerator* fG = *it2;  // Obtener el puntero del generador de fuerzas
			fG->update2(Vector3(0,0,0), 10);
			it2++;
		}
		cout << "Sumada K de elasticidad del muelle" << endl;
		break;
	}
	case '4':
	{
		for (auto it2 = forceGenerators.begin(); it2 != forceGenerators.end(); ) {
			ForceGenerator* fG = *it2;  // Obtener el puntero del generador de fuerzas
			fG->update2(Vector3(0, 0, 0), -10);
			it2++;
		}
		cout << "Restada K de elasticidad del muelle" << endl;
		break;
	}
	default:
		break;
	}

}
Particle* PhysicsScene::createNewParticle(FormaParticula Forma, Vector3 Pos, Vector3 Vel, Vector3 Acel, bool ConstantAcel, bool CanHaveAccForce, bool Simulado,
	float Radius, float Masa, float Gravedad, double Damping, double LifeTime, float VelR, float VelS)
{
	Particle* part = new Particle(Forma, Pos, Vel, Acel, ConstantAcel, CanHaveAccForce, Simulado, Radius, Masa, Gravedad, Damping, LifeTime , VelR, VelS);
	addCreatedParticle(part);
	return part;
}

ParticlesSystem* PhysicsScene::createNewParticlesSystem(Vector3 Origin, float Gravity, float TimeSpawn, bool Simulado, bool NormalDistribution, Sistema type) {
	ParticlesSystem* system = new ParticlesSystem(Origin, Gravity, TimeSpawn, Simulado, NormalDistribution, type);
	particlesSystems.push_back(system);
	return system;
}

ForceGenerator* PhysicsScene::createNewForceGenerator(GeneradorFuerzas type)
{
	ForceGenerator* forceGen;
	switch (type) {
	case Gravedad:

		forceGen = new GravityForceGenerator(gravity, simulado);
		break;
	case Viento:
		forceGen = new WindForceGenerator(Vector3(500, 0, 0), 2, 0);
		break;
	case Torbellino:
		forceGen = new WhirlwindForceGenerator(Vector3(0, 10, 0), 30);
		break;
	case Explosion:
		forceGen = new ExplosionForceGenerator(Vector3(0, 0, 0), 1000, 2000, 0.01f);
		break;
	case Muelle:
		forceGen = new SpringForceGenerator(Vector3(0, 50, 0), nullptr, nullptr, 100, 0);
		break;
	}
	addCreatedForceGenerator(forceGen);
	return forceGen;
}
