#include "SolidoRigidoSystem.h"
#include "core.hpp"
#include <iostream>
SolidoRigidoSystem::SolidoRigidoSystem(Vector3 Origin, physx::PxPhysics* Px, physx::PxScene* Scene, physx::PxMaterial* MGMaterial, float Gravity, bool Simulado, bool NormalDistribution, SistemaSD type) :
	origen(Origin), mPx(Px), mScene(Scene), mGMaterial (MGMaterial), gravity(Gravity), simulado(Simulado), normalDistribution(NormalDistribution), tipoSistema(type)
{
	mScene->setGravity({ 0, 0, 0 });

	//mGMaterial->setRestitution(1.2);
}
SolidoRigidoSystem::~SolidoRigidoSystem()
{
	for (auto sd : solidosRigidos) {
		delete sd;
	}
}

void SolidoRigidoSystem::initSystem()
{
	ForceGenerator* fg = createNewForceGenerator(GravedadSD);
	std::cout << "creada Gravedad" << std::endl;
	/*ForceGenerator* fg2 = createNewForceGenerator(VientoSD);
	std::cout << "creado Viento" << std::endl;*/
	SolidoRigido* proyectil = createNewSD(origen, { 5, 5, 5 }, {0,0,0}, {0,0,0}, ESFERA, mPx, mScene, 100, {0.5,0.5,0.5,1}, false, false);
	SolidoRigido* proyectil2 = createNewSD(origen, { 5, 15, 5 }, { 0,0,0 }, { 0,0,0 }, ESFERA, mPx, mScene, 100, { 0.5,0.5,0.5,1 }, false, false);
	SolidoRigido* proyectil3 = createNewSD(origen, { 5, 25, 5 }, { 0,0,0 }, { 0,0,0 }, ESFERA, mPx, mScene, 100, { 0.5,0.5,0.5,1 }, false, false);
	for (auto e : forceGenerators) {
		forceRegistriesSD.addRegistry(proyectil, e);
	}
	/*ForceGenerator* fg2 = createNewForceGenerator(Viento);
	std::cout << "creado Viento" << std::endl;
	ForceGenerator* fg3 = createNewForceGenerator(Torbellino);
	std::cout << "creado Torbellino" << std::endl;*/
	/*ForceGenerator* fg5 = createNewForceGenerator(Muelle);
	std::cout << "creado Muelle" << std::endl;*/


	SpringForceGenerator* sfg = new SpringForceGenerator(Vector3(0, 0, 0), nullptr, proyectil2, 50, 10);
	addCreatedForceGenerator(sfg);
	SpringForceGenerator* sfg2 = new SpringForceGenerator(Vector3(0, 0, 0), nullptr, proyectil, 50, 10);
	addCreatedForceGenerator(sfg2);
	SpringForceGenerator* sfg3 = new SpringForceGenerator(Vector3(0, 0, 0), nullptr, proyectil2, 50, 10);
	addCreatedForceGenerator(sfg3);
	SpringForceGenerator* sfg4 = new SpringForceGenerator(Vector3(0, 0, 0), nullptr, proyectil3, 50, 10);
	addCreatedForceGenerator(sfg4);


	/*GomuGomuFG* sfg = new GomuGomuFG(Vector3(0, 0, 0), proyectil2, 50, 10);
	addCreatedForceGenerator(sfg);
	GomuGomuFG* sfg2 = new GomuGomuFG(Vector3(0, 0, 0), proyectil, 50, 10);
	addCreatedForceGenerator(sfg2);
	GomuGomuFG* sfg3 = new GomuGomuFG(Vector3(0, 0, 0), proyectil2, 50, 10);
	addCreatedForceGenerator(sfg3);
	GomuGomuFG* sfg4 = new GomuGomuFG(Vector3(0, 0, 0), proyectil3, 50, 10);
	addCreatedForceGenerator(sfg4);*/

	forceRegistriesSD.addRegistry(proyectil, sfg);
	forceRegistriesSD.addRegistry(proyectil2, sfg2);
	forceRegistriesSD.addRegistry(proyectil3, sfg3);
	forceRegistriesSD.addRegistry(proyectil2, sfg4);
}

void SolidoRigidoSystem::sdGenerator() {

	switch (tipoSistema) {
	case FuenteSD:
		generateSDFuente();
		break;
	case LluviaSD:
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
	SolidoRigido* proyectil = createNewSD(origen, { 1, 1, 1 }, initialVel, initialAcel, ESFERA, mPx, mScene, masa, {0.5,0.5,0.5,1}, false, false);
	//proyectil->getRigidDynamic()->addForce(initialVel);
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
	SolidoRigido* proyectil = createNewSD(origen, { 1, 1, 1 }, initialVel, initialAcel, ESFERA, mPx, mScene, masa, { 0.5,0.5,0.5,1 }, false, false);
	//proyectil->getRigidDynamic()->addForce(initialVel, physx::PxForceMode::eIMPULSE);
	physx::PxRigidBodyExt::updateMassAndInertia(*proyectil->getRigidDynamic(), masa);

	forceRegistriesSD.addRegistry(proyectil, forceGenerators[0]);
	/*for (auto e : forceGenerators) {
		forceRegistriesSD.addRegistry(proyectil, e);
	}*/
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
	if (random_number <= 75 && solidosRigidos.size() <= 100) {
		sdGenerator();
	}

	forceRegistriesSD.updateForces(dt);
	for (auto it = solidosRigidos.begin(); it != solidosRigidos.end(); ) {
		SolidoRigido* sd = *it;  // Obtener el puntero de la partícula

		if (sd != nullptr) {  // Verifica que la partícula no sea nula


			//for (auto it2 = forceGenerators.begin(); it2 != forceGenerators.end(); ) {
			//	ForceGenerator* fG = *it2;  // Obtener el puntero del generador de fuerzas
			//	fG->applyForce(sd);
			//	fG->update(dt);
			//	it2++;
			//}

			//particle->integrate(dt);  // Actualiza la partícula
			//if (particle->getPos().y <= 0.0f || particle->toErase()) {
			//	delete particle;  // Elimina la memoria de la partícula
			//	it = particles.erase(it);  // Elimina la partícula del vector y actualiza el iterador
			//}
			//else {
			//	++it;  // Solo avanza al siguiente elemento si no eliminaste el actual
			//}
			it++;
		}
		else {
			it = solidosRigidos.erase(it);  // Si el puntero es nulo, lo eliminamos también
		}
	}
}

void SolidoRigidoSystem::pressKey(char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	switch (toupper(key))
	{
	case 'E':
	{
		ForceGenerator* fg4 = createNewForceGenerator(ExplosionSD);
		std::cout << "creada Explosion" << std::endl;

		for (auto e: solidosRigidos)
			forceRegistriesSD.addRegistry(e, fg4);
		break;
	}
	default:
		break;
	}

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
	case GravedadSD:

		forceGen = new GravityForceGenerator(gravity, simulado);
		break;
	case VientoSD:
		forceGen = new WindForceGenerator(Vector3(-3000, 0, 0), 2, 0);
		break;
	case TorbellinoSD:
		forceGen = new WhirlwindForceGenerator(Vector3(0, 10, 0), 30);
		break;
	case ExplosionSD:
		forceGen = new ExplosionForceGenerator(Vector3(0, 0, 0), 100000000, 2000, 0.01f);
		break;
	case MuelleSD:
		forceGen = new SpringForceGenerator(Vector3(0, 50, 0), nullptr, nullptr, 10, 0);
		break;
	}
	addCreatedForceGenerator(forceGen);
	return forceGen;
}
