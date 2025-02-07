#include "stdafx.h"

namespace ge
{
	void GPlanetNavigationComp::Initialize(GPhysicalComp* PhysicalComp, GLfloat GroundDisplacement)
	{
		this->PhysicalComp = PhysicalComp;
		this->GroundDisplacement = GroundDisplacement;

		GAMEWORLD->PhysicsManagerComp->AddPlanetNavigationComp(this);
	}
	void GPlanetNavigationComp::Update(float deltaTime)
	{
		GComp::Update(deltaTime);

		if (!IsEmbarked())
		{
			return;
		}

		if (NavigatorTangentialSpeed < 0.001f)
		{
			return;
		}
		math::MVector3 EulerDirection = math::MQuaternion::ToEuler(Direction);
		SphericalLocation = math::MQuaternion::FromEuler(EulerDirection.Normalized() * (deltaTime * NavigatorTangentialSpeed * PlanetRadius / 360) * math::M_PI) * SphericalLocation;

	}
	void GPlanetNavigationComp::Destroy()
	{
		GAMEWORLD->PhysicsManagerComp->RemovePlanetNavigationComp(this);

		GComp::Destroy();
	}
	void GPlanetNavigationComp::EmbarkOn(APlanet* Planet, math::MVector3 NavigatorVelocity)
	{		
		if (PhysicalComp->CheckOngoingCollision(Planet->GetPhysicalComp()))
		{
			return;
		}

		ASpherePlanet* SpherePlanet = (ASpherePlanet*)Planet;
		if (SpherePlanet == nullptr)
		{
			debug::Output(debug::EOutputType::Always, "Error: GPlanetNavigationComp_%s can only embark on ASpherePlanet due to competition restraints", GetCharName());
			return;
		}

		this->Planet = Planet;
		AActor* Navigator = (AActor*)GetActorRoot();
		Planet->AttachActor(Navigator);
		
		PhysicalComp->SetPhysicsType(EPhysicsType::PlanetSurface);

		math::MTransformData NavigatorTransformData = Navigator->GetGlobalTransformData();
		math::MTransformData PlanetTransformData = Planet->GetGlobalTransformData();
		math::MVector3 NavigatorUp = NavigatorTransformData.Position - PlanetTransformData.Position;
		math::MVector3 NavigatorTangentialVelocity = math::MVector3::ProjectOntoPlane(NavigatorVelocity, NavigatorUp);
		PlanetNorthPole = math::MVector3::UpVector().RotatedBy(PlanetTransformData.Rotation).Normalized();
		SphericalLocation = math::MQuaternion::RotationFromVectorToVector(PlanetNorthPole, NavigatorUp).Normalized();
		Direction = math::MQuaternion::RotationFromVectorToVector(NavigatorUp, NavigatorUp + NavigatorTangentialVelocity.Normalized()).Normalized();
		PlanetRadius = SpherePlanet->GetRadius();
		NavigatorTangentialSpeed = NavigatorTangentialVelocity.Magnitude();
	}
	void GPlanetNavigationComp::Disembark(GPhysicalComp* InstigatingPhysicalComp, math::MVector3 Impulse)
	{
		if (PhysicalComp->CheckOngoingCollision(InstigatingPhysicalComp))
		{
			return;
		}

		math::MVector3 NavigatorUp = GetNavigatorUp();
		if (!math::MVector3::IsOnSameSideAsNormal(Impulse, NavigatorUp))
		{
			Impulse = math::MVector3::ProjectOntoPlane(Impulse, NavigatorUp);
		}

		math::MVector3 TangentDirection = (NavigatorUp.RotatedBy(Direction) - NavigatorUp).Normalized();
		Impulse = Impulse + (TangentDirection * NavigatorTangentialSpeed * PhysicalComp->GetMass());
		PhysicalComp->AddLinearImpulse(InstigatingPhysicalComp, Impulse);

		// Force planet to not trap disembarking body 
		PhysicalComp->AddOngoingCollisionBufferFrames(Planet->GetPhysicalComp(), 1);
		
		PlanetNorthPole = math::MVector3::UpVector();
		SphericalLocation = math::MQuaternion::Identity();
		Direction = math::MQuaternion::Identity();
		PlanetRadius = 0.0f;
		NavigatorTangentialSpeed = 0.0f;

		PhysicalComp->SetPhysicsType(EPhysicsType::Space);

		Planet->DettachActor((AActor*)GetActorRoot());
		Planet = nullptr;
	}

	math::MTransformData GPlanetNavigationComp::GetLocalTransformData()
	{		
		math::MTransformData LocalTransformData = math::MTransformData::Identity();
		LocalTransformData.Position = (math::MVector3(0,1,0) * (PlanetRadius + GroundDisplacement)).RotatedBy(SphericalLocation.Normalized());
		LocalTransformData.Rotation = SphericalLocation.Normalized();
		math::MVector3 EulerRotation = math::MQuaternion::ToEuler(SphericalLocation);
		return LocalTransformData;
	}

	APlanet* GPlanetNavigationComp::GetEmbarkedPlanet() const
	{
		return Planet;
	}

	math::MVector3 GPlanetNavigationComp::GetNavigatorUp()
	{
		return PlanetNorthPole.RotatedBy(SphericalLocation);
	}
};
