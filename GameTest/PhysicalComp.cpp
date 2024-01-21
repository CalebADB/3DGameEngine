#include "stdafx.h"

//using namespace ge::math

namespace ge
{
	void GPhysicalComp::Begin()
	{
		GComp::Begin();
	}

	void GPhysicalComp::Initialize(GLfloat Mass, math::MVector3 Acceleration, math::MVector3 Velocity)
	{
		this->Mass = Mass;
		this->Acceleration = Acceleration;
		this->Velocity = Velocity;

		GAMEWORLD->PhysicsManagerComp->AddPhysicalComp(this);
	}
	
	bool GPhysicalComp::CalcCollision(GPhysicalComp* PhysicalComp1, GPhysicalComp* PhysicalComp2)
	{
		if (!PhysicalComp1 || !PhysicalComp2)
			return false; // Invalid pointers

		// Iterate through all shapes in the first physical component
		for (GShapeComp* Shape1 : PhysicalComp1->Shapes)
		{
			// Get global position of the current shape in PhysicalComp1
			math::MVector3 Pos1 = Shape1->GetGlobalTransformData().Position;

			// Iterate through all shapes in the second physical component
			for (GShapeComp* Shape2 : PhysicalComp2->Shapes)
			{
				// Get global position of the current shape in PhysicalComp2
				math::MVector3 Pos2 = Shape2->GetGlobalTransformData().Position;

				// Check the distance between Shape1 and Shape2
				GLfloat Distance = (Pos2 - Pos1).Magnitude();

				// Use the signed distance function to check for intersection
				GLfloat DistanceToShape1 = Shape2->GetSignedDistanceFrom(Pos1);
				GLfloat DistanceToShape2 = Shape1->GetSignedDistanceFrom(Pos2);

				// If the distance between centers is less than the sum of the distances to their surfaces, there is a collision
				if (Distance > (DistanceToShape1 + DistanceToShape2))
					return true; // Collision detected
			}
		}

		return false; // No collision detected
	}

	math::MVector3 GPhysicalComp::CalcImpulse(GPhysicalComp* PhysicalComp1, GPhysicalComp* PhysicalComp2)
	{
		math::MVector3 ResultingImpulse = math::MVector3::ZeroVector();

		// Calculate relative velocity
		math::MVector3 RelativeVelocity = PhysicalComp1->Velocity - PhysicalComp2->Velocity;

		// Calculate the reduced mass (for two-body problem in physics)
		GLfloat ReducedMass = (PhysicalComp1->Mass * PhysicalComp2->Mass) / (PhysicalComp1->Mass + PhysicalComp2->Mass);

		GLfloat Elasticity = 1.0; // Coefficient of restitution 

		return RelativeVelocity * ReducedMass * Elasticity * 2;
	}

	void GPhysicalComp::Update(float deltaTime)
	{
		GComp::Update(deltaTime);

		Velocity = Velocity + (Acceleration * deltaTime);

		for (math::MVector3 Impulse : Impulses)
		{
			Velocity = Velocity + (Impulse / Mass);
		}
		Impulses.clear();
	}

	void GPhysicalComp::SetPhysicsType(const EPhysicsType PhysicsType)
	{
		this->PhysicsType = PhysicsType;
		switch(PhysicsType)
		{
		case EPhysicsType::Space:
		{
			break;
		}
		case EPhysicsType::PlanetSurface:
		{
			Impulses.clear();
			Velocity = math::MVector3::ZeroVector();
			Acceleration = math::MVector3::ZeroVector();
			break;
		}
		}
	}

	void GPhysicalComp::AddShape(GShapeComp* Shape)
	{	
		Shapes.push_back(Shape);

		MaxCollisionBound = Shape->GetMaxSize() * 2 > MaxCollisionBound ? Shape->GetMaxSize() * 2 : MaxCollisionBound;
	}

	void GPhysicalComp::SetGravity(math::MVector3 Gravity)
	{
		Acceleration = Gravity;
	}

	math::MVector3 GPhysicalComp::GetLinearDisplacement(float deltaTime)
	{
		return Velocity * deltaTime;
	}

	void GPhysicalComp::AddLinearImpulse(GPhysicalComp* InstigatingPhysicalComp, math::MVector3 Impulse)
	{
		if (CheckOngoingCollision(InstigatingPhysicalComp)) 
		{
			return;
		}

		OngoingCollidingPhysicalComps.push_back(InstigatingPhysicalComp);
		Impulses.push_back(Impulse);
	}

	bool GPhysicalComp::CheckOngoingCollision(GPhysicalComp* InstigatingPhysicalComp)
	{
		return std::find(OngoingCollidingPhysicalComps.begin(), OngoingCollidingPhysicalComps.end(), InstigatingPhysicalComp) != OngoingCollidingPhysicalComps.end();
	}

	void GPhysicalComp::HandleOngoingCollisions()
	{
		// Iterator for the vector
		auto it = OngoingCollidingPhysicalComps.begin();

		// Iterate through the vector
		while (it != OngoingCollidingPhysicalComps.end())
		{
			// Check for collision with each other component in the vector
			bool collisionExists = false;
			for (auto& otherComp : OngoingCollidingPhysicalComps)
			{
				if (*it != otherComp && CalcCollision(*it, otherComp))
				{
					collisionExists = true;
					break; // Stop checking further if a collision is found
				}
			}

			// If no collision exists, remove the component from the vector
			if (!collisionExists)
			{
				// Using erase on a vector invalidates the current iterator
				// Erase returns the next valid iterator
				it = OngoingCollidingPhysicalComps.erase(it);
			}
			else
			{
				// Increment the iterator if the element was not erased
				++it;
			}
		}
	}

	void GPlanetPhysicalComp::Begin()
	{
		GPhysicalComp::Begin();

		PhysicalType = EPhysicalType::Planet;
	}
	void GPlanetPhysicalComp::Update(float deltaTime)
	{
		GPhysicalComp::Update(deltaTime);
	}

	void GPlayerPhysicalComp::Begin()
	{
		GPhysicalComp::Begin();

		PhysicalType = EPhysicalType::Player;
	}
	void GPlayerPhysicalComp::Update(float deltaTime)
	{
		GPhysicalComp::Update(deltaTime);
	}

	void GPressureWavePhysicalComp::Begin()
	{
		GPhysicalComp::Begin();

		PhysicalType = EPhysicalType::PressureWave;
	}
	void GPressureWavePhysicalComp::Update(float deltaTime)
	{
		GPhysicalComp::Update(deltaTime);
	}

	void GProjectilePhysicalComp::Begin()
	{
		GPhysicalComp::Begin();

		PhysicalType = EPhysicalType::Projectile;
	}
	void GProjectilePhysicalComp::Update(float deltaTime)
	{
		GPhysicalComp::Update(deltaTime);
	}

	void GPropPhysicalComp::Begin()
	{
		GPhysicalComp::Begin();

		PhysicalType = EPhysicalType::Prop;
	}
	void GPropPhysicalComp::Update(float deltaTime)
	{
		GPhysicalComp::Update(deltaTime);
	}
};
