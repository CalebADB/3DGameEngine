#include "stdafx.h"

namespace ge
{
    void AProjectile::Begin()
    {
        AActor::Begin();

        PhysicalComp = GAMEWORLD->NewComp<GPropPhysicalComp>(std::string("PropPhysicalComp"));
        AttachComp(this, PhysicalComp);

        //MeshComp = GAMEWORLD->NewComp<GEssentialMeshComp>(std::string("EssentialMeshComp"));
        //AttachComp(this, MeshComp);
        //MeshComp->SetEssentialShapeType(EEssentialShapeType::Cone, false);
    }

    void AProjectile::Update(float deltaTime)
    {


        AActor::Update(deltaTime);
    }
    void AProjectile::Render()
    {


        AActor::Render();
    }

};
