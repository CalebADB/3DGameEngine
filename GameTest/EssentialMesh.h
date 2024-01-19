#ifndef _GESSENTIALMESHCOMP_H
#define _GESSENTIALMESHCOMP_H

namespace ge
{
	enum EEssentialShapeType
	{
		Sphere,
		Cube,
		Cone,
		Torus,
		Dodecahedron,
		Octahedron,
		Tetrahedron,
		Icosahedron,
		Teapot,
		Default
	};

	class GEssentialMeshComp : public GMeshComp
	{
	private:
		EEssentialShapeType CurType = EEssentialShapeType::Default;
		bool bIsWired = false;

	public:
		GEssentialMeshComp(const std::string& Name)
			:
			GMeshComp(Name)
		{};

	protected:
		virtual void Update(float deltaTime);
		virtual void ApplySceneData();

	public:
		void SetEssentialShapeType(EEssentialShapeType Type, bool bIsWired);
	};
};

#endif //_GESSENTIALMESHCOMP_H