#include "Nivel1Juego.h"
#include "core.hpp"
#include <iostream>
Nivel1Juego::Nivel1Juego(Vector3 Origin, physx::PxPhysics* Px, physx::PxScene* Scene, physx::PxMaterial* MGMaterial, float Gravity, bool Simulado) :
	origen(Origin), mPx(Px), mScene(Scene), mGMaterial(MGMaterial), gravity(Gravity), simulado(Simulado)
{
	mScene->setGravity({ 0, 0, 0 });

	//mGMaterial->setRestitution(1.2);
}

Nivel1Juego::~Nivel1Juego(){
	for (auto sd : solidosRigidos) {
		delete sd;
	}
}

void Nivel1Juego::initLevel()
{
	//Suelos techos y paredes

	PxRigidStatic* pared1 = mPx->createRigidStatic(physx::PxTransform(-100, -20, 0));
	PxShape* shape0 = CreateShape(PxBoxGeometry(0.1, 100, 100));
	pared1->attachShape(*shape0);
	mScene->addActor(*pared1);
	RenderItem* itemR0 = new RenderItem(shape0, pared1, { 0,0,0,1 });

	PxRigidStatic* suelo1 = mPx->createRigidStatic(physx::PxTransform(0, -20, 0));
	PxShape* shape02 = CreateShape(PxBoxGeometry(100, 0.1, 100));
	suelo1->attachShape(*shape02);
	mScene->addActor(*suelo1);
	RenderItem* itemR02 = new RenderItem(shape02, suelo1, { 1,1,1,1 });

	PxRigidStatic* suelo2 = mPx->createRigidStatic(physx::PxTransform(600, 0, 0));
	PxShape* shape03 = CreateShape(PxBoxGeometry(100, 0.1, 100));
	suelo2->attachShape(*shape03);
	mScene->addActor(*suelo2);
	RenderItem* itemR03 = new RenderItem(shape03, suelo2, { 1,1,1,1 });


	PxRigidStatic* techo1 = mPx->createRigidStatic(physx::PxTransform(800, 200, 0));
	PxShape* shape04 = CreateShape(PxBoxGeometry(200, 0.1, 100));
	techo1->attachShape(*shape04);
	mScene->addActor(*techo1);
	RenderItem* itemR04 = new RenderItem(shape04, techo1, { 1,1,1,1 });


	PxRigidStatic* pared2 = mPx->createRigidStatic(physx::PxTransform(800, 0, 0));
	PxShape* shape05 = CreateShape(PxBoxGeometry(0.1, 150, 100));
	pared2->attachShape(*shape05);
	mScene->addActor(*pared2);
	RenderItem* itemR05 = new RenderItem(shape05, pared2, { 0,0,0,1 });


	PxRigidStatic* suelo3 = mPx->createRigidStatic(physx::PxTransform(1000, 0, 0));
	PxShape* shape06 = CreateShape(PxBoxGeometry(100, 0.1, 100));
	suelo3->attachShape(*shape06);
	mScene->addActor(*suelo3);
	RenderItem* itemR06 = new RenderItem(shape06, suelo3, { 1,1,1,1 });


	PxRigidStatic* suelo4 = mPx->createRigidStatic(physx::PxTransform(1400, 0, 0));
	PxShape* shape07 = CreateShape(PxBoxGeometry(100, 0.1, 100));
	suelo4->attachShape(*shape07);
	mScene->addActor(*suelo4);
	RenderItem* itemR07 = new RenderItem(shape07, suelo4, { 1,1,1,1 });

	PxRigidStatic* suelo5 = mPx->createRigidStatic(physx::PxTransform(1750, 0, 0));
	PxShape* shape08 = CreateShape(PxBoxGeometry(200, 0.1, 100));
	suelo5->attachShape(*shape08);
	mScene->addActor(*suelo5);
	RenderItem* itemR08 = new RenderItem(shape08, suelo5, { 1,1,1,1 });


	PxRigidStatic* techo2 = mPx->createRigidStatic(physx::PxTransform(1050, 322, 0));
	PxShape* shape09 = CreateShape(PxBoxGeometry(50, 0.1, 100));
	techo2->attachShape(*shape09);
	mScene->addActor(*techo2);
	RenderItem* itemR09 = new RenderItem(shape09, techo2, { 1,1,1,1 });


	//Puntos de anclaje

	PxRigidStatic* puntoAncla = mPx->createRigidStatic(physx::PxTransform(200, 50, 0));
	PxShape* shape = CreateShape(PxSphereGeometry(5));
	puntoAncla->attachShape(*shape);
	mScene->addActor(*puntoAncla);
	RenderItem* itemR = new RenderItem(shape, puntoAncla, { 0.1,0.1,0.1,1 });
	puntosAnclaje.push_back(puntoAncla);
	rendersAnclaje.push_back(itemR);

	PxRigidStatic* puntoAncla2 = mPx->createRigidStatic(physx::PxTransform(300, 50, 0));
	PxShape* shape2 = CreateShape(PxSphereGeometry(5));
	puntoAncla2->attachShape(*shape2);
	mScene->addActor(*puntoAncla2);
	RenderItem* itemR2 = new RenderItem(shape2, puntoAncla2, { 0.1,0.1,0.1,1 });
	puntosAnclaje.push_back(puntoAncla2);
	rendersAnclaje.push_back(itemR2);

	PxRigidStatic* puntoAncla3 = mPx->createRigidStatic(physx::PxTransform(400, 50, 0));
	PxShape* shape3 = CreateShape(PxSphereGeometry(5));
	puntoAncla3->attachShape(*shape3);
	mScene->addActor(*puntoAncla3);
	RenderItem* itemR3 = new RenderItem(shape3, puntoAncla3, { 0.1,0.1,0.1,1 });
	puntosAnclaje.push_back(puntoAncla3);
	rendersAnclaje.push_back(itemR3);


	//Sistemas de particulas
	
	Vector3 pSysPos = { -50, -20, 50 };

	Vector3 pSysPos2 = { -50, -20, -50 };

	Vector3 pSysPos3 = { 200, -60, -50 };

	for (int i = 0; i < 12; i++) {

		ParticlesSystem* systema = createNewParticlesSystem(pSysPos, 9.8f, 0.0f, false, true, Fuente);
		systema->initSystem();
		pSysPos.x += 10;
	}

	for (int i = 0; i < 12; i++) {
		ParticlesSystem* systema = createNewParticlesSystem(pSysPos2, 9.8f, 0.0f, false, true, Fuente);
		systema->initSystem();
		pSysPos2.x += 10;
	}

	for (int i = 0; i < 20; i++) {
		ParticlesSystem* systema = createNewParticlesSystem(pSysPos3, 9.8f * 0.00000095f, 0.0f, false, true, Remolino);
		systema->initSystem();
		pSysPos3.x += 100;
	}

	ParticlesSystem* systema = createNewParticlesSystem({0,100,0}, 9.8f, 0.0f, false, true, Lluvia);
	systema->initSystem();


	//Sistemas de solidos rigidos

	Vector3 pSysPos4 = { 235, 80, -15 };

	Vector3 pSysPos5 = { 1700, 80, -100 };

	Vector3 pSysPos6 = { 1700, 80, -60 };

	Vector3 pSysPos7 = { 1700, 80, -20 };

	Vector3 pSysPos8 = { 1700, 80, 20 };

	Vector3 pSysPos9 = { 1700, 80, 60 };


	for (int i = 0; i < 2; i++) {
		SolidoRigidoSystem* systema = new SolidoRigidoSystem(pSysPos4, mPx, mScene, mGMaterial, 9.8f, false, true, Lluvia2SD);
		systema->initSystem();
		systemasSolidosRigidos.push_back(systema);
		pSysPos4.x += 100;
	}

	for (int i = 0; i < 3; i++) {
		SolidoRigidoSystem* systema = new SolidoRigidoSystem(pSysPos5, mPx, mScene, mGMaterial, 9.8f, false, true, Lluvia2SD);
		systema->initSystem();
		systemasSolidosRigidos.push_back(systema);
		pSysPos5.x += 80;
	}
	for (int i = 0; i < 3; i++) {
		SolidoRigidoSystem* systema = new SolidoRigidoSystem(pSysPos6, mPx, mScene, mGMaterial, 9.8f, false, true, Lluvia2SD);
		systema->initSystem();
		systemasSolidosRigidos.push_back(systema);
		pSysPos6.x += 80;
	}
	for (int i = 0; i < 3; i++) {
		SolidoRigidoSystem* systema = new SolidoRigidoSystem(pSysPos7, mPx, mScene, mGMaterial, 9.8f, false, true, Lluvia2SD);
		systema->initSystem();
		systemasSolidosRigidos.push_back(systema);
		pSysPos7.x += 80;
	}
	for (int i = 0; i < 3; i++) {
		SolidoRigidoSystem* systema = new SolidoRigidoSystem(pSysPos8, mPx, mScene, mGMaterial, 9.8f, false, true, Lluvia2SD);
		systema->initSystem();
		systemasSolidosRigidos.push_back(systema);
		pSysPos8.x += 80;
	}
	for (int i = 0; i < 3; i++) {
		SolidoRigidoSystem* systema = new SolidoRigidoSystem(pSysPos9, mPx, mScene, mGMaterial, 9.8f, false, true, Lluvia2SD);
		systema->initSystem();
		systemasSolidosRigidos.push_back(systema);
		pSysPos9.x += 80;
	}

	//Gravedad

	gravedadG = new GravityForceGenerator(gravity, simulado);
	forceGenerators.push_back(gravedadG);
	std::cout << "creada Gravedad" << std::endl;

	//Generadores de viento en las 4 direcciones

	ForceGenerator* forceGenV1 = new WindForceGenerator(Vector3(-10000, 0, 0), 2, 0); // Izq
	addCreatedForceGenerator(forceGenV1);
	ForceGenerator* forceGenV2 = new WindForceGenerator(Vector3(10000, 0, 0), 2, 0); // Der
	addCreatedForceGenerator(forceGenV2);
	ForceGenerator* forceGenV3 = new WindForceGenerator(Vector3(0, 0, 10000), 2, 0); // Atras
	addCreatedForceGenerator(forceGenV3);
	ForceGenerator* forceGenV4 = new WindForceGenerator(Vector3(0, 0, -10000), 2, 0); // Adelante
	addCreatedForceGenerator(forceGenV4);

	//Obstaculos

	SolidoRigido* solidoDinamico = createNewSD({ 1050,150,0 }, { 3, 160, 50 }, { 0,0,0 }, { 0,0,0 }, CUBO, mPx, mScene, 0.1, 100, { 0,0,0,1 }, false, false, false);
	physx::PxRigidBodyExt::updateMassAndInertia(*solidoDinamico->getRigidDynamic(), 0.1);
	forceRegistriesSD.addRegistry(solidoDinamico, gravedadG);


	/*ForceGenerator* fg2 = createNewForceGenerator(VientoSD);
	std::cout << "creado Viento" << std::endl;*/
	player = createNewPlayer({ 0,100,0 }, { 5, 5, 5 }, { 0,0,0 }, { 0,0,0 }, ESFERA, mPx, mScene, 5, { 0.8,0.8,0.8,1 }, false, false);
	physx::PxRigidBodyExt::updateMassAndInertia(*player->getRigidDynamic(), 5);

	for (auto e : forceGenerators) {
		forceRegistriesSD.addRegistry(player, e);
	}
	/*ForceGenerator* fg2 = createNewForceGenerator(Viento);
	std::cout << "creado Viento" << std::endl;
	ForceGenerator* fg3 = createNewForceGenerator(Torbellino);
	std::cout << "creado Torbellino" << std::endl;*/
	/*ForceGenerator* fg5 = createNewForceGenerator(Muelle);
	std::cout << "creado Muelle" << std::endl;*/
}



void Nivel1Juego::updateLevel(double dt)
{
	for (auto it : particlesSystems) {
		it->updateSystem(dt);
	}
	for (auto it : systemasSolidosRigidos) {
		it->updateSystem(dt);
	}

	float distanciaMinima = 80; // Distancia mínima para cambiar el color

	if (rendersAnclaje.size() != puntosAnclaje.size()) {
		std::cerr << "Error: Las listas no están sincronizadas" << std::endl;
		return;
	}

	for (int i = 0; i < puntosAnclaje.size(); i++) {
		Vector3 relative_pos_vector = (puntosAnclaje[i]->getGlobalPose().p - player->getPos());
		float distancia = relative_pos_vector.magnitude();

		if (distancia <= distanciaMinima) {
			rendersAnclaje[i]->color = { 0.0f, 1.0f, 0.0f, 1.0f }; // Verde
		}
		else {
			rendersAnclaje[i]->color = { 0.1f, 0.1f, 0.1f, 1.0f }; // Negro
		}

		// Actualizar render (si es necesario)
		// rendersAnclaje[i]->updateColor(); // Solo si tu motor lo requiere
	}

	forceRegistriesSD.updateForces(dt);
	forceRegistriesSDMuelles.updateForces(dt);
	for (auto it = solidosRigidos.begin(); it != solidosRigidos.end();) {
		SolidoRigido* sd = *it;

		sd->update(dt);

		if (sd->ToErase()) {
			forceRegistriesSD.remove(sd);
			it = solidosRigidos.erase(it);
			delete sd;
		}
		else {
			++it;
		}
	}
}

void Nivel1Juego::pressKey(char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	switch (toupper(key))
	{
	case 'G':
	{
		//Invierte la gravedad
		gravedadG->reverseGravity();
		break;
	}
	case 'H':
	{
		//switch de la gravedad
		//gravedadG->SwitchOnOff();
		break;
	}
	case 'F':
	{
		//Invierte la gravedad
		player->jump(50000);
		break;
	}
	//Activacion de sistemas de viento
	case 'J':
	{
		forceGenerators[1]->SwitchOnOff(); //IZQ
		break;
	}
	case 'L':
	{
		forceGenerators[2]->SwitchOnOff(); //DER
		break;
	}
	case 'K':
	{
		forceGenerators[3]->SwitchOnOff(); //ATRAS
		break;
	}
	case 'I':
	{
		forceGenerators[4]->SwitchOnOff(); //ADELANTE
		break;
	}
	case 'Z':
	{
		if (muelles.size() < 1) {
			float distanciaMinima = 10000000000000000000; //Nos tenemos que quedar con la distancia mas corta, la que corresponde al punto de anclaje mas cercano
			PxRigidStatic* puntoAnclajeCercano;

			for (auto p : puntosAnclaje) {
				Vector3 relative_pos_vector = (p->getGlobalPose().p - player->getPos());
				float distancia = relative_pos_vector.magnitude();
				if (distancia < distanciaMinima) {
					distanciaMinima = distancia;
					puntoAnclajeCercano = p;
				}
			}

			if (distanciaMinima < 80) {
				SpringForceGenerator* sfg = new SpringForceGenerator(puntoAnclajeCercano->getGlobalPose().p, nullptr, nullptr, 2000, 10);

				muelles.push_back(sfg);
				forceRegistriesSDMuelles.addRegistry(player, sfg);
				std::cout << "muelles Creados" << std::endl;

			}
		}
		else {
			std::cout << "no se pueden crear mas muelles" << std::endl;
		}
		break;
	}
	case 'X':
	{
		muelles.clear();
		forceRegistriesSDMuelles.clearRegistries();
		break;
	}
	default:
		break;
	}

}

SolidoRigido* Nivel1Juego::createNewSD(Vector3 Pos, Vector3 Geo, Vector3 LinVel, Vector3 AngVel, FormaSolidoDinamico Type,
	physx::PxPhysics* Px, physx::PxScene* Scene, float Mass, double LifeTime, Vector4 Color, bool CanDie, bool ManualConfigLinVel, bool ManualConfigAngVel)
{
	SolidoRigido* sd = new SolidoRigido(Pos, Geo, LinVel, AngVel, Type, Px, Scene, Mass, LifeTime, Color, CanDie, ManualConfigLinVel, ManualConfigAngVel);
	addCreatedSD(sd);
	return sd;
}

Player* Nivel1Juego::createNewPlayer(Vector3 Pos, Vector3 Geo, Vector3 LinVel, Vector3 AngVel, FormaSolidoDinamico Type, physx::PxPhysics* Px, physx::PxScene* Scene, float Mass, Vector4 Color, bool ManualConfigLinVel, bool ManualConfigAngVel)
{
	Player* player = new Player(Pos, Geo, LinVel, AngVel, Type, Px, Scene, Mass, Color, ManualConfigLinVel, ManualConfigAngVel);
	addCreatedSD(player);
	return player;
}

ParticlesSystem* Nivel1Juego::createNewParticlesSystem(Vector3 Origin, float Gravity, float TimeSpawn, bool Simulado, bool NormalDistribution, Sistema type)
{
	ParticlesSystem* system = new ParticlesSystem(Origin, Gravity, TimeSpawn, Simulado, NormalDistribution, type);
	particlesSystems.push_back(system);
	return system;
}
