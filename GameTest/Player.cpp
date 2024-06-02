#include "stdafx.h"

namespace ge
{
    void APlayer::Begin()
    {
        AActor::Begin();

        PhysicalComp = GAMEWORLD->NewComp<GPlayerPhysicalComp>(std::string("PlayerPhysicalComp"));
        AttachComp(this, PhysicalComp);

        PlanetNavigationComp = GAMEWORLD->NewComp<GPlanetNavigationComp>(std::string("PlanetNavigationComp"));
        AttachComp(this, PlanetNavigationComp);

        FirstPersonCameraComp = GAMEWORLD->NewComp<GCameraComp>(std::string("CameraComp"));
        AttachComp(this, FirstPersonCameraComp);

        ControllerComp = GAMEWORLD->NewComp<GPlayerControllerComp>(std::string("PlayerControllerComp"));
        AttachComp(this, ControllerComp);

        ShapeComp = GAMEWORLD->NewComp<GSphereShapeComp>(std::string("PlayerShapeComp"));
        AttachComp(PhysicalComp, ShapeComp);
        PhysicalComp->AddShape(ShapeComp);
    }
    void APlayer::Initialize(GLfloat Mass, math::MVector3 Acceleration, math::MVector3 Velocity, GLfloat GroundDisplacement, GLfloat PlayerRadius, math::MVector3 Color)
    {
        PhysicalComp->Initialize(Mass, Acceleration, Velocity);
        PlanetNavigationComp->Initialize(PhysicalComp, GroundDisplacement);
        ControllerComp->Initialize(PhysicalComp);
        ShapeComp->Initialize(PlayerRadius, true, Color);
    }
    void APlayer::Update(float deltaTime)
    {
        AActor::Update(deltaTime);

        debug::Output(debug::EOutputType::Update, "Updating APlayer_%s ", GetCharName());
    }
    void APlayer::Render()
    {
        AActor::Render();

        debug::Output(debug::EOutputType::Render, "Rendering APlayer_%s ", GetCharName());
    }

};
