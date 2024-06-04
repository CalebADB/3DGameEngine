#include "stdafx.h"

namespace ge
{
	void AParticleEffect::Update(float deltaTime)
	{
		AActor::Update(deltaTime);
		while (QueuedParticleCount > 0)
		{
			math::MVector3 ParticleVelocity = EmissionDirection * ParticleSpeed;

			float RandRoll = -EmissionDirectionVariance + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (EmissionDirectionVariance + EmissionDirectionVariance)));
			float RandPitch = -EmissionDirectionVariance + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (EmissionDirectionVariance + EmissionDirectionVariance)));
			float RandYaw = -EmissionDirectionVariance + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (EmissionDirectionVariance + EmissionDirectionVariance)));

			ParticleVelocity = ParticleVelocity.RotatedBy(math::MQuaternion::FromEuler(math::MVector3(RandRoll, RandPitch, RandYaw)));
			AParticle* Particle = GAMEWORLD->SpawnActor<AParticle>(std::string("Particle"), GAMEWORLD, GetGlobalTransformData().Position, GetGlobalTransformData().Rotation);

			Particle->Initialize(ParticleLifetime, ParticleVelocity);

			Particles.push_back(Particle);

			QueuedParticleCount--;
		}

		//auto ParticleIter = Particles.begin();

		//while (ParticleIter != Particles.end())
		//{
		//	(*ParticleIter)->Get
		//	// Check for collision with each other component in the vector
		//	bool collisionExists = false;
		//	for (auto& otherComp : OngoingCollidingPhysicalComps)
		//	{
		//		if (*it != otherComp && CalcCollision(*it, otherComp))
		//		{
		//			collisionExists = true;
		//			break; // Stop checking further if a collision is found
		//		}
		//	}

		//	if (CheckOngoingCollisionBufferFrames(*it))
		//	{
		//		if (OngoingCollidingPhysicalCompBufferFrames[*it] > 1)
		//		{
		//			OngoingCollidingPhysicalCompBufferFrames[*it]--;
		//		}
		//		else
		//		{
		//			OngoingCollidingPhysicalCompBufferFrames.erase(*it);
		//		}
		//	}
		//	// If no collision exists, remove the component from the vector
		//	else if (!collisionExists)
		//	{

		//		// Using erase on a vector invalidates the current iterator
		//		// Erase returns the next valid iterator
		//		it = OngoingCollidingPhysicalComps.erase(it);
		//	}
		//	else
		//	{
		//		// Increment the iterator if the element was not erased
		//		++it;
		//	}
		//}
	}

	void AParticleEffect::DriveEffect(int QueuedParticleCount, math::MVector3 EmissionDirection)
	{
		this->QueuedParticleCount += QueuedParticleCount;
		this->EmissionDirection = EmissionDirection;
	}
}
