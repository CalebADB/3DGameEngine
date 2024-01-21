#ifndef _GESSENTIALMESHCOMP_H
#define _GESSENTIALMESHCOMP_H

namespace ge
{
	enum struct EEssentialShapeType
	{
		Sphere,
		SphereLP,
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
		EEssentialShapeType Type = EEssentialShapeType::Default;
		bool bIsSolid = false;

	public:
		GEssentialMeshComp(const std::string& Name)
			:
			GMeshComp(Name)
		{};

	protected:
		virtual void RenderSceneData();

	public:
		void SetEssentialShapeType(EEssentialShapeType Type, bool bIsWired);
	};
};

#endif //_GESSENTIALMESHCOMP_H