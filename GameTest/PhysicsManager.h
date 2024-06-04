#ifndef _GPHYSICSMANAGERCOMP_H
#define _GPHYSICSMANAGERCOMP_H

namespace ge
{
	class GPhysicsManagerComp : public GManagerComp
	{
	private:
		std::list<GPlayerControllerComp*> PlayerControllerComps;
		std::list<GPhysicalComp*> PhysicalComps;
		std::list<GPlanetNavigationComp*> PlanetNavigationComps;
		std::list<GGravityWellComp*> GravityWellComps;
		GOctree* Octree = nullptr;

	public:
		GPhysicsManagerComp(const std::string& Name) 
			: 
			GManagerComp(Name) 
		{}

		virtual void Begin();
	public:
		void AddPlayerControllerComp(GPlayerControllerComp* PlayerControllerComp);
		void AddPhysicalComp(GPhysicalComp* PhysicalComp);
		void AddPlanetNavigationComp(GPlanetNavigationComp* PlanetNavigationComp);
		void AddGravityWellComp(GGravityWellComp* GravityWellComp);
		
		void RemovePlayerControllerComp(GPlayerControllerComp* PlayerControllerComp);
		void RemovePhysicalComp(GPhysicalComp* PhysicalComp);
		void RemovePlanetNavigationComp(GPlanetNavigationComp* PlanetNavigationComp);
		void RemoveGravityWellComp(GGravityWellComp* GravityWellComp);

		void HandleForces(float deltaTime);
		void HandleDisplacement(float deltaTime);

		void CheckCollisions();

	private:
		math::MVector3 GetGravityAtPosition(math::MVector3 Position);

		void HandleCollision(GPhysicalComp* PhysicalComp1, GPhysicalComp* PhysicalComp2);
		void HandlePlanetCollisionImpact(GPlanetPhysicalComp* TargetPhysicalComp);
		void HandlePlayerCollisionImpact(GPlayerPhysicalComp* TargetPhysicalComp, GPhysicalComp* InstigatingPhysicalComp, math::MVector3 Impulse);
		void HandlePressureWaveCollisionImpact(GPressureWavePhysicalComp* TargetPhysicalComp);
		void HandleProjectileCollisionImpact(GProjectilePhysicalComp* TargetPhysicalComp, math::MVector3 Impulse);
		void HandlePropCollisionImpact(GPropPhysicalComp* TargetPhysicalComp, GPhysicalComp* InstigatingPhysicalComp, math::MVector3 Impulse);
	};
};

#endif //_GPHYSICSMANAGERCOMP_H