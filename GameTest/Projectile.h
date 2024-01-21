#ifndef _GPROJECTILE_h
#define _GPROJECTILE_h

namespace ge
{
	class AProjectile : public AActor
	{
	public:
		GPropPhysicalComp* PhysicalComp = nullptr;
		//GEssentialMeshComp* DebugShape = nullptr;

	public:
		AProjectile(const std::string& Name)
			:
			AActor(Name)
		{};

		virtual void Begin();

	protected:
		virtual void Update(float deltaTime);
		virtual void Render();
	};
};

#endif //_GPROJECTILE_h