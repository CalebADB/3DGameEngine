#include "stdafx.h"

//using namespace ge::math

namespace ge
{
	void GPlayerControllerComp::Initialize()
	{
		GAMEWORLD->PhysicsManagerComp->AddPlayerControllerComps(this);
	}

	void GPlayerControllerComp::Update(float deltaTime)
	{
		GComp::Update(deltaTime);

		UpdateFrameImpulse(deltaTime);

	}

	void GPlayerControllerComp::SetPhysicsType(const EPhysicsType PhysicsType)
	{
		this->PhysicsType = PhysicsType;

		switch (PhysicsType)
		{
		case EPhysicsType::Space:
		{

			break;
		}
		case EPhysicsType::PlanetSurface:
		{

			break;
		}
		}
	}

	void GPlayerControllerComp::SetLocalUp(math::MVector3 LocalUp)
	{
		this->LocalUp = LocalUp;
	}

	math::MVector3 GPlayerControllerComp::GetLinearDisplacement(float deltaTime)
	{
		//this will ideally handle a rotated camera but its 9 on sunday and the projection matrix is still wack
		return Impulse * deltaTime;
	}

	math::MVector3 GPlayerControllerComp::GetJumpImpulse()
	{
		bIsJumpQueued = false;

		return LocalUp * bIsJumpImpulseFactor;
	}

	void GPlayerControllerComp::UpdateFrameImpulse(float deltaTime)
	{
		Impulse = math::MVector3::ZeroVector();

		if (App::IsKeyPressed(0x41)) // A Key
		{
			Impulse = Impulse + math::MVector3::LeftVector();
		}
		if (App::IsKeyPressed(0x57)) // W Key
		{
			Impulse = Impulse + math::MVector3::ForwardVector();
		}
		if (App::IsKeyPressed(0x44)) // D Key
		{
			Impulse = Impulse + math::MVector3::RightVector();

		}
		if (App::IsKeyPressed(0x53)) // S Key
		{
			Impulse = Impulse + math::MVector3::BackwardVector();
		}


		switch (PhysicsType)
		{
		case EPhysicsType::Space:
		{
			if (App::IsKeyPressed(0x51)) // Q Key
			{
				Impulse = Impulse + math::MVector3::UpVector();
			}
			if (App::IsKeyPressed(0x45)) // E Key
			{
				Impulse = Impulse + math::MVector3::DownVector();
			}

			Impulse = Impulse * SpaceSpeed;
			break;
		}
		case EPhysicsType::PlanetSurface:
		{
			if (App::IsKeyPressed(VK_SPACE)) // Space Key
			{
				Impulse = Impulse + math::MVector3::BackwardVector();
			}

			Impulse = Impulse * SurfaceSpeed;
			break;
		}
		}
	}
};
