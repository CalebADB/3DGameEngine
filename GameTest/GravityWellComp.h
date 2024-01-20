#ifndef _GGRAVITYWELLCOMP_H
#define _GGRAVITYWELLCOMP_H

namespace ge
{
	class GGravityWellComp : public GSceneComp
	{
	private:
		GShapeComp* Shape;
		GLfloat Strength;

	public:
		GGravityWellComp(const std::string& Name)
			:
			GSceneComp(Name)
		{}

	protected:
		virtual void Update(float deltaTime);

	public:
		virtual math::MVector3 GetGravityForceAtPosition(math::MVector3 GlobalPosition) = 0;
	};

	class GSphereGravityWellComp : public GGravityWellComp
	{
	public:
		virtual void Begin();
		void Initialize();

		virtual math::MVector3 GetGravityForceAtPosition(math::MVector3 GlobalPosition) = 0;
	};
};

#endif //_GGRAVITYWELLCOMP_H