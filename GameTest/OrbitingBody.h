#ifndef _GORBITINGBODY_h
#define _GORBITINGBODY_h

namespace ge
{
	class AOrbitingBody : public AActor
	{
	private:
		GEssentialMeshComp* MeshComp = nullptr;
		GOrbitComp* OrbitComp = nullptr;
		

	public:
		AOrbitingBody(const std::string& Name)
			:
			AActor(Name)
		{};

	public:
		virtual void Begin();
		void Initialize(GLfloat Radius, GLfloat AngularSpeed, GLfloat AngularDistance = 0.0f, math::MVector3 Axis = math::MVector3::UpVector());
	protected:
		virtual void Update(float deltaTime);
		virtual void Render();

	public:
		void SetEssentialShapeType(EEssentialShapeType Type, bool bIsSolid);
	};
};

#endif //_GORBITINGBODY_h