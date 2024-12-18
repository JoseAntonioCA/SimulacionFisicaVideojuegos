#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "Particle.h"
#include "SolidoRigido.h"
#include "PhysicsScene.h"
#include "SolidoRigidoSystem.h"
#include "Nivel1Juego.h"

#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
RenderItem* xRenderItem = NULL, * yRenderItem = NULL, * zRenderItem = NULL;
PxTransform* x, *y, *z, *origin;
PxSphereGeometry* gSphere = new PxSphereGeometry(10);
Particle* particula;
PhysicsScene* escena1;
SolidoRigidoSystem* sdSys;
Nivel1Juego* level1;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);


	/*SolidoRigido* solidoDinamico = new SolidoRigido({ 0,0,0 }, { 10,10,10 }, { 0,0,0 }, { 0,0,0 }, ESFERA, gPhysics, gScene, 1, { 0.1,0.1,0.1,1 }, false, false);*/

	/*PxRigidDynamic* solidoDinamico = gPhysics->createRigidDynamic(physx::PxTransform(0, 0, 0));
	solidoDinamico->setLinearVelocity({ 0,0,0 });
	solidoDinamico->setAngularVelocity({ 0,3,0 });
	PxShape* shape2 = CreateShape(PxBoxGeometry(10, 10, 10));
	solidoDinamico->attachShape(*shape2);

	PxRigidBodyExt::updateMassAndInertia(*solidoDinamico, 0.15);
	gScene->addActor(*solidoDinamico);
	RenderItem* item2 = new RenderItem(shape2, solidoDinamico, { 0.1,0.1,0.1,1 });*/

	level1 = new Nivel1Juego({ 0,10,0 }, gPhysics, gScene, gMaterial, 9.8f, false);
	level1->initLevel();
	sdSys = new SolidoRigidoSystem({ 100,10,0 }, gPhysics, gScene, gMaterial, 9.8f, false, true, Lluvia2SD);
	sdSys->initSystem();
	/*escena1 = new PhysicsScene(false, 9.8f);
	escena1->initScene();*/
	}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	level1->updateLevel(t);
	//escena1->updateScene(t);
	sdSys->updateSystem(t);
	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	if (particula) {
		delete particula;
	}

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	//delete escena1;
	delete sdSys;
	delete level1;
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);
	
	//escena1->pressKey(key, camera);
	sdSys->pressKey(key, camera);
	level1->pressKey(key, camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case ' ':
	{
		break;
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}