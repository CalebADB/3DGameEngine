#include "stdafx.h"

namespace ge
{
    void AEssentialShape::Begin()
    {
        //GAMEWORLD->SpawnActor<AActor>(std::string("Shape1"), this, math::MVector3(0.0, 0.0, 0.0), math::MQuaternion::Identity());

        //GAMEWORLD->NewComp<GComp>(std::string("EssentialMesh"));
        //MeshComp = 
        AttachComp(this, MeshComp);
    }

    void AEssentialShape::Update(float deltaTime)
    {
        debug::Output(debug::EOutputType::Update, "Updating AEssentialShape_%s ", GetCharName());

        AActor::Update(deltaTime);
    }
    void AEssentialShape::Render()
    {
        debug::Output(debug::EOutputType::Render, "Rendering AEssentialShape_%s ", GetCharName());

        AActor::Render();
    }

    void AEssentialShape::SetEssentialShapeType(EEssentialShapeType Type, bool bIsWired)
    {
        MeshComp->SetEssentialShapeType(Type, bIsWired);
    }

};
