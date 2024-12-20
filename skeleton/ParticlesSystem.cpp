#include "ParticlesSystem.h"
#include "core.hpp"
#include <iostream>
ParticlesSystem::ParticlesSystem(Vector3 Origin, float Gravity, float TimeSpawn, bool Simulado, bool NormalDistribution, Sistema type) :
	origen(Origin), gravity(Gravity), timeSpawn(TimeSpawn), simulado(Simulado), normalDistribution(NormalDistribution), tipoSistema(type), canCreateParticle(true)
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
	if (tipoSistema == Remolino) {
		ForceGenerator* fg2 = createNewForceGenerator(Torbellino);
		std::cout << "creado Torbellino" << std::endl;

	}
	/*ForceGenerator* fg2 = createNewForceGenerator(Viento);
	std::cout << "creado Viento" << std::endl;*/
	/*ForceGenerator* fg4 = createNewForceGenerator(Explosion);
	std::cout << "creada Explosion" << std::endl;*/
	/*ForceGenerator* fg3 = createNewForceGenerator(Torbellino);
	std::cout << "creado Torbellino" << std::endl;*/
	/*ForceGenerator* fg4 = createNewForceGenerator(Explosion);
	std::cout << "creada Explosion" << std::endl;*/
	/*ForceGenerator* fg5 = createNewForceGenerator(Muelle);
	std::cout << "creado Muelle" << std::endl;*/
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
	case Remolino:
		generateParticleRemolino();
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
	float radius = 0.25f;

	std::random_device rd;
	std::mt19937 gen(rd());

	// Definimos una distribuci�n uniforme de enteros entre 1 y 3 (inclusive)
	std::uniform_int_distribution<> dis(1, 3);

	// Generamos un n�mero aleatorio
	int random_number = dis(gen);
	int rand = std::rand();
	if (random_number == 3) {
		masa *= 2;
		radius *= 2;
	}


	float velReal = 10.0f;
	float velSim = 5.0f;
	Vector3 initialVel(velX, velY, velZ);
	Vector3 initialAcel(0, gravity, 0);
	Particle* proyectil = createNewParticle(Esfera, origen, initialVel, initialAcel, true, true, simulado, radius, masa, gravity, 0.98, 2, velReal, velSim);
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
	float radius = 0.25f;

	std::random_device rd;
	std::mt19937 gen(rd());

	// Definimos una distribuci�n uniforme de enteros entre 1 y 3 (inclusive)
	std::uniform_int_distribution<> dis(1, 3);

	// Generamos un n�mero aleatorio
	int random_number = dis(gen);
	int rand = std::rand();
	if (random_number == 3) {
		masa *= 3;
		radius *= 3;
	}

	float velReal = 10.0f;
	float velSim = 5.0f;
	Vector3 initialVel(0, velY, 0);
	Vector3 initialAcel(0, gravity, 0);
	Particle* proyectil = createNewParticle(Esfera, origen, initialVel, initialAcel, true, true, simulado, radius, masa, gravity, 0.98, 10, velReal, velSim);
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
	Particle* particula = createNewParticle(Esfera, origen, initialVel, initialAcel, true, true, false, 0.1f, masa, gravity*0.0095f, 0.98, 2, 1.0f, 0.5f);
}

void ParticlesSystem::generateParticleRemolino()
{
	double velX = 1;
	double velY = 0.5f;
	double velZ = 1;
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
	float radius = 0.5f;

	std::random_device rd;
	std::mt19937 gen(rd());

	// Definimos una distribuci�n uniforme de enteros entre 1 y 3 (inclusive)
	std::uniform_int_distribution<> dis(1, 3);

	// Generamos un n�mero aleatorio
	int random_number = dis(gen);
	int rand = std::rand();
	if (random_number == 3) {
		masa *= 2;
		radius *= 2;
	}


	float velReal = 10.0f;
	float velSim = 5.0f;
	Vector3 initialVel(velX, velY, velZ);
	Vector3 initialAcel(0, gravity, 0);
	Particle* proyectil = createNewParticle(Esfera, origen, initialVel, initialAcel, true, true, simulado, radius, masa, gravity, 0.98, 2, velReal, velSim);
}

void ParticlesSystem::updateSystem(double dt)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	// Definimos una distribuci�n uniforme de enteros entre 1 y 100 (inclusive)
	std::uniform_int_distribution<> dis(1, 100);

	// Generamos un n�mero aleatorio
	int random_number = dis(gen);
	int rand = std::rand();
	if (random_number <= 75) {
		particlesGenerator();
	}

	for (auto it = particles.begin(); it != particles.end(); ) {
		Particle* particle = *it;  // Obtener el puntero de la part�cula

		if (particle != nullptr) {  // Verifica que la part�cula no sea nula

			for (auto it2 = forceGenerators.begin(); it2 != forceGenerators.end(); ) {
				ForceGenerator* fG = *it2;  // Obtener el puntero del generador de fuerzas
				fG->applyForce(particle);
				fG->update(dt);
				it2++;
			}
			
			particle->integrate(dt);  // Actualiza la part�cula
			if (/*particle->getPos().y <= 0.0f ||*/ particle->toErase()) {
				delete particle;  // Elimina la memoria de la part�cula
				it = particles.erase(it);  // Elimina la part�cula del vector y actualiza el iterador
			}
			else {
				++it;  // Solo avanza al siguiente elemento si no eliminaste el actual
			}
		}
		else {
			it = particles.erase(it);  // Si el puntero es nulo, lo eliminamos tambi�n
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
	default:
		break;
	}

}

Particle* ParticlesSystem::createNewParticle(FormaParticula Forma, Vector3 Pos, Vector3 Vel, Vector3 Acel, bool ConstantAcel, bool CanHaveAccForce, bool Simulado,
	float Radius, float Masa, float Gravedad, double Damping, double LifeTime, float VelR, float VelS)
{
	Particle* part = new Particle(Forma, Pos, Vel, Acel, ConstantAcel, CanHaveAccForce, Simulado, Radius, Masa, Gravedad, Damping, LifeTime, VelR, VelS);
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
		forceGen = new WhirlwindForceGenerator(origen, 50);
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
