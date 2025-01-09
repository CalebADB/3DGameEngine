#ifndef _GESSENTIALMESHCOMP_H
#define _GESSENTIALMESHCOMP_H

namespace ge
{
	enum struct EEssentialShapeType
	{
		Sphere,
		SphereLP,
		SpherePlanet,
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

	class GVertexMesh : public GObject
	{
	public:
		GVertexMesh(const std::string & Name)
			:
			GObject(Name)
		{
		}
	};

	class GSphereVertex : public GObject
	{
	public:
		GSphereVertex(const std::string& Name)
			:
			GObject(Name)
		{
		}

		math::MQuaternion RadialCoord = math::MQuaternion::Identity();

		GSphereVertex* NorthVertex = nullptr;
		GSphereVertex* WestVertex = nullptr;
		GSphereVertex* EastVertex = nullptr;
		GSphereVertex* SouthVertex = nullptr;
	};

	class GSphereVertexMesh : public GVertexMesh
	{
	public:
		GSphereVertexMesh(const std::string& Name)
			:
			GVertexMesh(Name)
		{
		}

		math::MVector3 NorthPoleDisplacement = math::MVector3::ZeroVector();
		GSphereVertex* NorthPoleVertex = nullptr;
		GSphereVertex* SouthPoleVertex = nullptr;
		std::vector<GSphereVertex*> NorthPoleConnections = {};
		std::vector<GSphereVertex*> SouthPoleConnections = {};
	};

	class GEssentialMeshComp : public GMeshComp
	{
	private:
		EEssentialShapeType Type = EEssentialShapeType::Default;
		bool bIsSolid = false;
		GSphereVertexMesh* SphereVertexMesh = nullptr;

	public:
		GEssentialMeshComp(const std::string& Name)
			:
			GMeshComp(Name)
		{};

	protected:
		virtual void RenderSceneData();

	public:
		void SetEssentialShapeType(EEssentialShapeType Type, bool bIsWired);
		GSphereVertexMesh* GetSphereVertexMesh();
	private:
		void BuildMesh();
		void CheckPlanet();
		void RenderPlanet();
	};
};

#endif //_GESSENTIALMESHCOMP_H