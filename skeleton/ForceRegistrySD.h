#pragma once
#include <vector>
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "ForceGenerator.h"
#include "SolidoRigido.h"

class ForceRegistrySD
{
public:
	ForceRegistrySD() {}
	void addRegistry(SolidoRigido* sd, ForceGenerator* fg) {
		registries.push_back({ sd, fg });
	}
	void remove(SolidoRigido* sd) {
		for (auto it = registries.begin(); it != registries.end(); ) {
			if (it->sd == sd) {
				it = registries.erase(it); // Eliminar asociación y actualizar iterador
			}
			else {
				++it; // Avanzar solo si no se elimina
			}
		}
	}
	void clearRegistries() {
		registries.clear();
	}

	void updateForces(double dt) {
		for (ForceRegistrationSD& r : registries) {
			if (r.sd != nullptr) {
				r.fg->applyForce(r.sd);
				r.fg->update(dt);

			}
		}
	}




		
	

	//forceRegistriesSD.updateForces(dt);
	//for (auto it = solidosRigidos.begin(); it != solidosRigidos.end(); ) {
	//	SolidoRigido* sd = *it;  // Obtener el puntero de la partícula

	//	if (sd != nullptr) {  // Verifica que la partícula no sea nula


	//		//for (auto it2 = forceGenerators.begin(); it2 != forceGenerators.end(); ) {
	//		//	ForceGenerator* fG = *it2;  // Obtener el puntero del generador de fuerzas
	//		//	fG->applyForce(sd);
	//		//	fG->update(dt);
	//		//	it2++;
	//		//}

	//		sd->update(dt);  // Actualiza la partícula
	//		if (sd->ToErase()) {
	//			delete sd;  // Elimina la memoria de la partícula
	//			it = solidosRigidos.erase(it);  // Elimina la partícula del vector y actualiza el iterador
	//		}
	//		else {
	//			++it;  // Solo avanza al siguiente elemento si no eliminaste el actual
	//		}
	//		//it++;
	//	}
	//	else {
	//		it = solidosRigidos.erase(it);  // Si el puntero es nulo, lo eliminamos también
	//	}
	//}

private:
	struct ForceRegistrationSD {
		SolidoRigido* sd;
		ForceGenerator* fg;
	};
	std::vector<ForceRegistrationSD> registries;
};