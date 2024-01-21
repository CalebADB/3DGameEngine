#ifndef _GPRESSUREWAVE_h
#define _GPRESSUREWAVE_h

namespace ge
{
	class APressureWave : public AActor
	{
	public:
		GPressureWavePhysicalComp* PhysicalComp = nullptr;
		//GEssentialMeshComp* DebugShape = nullptr;

	public:
		APressureWave(const std::string& Name)
			:
			AActor(Name)
		{};

		virtual void Begin();

	protected:
		virtual void Update(float deltaTime);
		virtual void Render();
	};
};

#endif //_GPRESSUREWAVE_h