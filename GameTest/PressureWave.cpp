#include "stdafx.h"

namespace ge
{
    void APressureWave::Begin()
    {
        AActor::Begin();

        PhysicalComp = GAMEWORLD->NewComp<GPressureWavePhysicalComp>(std::string("PressureWavePhysicalComp"));
        AttachComp(this, PhysicalComp);

        //MeshComp = GAMEWORLD->NewComp<GEssentialMeshComp>(std::string("EssentialMeshComp"));
        //AttachComp(this, MeshComp);
        //MeshComp->SetEssentialShapeType(EEssentialShapeType::Cone, false);

    }

    void APressureWave::Update(float deltaTime)
    {


        AActor::Update(deltaTime);
    }
    void APressureWave::Render()
    {


        AActor::Render();
    }

};
