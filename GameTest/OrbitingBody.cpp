#include "stdafx.h"

namespace ge
{
    void AOrbitingBody::Begin()
    {
        MeshComp = GAMEWORLD->NewComp<GEssentialMeshComp>(std::string("EssentialMeshComp"));
        AttachComp(this, MeshComp);

        OrbitComp = GAMEWORLD->NewComp<GOrbitComp>(std::string("OrbitComp"));
        AttachComp(this, OrbitComp);

        AActor::Begin();
    }

    void AOrbitingBody::Initialize(GLfloat Radius, GLfloat AngularSpeed, GLfloat AngularDistance, math::MVector3 Axis)
    {
        OrbitComp->Initialize(Radius, AngularSpeed, AngularDistance, Axis);
    }

    void AOrbitingBody::Update(float deltaTime)
    {
        math::MTransformData LocalTransformData = GetLocalTransformData();
        LocalTransformData.Position = OrbitComp->GetOrbitRelPosition();
        LocalTransformData.Rotation = OrbitComp->GetOrbitRelRotation();
        SetLocalTransformData(LocalTransformData);

        AActor::Update(deltaTime);
    }
    void AOrbitingBody::Render()
    {
        debug::Output(debug::EOutputType::Render, "Rendering AEssentialShape_%s ", GetCharName());

        AActor::Render();
    }

    void AOrbitingBody::SetEssentialShapeType(EEssentialShapeType Type, bool bIsSolid)
    {
        MeshComp->SetEssentialShapeType(Type, bIsSolid);
    }

};
