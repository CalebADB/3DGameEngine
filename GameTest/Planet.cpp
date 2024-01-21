#include "stdafx.h"

namespace ge
{
    void APlanet::Begin()
    {
        AActor::Begin();

        PhysicalComp = GAMEWORLD->NewComp<GPlanetPhysicalComp>(std::string("PlanetPhysicalComp"));
        AttachComp(this, PhysicalComp);
    }

    void APlanet::Initialize(GLfloat Mass, math::MVector3 Acceleration, math::MVector3 Velocity)
    {
        PhysicalComp->Initialize(Mass, Acceleration, Velocity);
    }

    void APlanet::Update(float deltaTime)
    {
        AActor::Update(deltaTime);
    }
    void APlanet::Render()
    {
        AActor::Render();
    }

};
