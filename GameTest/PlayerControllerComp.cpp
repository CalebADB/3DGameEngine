#include "stdafx.h"

//using namespace ge::math

namespace ge
{
	void GPlayerControllerComp::Initialize(AParticleEffect* ParticleEffect, GPhysicalComp* PhysicalComp)
	{
		this->ParticleEffect = ParticleEffect;

		GAMEWORLD->PhysicsManagerComp->AddPlayerControllerComp(this);

		this->PhysicalComp = PhysicalComp;
	}

	void GPlayerControllerComp::Update(float deltaTime)
	{
		GComp::Update(deltaTime);

		UpdateFrameImpulse(deltaTime);
	}

	void GPlayerControllerComp::Destroy()
	{
		GAMEWORLD->PhysicsManagerComp->RemovePlayerControllerComp(this);

		GComp::Destroy();
	}

	void GPlayerControllerComp::SetLocalUp(math::MVector3 LocalUp)
	{
		this->LocalUp = LocalUp;
	}

	math::MVector3 GPlayerControllerComp::GetLinearDisplacement(float deltaTime)
	{
		ParticleEffect->DriveEffect(Impulse.Magnitude(), Impulse * -1);

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
			Impulse = Impulse + math::MVector3::LeftVector().RotatedBy(GetActorRoot()->GetGlobalTransformData().Rotation);
		}
		if (App::IsKeyPressed(0x57)) // W Key
		{
			Impulse = Impulse + math::MVector3::BackwardVector().RotatedBy(GetActorRoot()->GetGlobalTransformData().Rotation);
		}
		if (App::IsKeyPressed(0x44)) // D Key
		{
			Impulse = Impulse + math::MVector3::RightVector().RotatedBy(GetActorRoot()->GetGlobalTransformData().Rotation);
		}
		if (App::IsKeyPressed(0x53)) // S Key
		{
			Impulse = Impulse + math::MVector3::ForwardVector().RotatedBy(GetActorRoot()->GetGlobalTransformData().Rotation);
		}

		switch (PhysicalComp->GetPhysicsType())
		{
		case EPhysicsType::Space:
		{
			if (App::IsKeyPressed(0x51)) // Q Key
			{
				Impulse = Impulse + math::MVector3::UpVector().RotatedBy(GetActorRoot()->GetGlobalTransformData().Rotation);
			}
			if (App::IsKeyPressed(0x45)) // E Key
			{
				Impulse = Impulse + math::MVector3::DownVector().RotatedBy(GetActorRoot()->GetGlobalTransformData().Rotation);
			}

			Impulse = Impulse * SpaceSpeed;
			break;
		}
		case EPhysicsType::PlanetSurface:
		{
			if (App::IsKeyPressed(VK_SPACE)) // Space Key
			{
				bIsJumpQueued = true;
			}

			Impulse = Impulse * SurfaceSpeed;
			break;
		}
		}

		PhysicalComp->AddLinearImpulse(nullptr, Impulse);
	}
};
