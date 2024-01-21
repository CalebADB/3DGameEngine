#ifndef _GPROP_h
#define _GPROP_h

namespace ge
{
	class AProp : public AActor
	{
	protected:
		GPropPhysicalComp* PhysicalComp = nullptr;

	public:
		GPlanetNavigationComp* PlanetNavigationComp = nullptr;

	public:
		AProp(const std::string& Name)
			:
			AActor(Name)
		{};

		virtual void Begin();
		void Initialize(GLfloat Mass, math::MVector3 Acceleration, math::MVector3 Velocity, GLfloat GroundDisplacement);

	protected:
		virtual void Update(float deltaTime);
		virtual void Render();
	};
};

#endif //_GPROP_h