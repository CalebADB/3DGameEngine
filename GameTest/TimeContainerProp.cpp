#include "stdafx.h"

namespace ge
{
    void ATimeContainerProp::Begin()
    {
        AProp::Begin();

        ShapeComp = GAMEWORLD->NewComp<GSphereShapeComp>(std::string("TimeContainerPropShapeComp"));
        AttachComp(PhysicalComp, ShapeComp);
        PhysicalComp->AddShape(ShapeComp);
    }
    void ATimeContainerProp::Initialize(GLfloat Mass, math::MVector3 Acceleration, math::MVector3 Velocity, GLfloat GroundDisplacement, GLfloat BoxEdgeLength, math::MVector3 Color)
    {
        AProp::Initialize(Mass, Acceleration, Velocity, GroundDisplacement);

        ShapeComp->Initialize(BoxEdgeLength, true, Color);
    }

    void ATimeContainerProp::Update(float deltaTime)
    {
        AProp::Update(deltaTime);
    }
    void ATimeContainerProp::Render()
    {
        AProp::Render();
    }

};
