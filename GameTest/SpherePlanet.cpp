#include "stdafx.h"

namespace ge
{
    void ASpherePlanet::Begin()
    {
        APlanet::Begin();

        GravityWellComp = GAMEWORLD->NewComp<GSphereGravityWellComp>(std::string("SphereGravityWellComp1"));
        AttachComp(this, GravityWellComp);
        GravityWellComps.push_back(GravityWellComp);

        ShapeComp = GAMEWORLD->NewComp<GSphereShapeComp>(std::string("SphereGravityWellComp1"));
        AttachComp(PhysicalComp, ShapeComp);
        PhysicalComp->AddShape(ShapeComp);
    }

    void ASpherePlanet::Initialize(GLfloat Mass, math::MVector3 Acceleration, math::MVector3 Velocity, GLfloat SurfaceRadius, GLfloat GravityStrength, GLfloat GravityReachRadius, math::MVector3 Color)
    {
        APlanet::Initialize(Mass, Acceleration, Velocity);

        ShapeComp->Initialize(SurfaceRadius, Color);
        GravityWellComp->Initialize(GravityStrength, GravityReachRadius, Color);
    }

    void ASpherePlanet::Update(float deltaTime)
    {
        APlanet::Update(deltaTime);
    }
    void ASpherePlanet::Render()
    {
        APlanet::Render();
    }

};
