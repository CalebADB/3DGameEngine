#include "stdafx.h"

namespace ge
{
    void APlayer::Begin()
    {
        AActor::Begin();

        PlanetNavigationComp = GAMEWORLD->NewComp<GPlanetNavigationComp >(std::string("PlanetNavigationComp"));

        GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape10"), this, math::MVector3(0.0, 0.0, 0.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Teapot, false);;
    }
    void APlayer::Initialize(GLfloat Mass, math::MVector3 Acceleration, math::MVector3 Velocity, GLfloat GroundDisplacement)
    {
        PhysicalComp->Initialize(Mass, Acceleration, Velocity);
        PlanetNavigationComp->Initialize(PhysicalComp, GroundDisplacement);

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
