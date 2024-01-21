#ifndef _GSHAPECOMP_H
#define _GSHAPECOMP_H

namespace ge
{
	enum EShapeType
	{
		Sphere,
		Cube,
		Cylinder
	};

	class GShapeComp : public GSceneComp
	{
	private:
		math::MVector3 Color = math::MVector3(1,0,1);

	protected:
		GEssentialMeshComp* DebugShape = nullptr;

	public:
		GShapeComp(const std::string& Name)
			:
			GSceneComp(Name)
		{}
		void Initialize(math::MVector3 Color);

	public:
		virtual GLfloat GetMaxSize() const = 0;
		math::MVector3 GetShapeColor();
		virtual GLfloat GetSignedDistanceFrom(math::MVector3 GlobalPosition) = 0;
	};

	class GSphereShapeComp : public GShapeComp
	{
	private:
		// Shape Params
		GLfloat Radius = 0;
	public:
		GSphereShapeComp(const std::string& Name)
			:
			GShapeComp(Name)
		{}
		virtual void Begin();
		void Initialize(GLfloat Radius, math::MVector3 Color);
		GLfloat GetRadius() const { return Radius; }

	protected:
		virtual void RenderSceneData();
		
	public:
		GLfloat GetMaxSize() const { return Radius; }
		virtual GLfloat GetSignedDistanceFrom(math::MVector3 GlobalPosition);
	};
};

#endif //_GSHAPECOMP_H