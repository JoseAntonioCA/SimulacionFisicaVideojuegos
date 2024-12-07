#include "SolidoRigidoSystem.h"
#include "core.hpp"
#include <iostream>
SolidoRigidoSystem::SolidoRigidoSystem(Vector3 Origin, physx::PxPhysics* Px, physx::PxScene* Scene, float Gravity, bool Simulado, bool NormalDistribution, SistemaSD type) :
	origen(Origin), mPx(Px), mScene(Scene), gravity(Gravity), simulado(Simulado), normalDistribution(NormalDistribution), tipoSistema(type)
{

}
SolidoRigidoSystem::~SolidoRigidoSystem()
{
	for (auto sd : solidosRigidos) {
		delete sd;
	}
}

void SolidoRigidoSystem::initSystem()
{
	ForceGenerator* fg = createNewForceGenerator(Gravedad);
	std::cout << "creada Gravedad" << std::endl;
	/*ForceGenerator* fg2 = createNewForceGenerator(Viento);
	std::cout << "creado Viento" << std::endl;
	ForceGenerator* fg3 = createNewForceGenerator(Torbellino);
	std::cout << "creado Torbellino" << std::endl;*/
	/*ForceGenerator* fg4 = createNewForceGenerator(Explosion);
	std::cout << "creada Explosion" << std::endl;*/
	/*ForceGenerator* fg5 = createNewForceGenerator(Muelle);
	std::cout << "creado Muelle" << std::endl;*/
}

void SolidoRigidoSystem::sdGenerator() {

	switch (tipoSistema) {
	case Fuente:
		generateSDFuente();
		break;
	case Lluvia:
		generateSDLluvia();
		break;
	default:
		break;
	}
}

void SolidoRigidoSystem::generateSDFuente() {
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

	float masa = 5.0f;
	float velReal = 10.0f;
	float velSim = 5.0f;
	Vector3 initialVel(velX, velY, velZ);
	Vector3 initialAcel(0, gravity, 0);
	SolidoRigido* proyectil = createNewSD(origen, { 0.25, 0.25, 0.25 }, initialVel, initialAcel, ESFERA, mPx, mScene, masa, {0.5,0.5,0.5,1}, false, false);
	proyectil->getRigidDynamic()->addForce(initialVel);
}

void SolidoRigidoSystem::generateSDLluvia() {
	double velY = -0.01f;

	if (!normalDistribution) {
		origen.x = (_uNiebla(_mt));
		origen.z = (_uNiebla(_mt));
		velY *= (_u(_mt) - 0.5);
	}
	else {
		origen.x = (_nNiebla(_mt));
		origen.z = (_nNiebla(_mt));
		velY *= (_n(_mt));
	}

	float masa = 5.0f;
	float velReal = 10.0f;
	float velSim = 5.0f;
	Vector3 initialVel(0, velY, 0);
	Vector3 initialAcel(0, gravity, 0);
	SolidoRigido* proyectil = createNewSD(origen, { 0.25, 0.25, 0.25 }, initialVel, initialAcel, ESFERA, mPx, mScene, masa, { 0.5,0.5,0.5,1 }, false, false);
	proyectil->getRigidDynamic()->addForce(initialVel);
}


void SolidoRigidoSystem::updateSystem(double dt)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// Definimos una distribución uniforme de enteros entre 1 y 100 (inclusive)
	std::uniform_int_distribution<> dis(1, 100);

	// Generamos un número aleatorio
	int random_number = dis(gen);
	int rand = std::rand();
	if (random_number <= 75) {
		sdGenerator();
	}

	for (auto it = solidosRigidos.begin(); it != solidosRigidos.end(); ) {
		SolidoRigido* sd = *it;  // Obtener el puntero de la partícula

		if (sd != nullptr) {  // Verifica que la partícula no sea nula

			for (auto it2 = forceGenerators.begin(); it2 != forceGenerators.end(); ) {
				ForceGenerator* fG = *it2;  // Obtener el puntero del generador de fuerzas
				fG->applyForce(sd);
				fG->update(dt);
				it2++;
			}

			//particle->integrate(dt);  // Actualiza la partícula
			//if (particle->getPos().y <= 0.0f || particle->toErase()) {
			//	delete particle;  // Elimina la memoria de la partícula
			//	it = particles.erase(it);  // Elimina la partícula del vector y actualiza el iterador
			//}
			//else {
			//	++it;  // Solo avanza al siguiente elemento si no eliminaste el actual
			//}
		}
		else {
			it = solidosRigidos.erase(it);  // Si el puntero es nulo, lo eliminamos también
		}
	}
}

void SolidoRigidoSystem::pressKey(char key, const PxTransform& camera)
{
	//PX_UNUSED(camera);
	//switch (toupper(key))
	//{
	//case '1':
	//{
	//	//Bala pistola
	//	PxVec3 cameraDirection = camera.q.getBasisVector2();

	//	Vector3 initialVel(cameraDirection.x * -3,
	//		cameraDirection.y * -3,
	//		cameraDirection.z * -3);
	//	Vector3 initialAcel(0, 1.0001, 0);

	//	Particle* proyectil = createNewParticle(Esfera, camera.p, initialVel, initialAcel, true, false, false, 0.5f, 5, 9.8f, 0.98, 2, 100, 5);
	//	break;
	//}
	//case '2':
	//{
	//	//Bala canyon
	//	PxVec3 cameraDirection = camera.q.getBasisVector2();

	//	Vector3 initialVel(cameraDirection.x * -3,
	//		cameraDirection.y * -3,
	//		cameraDirection.z * -3);
	//	Vector3 initialAcel(0, 1.0001, 0);
	//	Particle* proyectil = createNewParticle(Esfera, camera.p, initialVel, initialAcel, true, false, false, 0.5f, 5, 9.8f, 0.98, 2, 10, 5);
	//	break;
	//}
	//default:
	//	break;
	//}

}

SolidoRigido* SolidoRigidoSystem::createNewSD(Vector3 Pos, Vector3 Geo, Vector3 LinVel, Vector3 AngVel, FormaSolidoDinamico Type,
	physx::PxPhysics* Px, physx::PxScene* Scene, float Mass, Vector4 Color, bool ManualConfigLinVel, bool ManualConfigAngVel)
{
	SolidoRigido* sd = new SolidoRigido(Pos, Geo, LinVel, AngVel, Type, Px, Scene, Mass, Color, ManualConfigLinVel, ManualConfigAngVel);
	addCreatedSD(sd);
	return sd;
}

ForceGenerator* SolidoRigidoSystem::createNewForceGenerator(GeneradorFuerzasSD type)
{
	ForceGenerator* forceGen;
	switch (type) {
	case Gravedad:

		forceGen = new GravityForceGenerator(gravity, simulado);
		break;
	case Viento:
		forceGen = new WindForceGenerator(Vector3(30, 0, 0), 2, 0);
		break;
	case Torbellino:
		forceGen = new WhirlwindForceGenerator(Vector3(0, 10, 0), 30);
		break;
	case Explosion:
		forceGen = new ExplosionForceGenerator(Vector3(0, 0, 0), 1000, 2000, 0.01f);
		break;
	case Muelle:
		forceGen = new SpringForceGenerator(Vector3(0, 50, 0), nullptr, nullptr, 10, 0);
		break;
	}
	addCreatedForceGenerator(forceGen);
	return forceGen;
}
