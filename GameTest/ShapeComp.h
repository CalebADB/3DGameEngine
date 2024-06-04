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
		bool bIsRendered = false;
	protected:
		GEssentialMeshComp* DebugShape = nullptr;

	public:
		GShapeComp(const std::string& Name)
			:
			GSceneComp(Name)
		{}
		void Initialize(bool bIsRendered, math::MVector3 Color);

	protected:
		virtual void RenderSceneData();

		virtual void Destroy();

	public:
		virtual bool IsRendered() const { return bIsRendered; }
		math::MVector3 GetShapeColor();
		virtual GLfloat GetMaxSize() const = 0;
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
		void Initialize(GLfloat Radius, bool bIsRendered, math::MVector3 Color);
		
	public:
		GLfloat GetRadius() const { return Radius; }
		GLfloat GetMaxSize() const { return Radius; }
		virtual GLfloat GetSignedDistanceFrom(math::MVector3 GlobalPosition);
	};
};

#endif //_GSHAPECOMP_H