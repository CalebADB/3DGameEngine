#ifndef _GPLANET_h
#define _GPLANET_h

namespace ge
{
	class APlanet : public AActor
	{
	protected:
		GPlanetPhysicalComp* PhysicalComp = nullptr;
		std::list<GGravityWellComp*> GravityWellComps;

	public:
		APlanet(const std::string& Name)
			:
			AActor(Name)
		{};

		virtual void Begin();
		void Initialize(GLfloat Mass, math::MVector3 Velocity, math::MVector3 Acceleration);
		
		GPlanetPhysicalComp* GetPhysicalComp() { return PhysicalComp; }

	protected:
		virtual void Update(float deltaTime);
		virtual void Render();
	};
};

#endif //_GPLANET_h