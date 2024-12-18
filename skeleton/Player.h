#pragma once
#include "SolidoRigido.h"

class Player : public SolidoRigido
{
public:
    Player(Vector3 Pos, Vector3 Geo, Vector3 LinVel, Vector3 AngVel, FormaSolidoDinamico Type,
        physx::PxPhysics* Px, physx::PxScene* Scene, float Mass, Vector4 Color, bool ManualConfigLinVel, bool ManualConfigAngVel)
        : SolidoRigido(Pos, Geo, LinVel, AngVel, Type, Px, Scene, Mass, 0, Color, false, ManualConfigLinVel, ManualConfigAngVel) {}

    void jump(float force) {
        rigidDynamic->addForce({ 0,force,0 }, physx::PxForceMode::eIMPULSE);
        std::cout << "saltando" << std::endl;
    }
};

