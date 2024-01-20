#include "stdafx.h"

//using namespace ge::math

namespace ge
{
	void GPhysicalComp::Begin()
	{
		MaxCollisionBound = GAMEWORLD->NewComp<GSphereShapeComp>("MaxCollisionBound");
		AttachComp(this, MaxCollisionBound);
		MaxCollisionBound->SetDimensions(1.0f);
	}

	void GPhysicalComp::Initialize(GLfloat Mass, math::MVector3 Acceleration, math::MVector3 Velocity)
	{
		this->Mass = Mass;
		this->Acceleration = Acceleration;
		this->Velocity = Velocity;
	}

	void GPhysicalComp::Update(float deltaTime)
	{
		GSceneComp::Update(deltaTime);

		Displace();
	}

	void GPhysicalComp::AddShape(GShapeComp* RootShape, GShapeComp* Shape, GLfloat Mass)
	{
		if (RootShape == nullptr)
		{
			AttachComp(this, Shape);
		}
		else
		{
			AttachComp(RootShape, Shape);
		}
		
		Shapes.push_back(Shape);

		this->Mass += Mass;
	}

	void GPhysicalComp::SetGravity(math::MVector3 Gravity)
	{
		Acceleration = Gravity;
	}

	bool GPhysicalComp::CheckCollisionWith(GPhysicalComp* PhysicalComp)
	{
		//CHECK SHAPES

		return false;
	}
	void GPhysicalComp::AddLinearImpulse(math::MVector3 Impulse)
	{
		Velocity = Velocity + (Impulse / Mass);
	}

};
