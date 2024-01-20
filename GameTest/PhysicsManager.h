#ifndef _GPHYSICSMANAGERCOMP_H
#define _GPHYSICSMANAGERCOMP_H

namespace ge
{
	class GPhysicsManagerComp : public GManagerComp
	{
	private:
		std::list<GPhysicalComp*> PhysicalComps;
		std::list<GGravityWellComp*> GravityWellComps;
	public:
		GPhysicsManagerComp(const std::string& Name) 
			: 
			GManagerComp(Name) 
		{}

	protected:
		virtual void Update(float deltaTime);
		virtual void Render();

	public:
		void AddPhysicalComp(GPhysicalComp* PhysicalComp);
		void AddGravityWellComp(GGravityWellComp* GravityWellComp);

	private:
		math::MVector3 GetGravityForceAtPosition(math::MVector3 Position);

		void CheckCollision();

		bool QueuePlanetCollisionImpulse();
		bool QueueProjectileCollisionImpulse();
		bool QueuePropCollisionImpulse();
		bool QueuePlayerCollisionImpulse();
	};
};

#endif //_GPHYSICSMANAGERCOMP_H