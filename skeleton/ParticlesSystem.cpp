#include "ParticlesSystem.h"
#include "core.hpp"
#include <iostream>
ParticlesSystem::ParticlesSystem(Vector3 Origin, float SpeedSim, float GravitySim, float MassSim, float Gravity, float TimeSpawn, bool Simulado, bool NormalDistribution, Sistema type) :
	origen(Origin), speedSim(SpeedSim), gravitySim(GravitySim), massSim(MassSim), gravity(Gravity), timeSpawn(TimeSpawn), simulado(Simulado), normalDistribution(NormalDistribution), tipoSistema(type), canCreateParticle(true)
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
	ForceGenerator* fg = createNewForceGenerator(Gravedad);
	std::cout << "creada Gravedad" << std::endl;
	ForceGenerator* fg2 = createNewForceGenerator(Viento);
	std::cout << "creado Viento" << std::endl;
	ForceGenerator* fg3 = createNewForceGenerator(Torbellino);
	std::cout << "creado Torbellino" << std::endl;
	/*ForceGenerator* fg4 = createNewForceGenerator(Explosion);
	std::cout << "creada Explosion" << std::endl;*/
}

void ParticlesSystem::particlesGenerator() {

	switch (tipoSistema) {
	case Fuente:
		generateParticleFuente();
		break;
	case Lluvia:
		generateParticleLluvia();
		break;
	case Niebla:
		generateParticleNiebla();
		break;
	default:
		break;
	}
}

void ParticlesSystem::generateParticleFuente() {
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
	Particle* proyectil = createNewParticle(origen, initialVel, initialAcel, 0.98, true, true, 0.25f, masa, gravity, simulado, velReal, velSim);
}

void ParticlesSystem::generateParticleLluvia() {
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
	Particle* proyectil = createNewParticle(origen, initialVel, initialAcel, 0.98, true, true, 0.25f, 5, gravity, simulado, velReal, velSim);
}

void ParticlesSystem::generateParticleNiebla() {
	double velX = 0.001f;
	double velY = -0.0001f;
	double velZ = 0.001f;
	if (!normalDistribution) {
		origen.x = (_uNiebla(_mt));
		origen.y = (_uNiebla(_mt));
		origen.z = (_uNiebla(_mt));

		velX *= (_u(_mt) - 0.5);
		velY *= (_u(_mt) - 0.5);
		velZ *= (_u(_mt) - 0.5);
	}
	else {
		origen.x = (_nNiebla(_mt));
		origen.y = (_nNiebla(_mt));
		origen.z = (_nNiebla(_mt));

		velX *= (_n(_mt));
		velY *= (_n(_mt));
		velZ *= (_n(_mt));
	}

	//le envio una gravedad modificada puesto que por ahora no hay rozamiento con el aire implementeado para modificar la  velocidad de la particula
	float masa = 0.01f;
	Vector3 initialVel(velX, velY, velZ);
	Vector3 initialAcel(0, -gravity*0.0095f, 0);
	Particle* particula = createNewParticle(origen, initialVel, initialAcel, 0.98, true, true, 0.1f, masa, gravity*0.0095f, false, 1.0f, 0.5f);
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
		particlesGenerator();
	}

	for (auto it = particles.begin(); it != particles.end(); ) {
		Particle* particle = *it;  // Obtener el puntero de la partícula

		if (particle != nullptr) {  // Verifica que la partícula no sea nula

			for (auto it2 = forceGenerators.begin(); it2 != forceGenerators.end(); ) {
				ForceGenerator* fG = *it2;  // Obtener el puntero del generador de fuerzas
				fG->applyForce(particle);
				fG->update(dt);
				it2++;
			}
			
			particle->integrate(dt);  // Actualiza la partícula
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
		
		Particle* proyectil = createNewParticle(camera.p, initialVel, initialAcel, 0.98, true, true, 0.5f, 5, gravity, false, 100, 5);
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
		Particle* proyectil = createNewParticle(camera.p, initialVel, initialAcel, 0.98, true, true, 1, 20, gravity, false, 10, 5);
		break;
	}
	default:
		break;
	}

}

Particle* ParticlesSystem::createNewParticle(Vector3 Pos, Vector3 Vel, Vector3 Acel, double Damping, bool ConstantAcel, bool CanHaveAccForce, float Radius, float Masa, float Gravedad,
	bool Simulado, float VelR, float VelS)
{
	Particle* part = new Particle(Pos, Vel, Acel, Damping, ConstantAcel, CanHaveAccForce, Radius, Masa, Gravedad, Simulado, VelR, VelS);
	addCreatedParticle(part);
	return part;
}

ForceGenerator* ParticlesSystem::createNewForceGenerator(GeneradorFuerzas type)
{
	ForceGenerator* forceGen;
	switch (type) {
	case Gravedad:

		forceGen = new GravityForceGenerator(gravity, simulado);
		break;
	case Viento:
		forceGen = new WindForceGenerator(Vector3(30,0,0), 2, 0);
		break;
	case Torbellino:
		forceGen = new WhirlwindForceGenerator(Vector3(0, 10, 0), 30);
		break;
	case Explosion:
		forceGen = new ExplosionForceGenerator(Vector3(0, 0, 0), 1000, 20, 0.1f);
	}
	addCreatedForceGenerator(forceGen);
	return forceGen;
}
