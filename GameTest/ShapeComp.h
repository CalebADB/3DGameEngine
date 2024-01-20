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
	public:
		GShapeComp(const std::string& Name)
			:
			GSceneComp(Name)
		{}

	protected:
		virtual void Update(float deltaTime);
		virtual void Render();

	public:
		virtual GLfloat GetSignedDistanceFrom(math::MVector3 GlobalPosition) = 0;
		virtual math::MVector3 GetShapeColor();
	};

	class GSphereShapeComp : public GShapeComp
	{
	private:
		// Shape Params
		GLfloat Radius;
	public:
		GSphereShapeComp(const std::string& Name)
			:
			GShapeComp(Name)
		{}

		void SetDimensions(GLfloat Radius);

		virtual GLfloat GetSignedDistanceFrom(math::MVector3 GlobalPosition);
	};

	//class GShapeComp : public GShapeComp
	//{
	//private:
	//	// Shape Variables

	//public:
	//	GShapeComp(const std::string& Name)
	//		:
	//		GShapeComp(Name)
	//	{}

	//public:
	//	virtual GLfloat GetSignedDistanceFrom(math::MVector3 Position);
	//};
};

#endif //_GSHAPECOMP_H