#include "stdafx.h"

namespace ge
{

	void AParticle::Begin()
	{
		AActor::Begin();

		ShapeComp = GAMEWORLD->NewComp<GSphereShapeComp>(std::string("PlayerShapeComp"));
		AttachComp(this, ShapeComp);
	}

	void AParticle::Initialize(float TimeUntilDeath, math::MVector3 Velocity)
	{
		this->TimeUntilDeath = TimeUntilDeath;
		this->Velocity = Velocity;

		ShapeComp->Initialize(0.1, true, math::MVector3(1, 1, 0));
	}

	void AParticle::Update(float deltaTime)
	{
		AActor::Update(deltaTime);


		math::MTransformData NewTransform = GetLocalTransformData();

		NewTransform.Translate(Velocity * deltaTime);

		SetLocalTransformData(NewTransform);


		TimeUntilDeath -= deltaTime;

		if (TimeUntilDeath < 0)
		{
			Destroy();
		}
	}

	void AParticle::Render()
	{
		AActor::Render();

		debug::Output(debug::EOutputType::Render, "Rendering APlayer_%s ", GetCharName());
	}

	bool AParticle::GetShouldDie() const
	{
		return bShouldDie;
	}
}