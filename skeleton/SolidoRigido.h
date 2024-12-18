
#pragma once
#include <PxPhysicsAPI.h>
#include <iostream>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include <ctype.h>
#include <vector>
#include <list>

enum FormaSolidoDinamico { CUBO, ESFERA, PLANO, CAPSULA };

using namespace std;

class SolidoRigido
{
public:
    SolidoRigido(Vector3 Pos, Vector3 Geo, Vector3 LinVel, Vector3 AngVel, FormaSolidoDinamico Type,
        physx::PxPhysics* Px, physx::PxScene* Scene, float Mass, Vector4 Color, bool ManualConfigLinVel, bool ManualConfigAngVel)
        : mScene(Scene), masa(Mass) {

        rigidDynamic = Px->createRigidDynamic(physx::PxTransform(Pos));
        physx::PxShape* shape;

        // Ajuste para las dimensiones
        //Geo = ajustarUnidades(Geo); // Convertir a metros si es necesario

        switch (Type) {
        case CUBO:
            shape = CreateShape(physx::PxBoxGeometry(Geo.x, Geo.y, Geo.z));
            calcularMomentosDeInerciaCubo(Geo); // Calcular momentos de inercia manualmente
            break;
        case ESFERA:
            shape = CreateShape(physx::PxSphereGeometry(Geo.x)); // X = radio
            calcularMomentosDeInerciaEsfera(Geo.x);
            break;
        case PLANO:
            shape = CreateShape(physx::PxPlaneGeometry());
            break;
        case CAPSULA:
            shape = CreateShape(physx::PxCapsuleGeometry(Geo.x, Geo.y)); // X = radio, Y = altura
            break;
        default:
            break;
        }

        rigidDynamic->attachShape(*shape);
        std::cout << "Masa antes de setMass: " << rigidDynamic->getMass() << "\n";
        rigidDynamic->setMass(masa);
        std::cout << "Masa después de setMass: " << rigidDynamic->getMass() << "\n";

        // Dejar que PhysX calcule automáticamente la inercia
        //physx::PxRigidBodyExt::updateMassAndInertia(*rigidDynamic, masa);

        // Comparar los valores calculados por PhysX con los manuales
        compararInercias();

        if (ManualConfigLinVel) {
            rigidDynamic->setLinearVelocity(LinVel);
        }
        if (ManualConfigAngVel) {
            rigidDynamic->setAngularVelocity(AngVel);
        }

        renderItem = new RenderItem(shape, rigidDynamic, Color);
        mScene->addActor(*rigidDynamic);
        std::cout << "Masa después de setMass: " << rigidDynamic->getMass() << "\n";
        //mScene->setGravity(physx::PxVec3(0, 0, 0));
        //rigidDynamic->addForce({ 10000,0,0 }, physx::PxForceMode::eIMPULSE);
    }

    ~SolidoRigido() {
        mScene->removeActor(*rigidDynamic);
        rigidDynamic->release();
        if (renderItem) {
            DeregisterRenderItem(renderItem);
        }
    }

    physx::PxRigidDynamic* getRigidDynamic() {
        return rigidDynamic;
    }

    float getMasa() {
        return rigidDynamic->getMass();
        //return masa;
    }

    Vector3 getPos() {
        return rigidDynamic->getGlobalPose().p;
    }

    Vector3 getVel() {
        return rigidDynamic->getLinearVelocity();
    }

protected:
    physx::PxScene* mScene; // Puntero de la escena a la que está atachado el objeto
    float masa;
    RenderItem* renderItem; // Render item para el renderizado del objeto
    physx::PxRigidDynamic* rigidDynamic; // El tipo de objeto que crearemos, en este caso un solido rigido dinamico
    physx::PxVec3 momentosInerciaManual; // Para guardar los momentos de inercia calculados manualmente

    Vector3 ajustarUnidades(Vector3 dimensiones) {
        // Si las dimensiones están en cm, conviértelas a metros
        return Vector3(dimensiones.x / 100.0f, dimensiones.y / 100.0f, dimensiones.z / 100.0f);
    }

    void calcularMomentosDeInerciaCubo(Vector3 dimensiones) {
        // Fórmulas de momentos de inercia para un cubo homogéneo
        float Ix = (1.0f / 12.0f) * masa * (dimensiones.y * dimensiones.y + dimensiones.z * dimensiones.z);
        float Iy = (1.0f / 12.0f) * masa * (dimensiones.x * dimensiones.x + dimensiones.z * dimensiones.z);
        float Iz = (1.0f / 12.0f) * masa * (dimensiones.x * dimensiones.x + dimensiones.y * dimensiones.y);

        // Asignar los momentos de inercia manualmente
        momentosInerciaManual = physx::PxVec3(Ix, Iy, Iz);

        // Imprimir los momentos de inercia calculados manualmente
        std::cout << "Momentos de inercia del cubo (manuales): Ix = " << Ix << ", Iy = " << Iy << ", Iz = " << Iz << "\n";
    }

    void calcularMomentosDeInerciaEsfera(float radio) {
        // Fórmula de momento de inercia para una esfera homogénea
        float I = (2.0f / 5.0f) * masa * radio * radio;
        momentosInerciaManual = physx::PxVec3(I, I, I); // La esfera tiene el mismo momento en todos los ejes

        // Imprimir el momento de inercia calculado manualmente
        std::cout << "Momentos de inercia de la esfera (manuales): I = " << I << "\n";
    }

    void compararInercias() {
        // Obtener los momentos de inercia calculados automáticamente por PhysX
        physx::PxVec3 momentosInerciaPhysX = rigidDynamic->getMassSpaceInertiaTensor();

        // Comparar los resultados
        std::cout << "Momentos de inercia calculados por PhysX:\n";
        std::cout << "Ix = " << momentosInerciaPhysX.x << ", Iy = " << momentosInerciaPhysX.y << ", Iz = " << momentosInerciaPhysX.z << "\n";

        // Mostrar diferencias con los cálculos manuales
        std::cout << "Diferencias entre inercia manual y PhysX:\n";
        std::cout << "Ix = " << fabs(momentosInerciaManual.x - momentosInerciaPhysX.x) << ", "
            << "Iy = " << fabs(momentosInerciaManual.y - momentosInerciaPhysX.y) << ", "
            << "Iz = " << fabs(momentosInerciaManual.z - momentosInerciaPhysX.z) << "\n";
    }
};
