#include "stdafx.h"

namespace ge
{
	void GPlayerPlanetNavigationComp::Initialize(GPhysicalComp* PhysicalComp, GLfloat GroundDisplacement, GPlayerControllerComp* PlayerControllerComp)
	{
		GPlanetNavigationComp::Initialize(PhysicalComp, GroundDisplacement);

		this->PlayerControllerComp = PlayerControllerComp;
	}
	void GPlayerPlanetNavigationComp::EmbarkOn(APlanet* Planet, math::MVector3 NavigatorVelocity)
	{
		GPlanetNavigationComp::EmbarkOn(Planet, NavigatorVelocity);

		PlayerControllerComp->SetPhysicsType(EPhysicsType::PlanetSurface);
	}
	void GPlayerPlanetNavigationComp::Disembark(GPhysicalComp* InstigatingPhysicalComp, math::MVector3 Impulse)
	{
		GPlanetNavigationComp::Disembark(InstigatingPhysicalComp, Impulse);
		PlayerControllerComp->SetPhysicsType(EPhysicsType::PlanetSurface);
	}
};
