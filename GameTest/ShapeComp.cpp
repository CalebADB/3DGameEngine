#include "stdafx.h"

namespace ge
{
    void GShapeComp::Update(float deltaTime)
    {

    }
    void GShapeComp::Render()
    {

    }

    math::MVector3 GShapeComp::GetShapeColor()
    {
        return Color;
    }


    void GSphereShapeComp::SetDimensions(GLfloat Radius)
    {
        this->Radius = Radius;
    }

    GLfloat GSphereShapeComp::GetSignedDistanceFrom(math::MVector3 GlobalPosition)
    {
        return (GlobalPosition - GetGlobalTransformData().Position).Magnitude() - Radius;
    }

};
