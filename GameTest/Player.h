#ifndef _GPLAYER_H
#define _GPLAYER_H

namespace ge
{
	class APlayer : public AActor
	{
	protected:
		GPlayerPhysicalComp* PhysicalComp = nullptr;
		GSphereShapeComp* ShapeComp = nullptr;

	public:
		GCameraComp* FirstPersonCameraComp = nullptr;
		GPlayerControllerComp* ControllerComp = nullptr;

	public:
		GPlayerPlanetNavigationComp* PlanetNavigationComp = nullptr;

	public:
		APlayer(const std::string& Name) 
			: 
			AActor(Name)
		{};

		virtual void Begin();
		void Initialize(GLfloat Mass, math::MVector3 Acceleration, math::MVector3 Velocity, GLfloat GroundDisplacement, GLfloat PlayerRadius, math::MVector3 Color);

	protected:
		virtual void Update(float deltaTime);
		virtual void Render();
	};
};

#endif //_GPLAYER_H