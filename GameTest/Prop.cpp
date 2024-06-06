#include "stdafx.h"

namespace ge
{
    void AProp::Begin()
    {
        AActor::Begin();

        PhysicalComp = GAMEWORLD->NewComp<GPropPhysicalComp>(std::string("PropPhysicalComp"));
        AttachComp(this, PhysicalComp);

        PlanetNavigationComp = GAMEWORLD->NewComp<GPlanetNavigationComp >(std::string("PlanetNavigationComp"));
        AttachComp(this, PlanetNavigationComp);
    }
    void AProp::Initialize(GLfloat Mass, math::MVector3 Acceleration, math::MVector3 Velocity, GLfloat GroundDisplacement)
    {
        PhysicalComp->Initialize(Mass, Acceleration, Velocity);
        PlanetNavigationComp->Initialize(PhysicalComp, GroundDisplacement);
    }

    void AProp::Update(float deltaTime)
    {
        AActor::Update(deltaTime);
    }
    void AProp::Render()
    {
        AActor::Render();
    }

};
