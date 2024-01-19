#ifndef _GESSENTIALSHAPE_H
#define _GESSENTIALSHAPE_h

namespace ge
{
	class AEssentialShape : public AActor
	{
	private:
		GEssentialMeshComp* MeshComp = nullptr;

	public:
		AEssentialShape(const std::string& Name)
			:
			AActor(Name)
		{};

	public:
		virtual void Begin();

	protected:
		virtual void Update(float deltaTime);
		virtual void Render();
	
	public:
		void SetEssentialShapeType(EEssentialShapeType Type, bool bIsSolid);

	};
};

#endif //_GESSENTIALSHAPE_H