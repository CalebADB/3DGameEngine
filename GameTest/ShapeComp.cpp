#include "stdafx.h"

namespace ge
{
    void GShapeComp::Initialize(math::MVector3 Color)
    {
        this->Color = Color;
    }

    math::MVector3 GShapeComp::GetShapeColor()
    {
        return Color;
    }


    void GSphereShapeComp::Begin()
    {
        GShapeComp::Begin();

        DebugShape = GAMEWORLD->NewComp<GEssentialMeshComp>("DebugShape");
        AttachComp(this, DebugShape);
        DebugShape->SetEssentialShapeType(EEssentialShapeType::SphereLP, false);
    }

    void GSphereShapeComp::Initialize(GLfloat Radius, math::MVector3 Color)
    {
        GShapeComp::Initialize(Color);

        this->Radius = Radius;

        DebugShape->SetLocalTransformData(math::MTransformData(math::MVector3(0, 0, 0), math::MQuaternion::Identity(), math::MVector3(Radius, Radius, Radius)));
    }

    void GSphereShapeComp::RenderSceneData()
    {
        GShapeComp::RenderSceneData();
    }

    GLfloat GSphereShapeComp::GetSignedDistanceFrom(math::MVector3 GlobalPosition)
    {
        return (GlobalPosition - GetGlobalTransformData().Position).Magnitude() - Radius;
    }
};
