#include "stdafx.h"

namespace ge
{
    void GOrbitComp::Initialize(GLfloat Radius, GLfloat AngularSpeed, GLfloat AngularDistance, math::MVector3 Axis)
    {
        this->Radius = Radius;
        this->AngularSpeed = AngularSpeed;
        this->AngularDistance = AngularDistance;
        this->Axis = Axis;
    }
    void GOrbitComp::Update(float deltaTime)
    {
        AngularDistance += AngularSpeed * deltaTime;
    }
    math::MVector3 GOrbitComp::GetOrbitRelPosition()
    {
        math::MVector3 BaseRadialDisplacement = math::MVector3(Radius, 0, 0);
        math::MQuaternion OrbitRotation = math::MQuaternion::FromAxisAngle(Axis, AngularDistance);

        return BaseRadialDisplacement.RotatedBy(OrbitRotation);;
    }
    math::MQuaternion GOrbitComp::GetOrbitRelRotation()
    {
        math::MVector3 BaseRadialDisplacement = math::MVector3(1, 0, 0);
        math::MQuaternion OrbitRotation = math::MQuaternion::FromAxisAngle(Axis, -(AngularDistance + (AngularSpeed > 0 ? (math::M_PI / 1.0f) : 0.0f )));

        return OrbitRotation;
    }
};
