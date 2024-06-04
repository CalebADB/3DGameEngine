#ifndef _GGRAVITYWELLCOMP_H
#define _GGRAVITYWELLCOMP_H

namespace ge
{
	enum struct EGravityWellType
	{
		Null,
		Sphere
	};

	class GGravityWellComp : public GSceneComp
	{
	protected:
		EGravityWellType Type = EGravityWellType::Null;

		GLfloat Strength = 0.0;

	public:
		GGravityWellComp(const std::string& Name)
			:
			GSceneComp(Name)
		{}

		virtual void Begin();
		void Initialize(GLfloat Strength);

	protected:
		virtual void Update(float deltaTime);

		virtual void Destroy();

	public:
		EGravityWellType GetType() { return Type; }

		virtual math::MVector3 GetGravityAtPosition(math::MVector3 GlobalPosition) = 0;
	};

	class GSphereGravityWellComp : public GGravityWellComp
	{
	private:
		GSphereShapeComp* SphereShapeComp = nullptr;

	public:
		GSphereGravityWellComp(const std::string& Name)
			:
			GGravityWellComp(Name)
		{}

		virtual void Begin();
		void Initialize(GLfloat Strength, GLfloat GravityReachRadius, math::MVector3 Color);

		virtual void RenderSceneData();

		virtual math::MVector3 GetGravityAtPosition(math::MVector3 GlobalPosition);
	};
};

#endif //_GGRAVITYWELLCOMP_H