#include "stdafx.h"

namespace ge
{
    void GShapeComp::Initialize(bool bIsRendered, math::MVector3 Color)
    {
        this->bIsRendered = bIsRendered;
        this->Color = Color;
    }

    void GShapeComp::RenderSceneData()
    {
        GSceneComp::RenderSceneData();

        glColor3f(Color.X, Color.Y, Color.Z);
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

    void GSphereShapeComp::Initialize(GLfloat Radius, bool bIsRendered, math::MVector3 Color)
    {
        GShapeComp::Initialize(bIsRendered, Color);

        this->Radius = Radius;

        DebugShape->SetLocalTransformData(math::MTransformData(math::MVector3(0, 0, 0), math::MQuaternion::Identity(), math::MVector3(Radius, Radius, Radius)));

        GAMEWORLD->RenderManagerComp->AddShapeComp(this);
    }

    void GShapeComp::Destroy()
    {
        GAMEWORLD->RenderManagerComp->RemoveShapeComp(this);

        GSceneComp::Destroy();
    }

    GLfloat GSphereShapeComp::GetSignedDistanceFrom(math::MVector3 GlobalPosition)
    {
        return (GlobalPosition - GetGlobalTransformData().Position).Magnitude() - Radius;
    }
};
