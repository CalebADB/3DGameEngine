#include "stdafx.h"

namespace ge
{
    void AEssentialShape::Begin()
    {
        MeshComp = GAMEWORLD->NewComp<GEssentialMeshComp>(std::string("EssentialMeshComp"));
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

    void AEssentialShape::SetEssentialShapeType(EEssentialShapeType Type, bool bIsSolid)
    {
        MeshComp->SetEssentialShapeType(Type, bIsSolid);
    }

};
