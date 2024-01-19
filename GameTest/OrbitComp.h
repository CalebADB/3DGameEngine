#ifndef _GORBITCOMP_H
#define _GORBITCOMP_H

namespace ge
{
	class GOrbitComp : public GComp
	{
	private:
		GSceneComp* MajorBody;
		GLfloat Radius;
		GLfloat AngularSpeed;
		GLfloat AngularDistance;
		math::MVector3 Axis = math::MVector3::UpVector();

	public:
		GOrbitComp(const std::string& Name) : GComp(Name) {};
		void Initialize(GSceneComp* MajorBody, GLfloat Radius, GLfloat AngularSpeed, GLfloat AngularDistance = 0.0f, math::MVector3 Axis = math::MVector3::UpVector());

	protected:
		virtual void Update(float deltaTime);

	public:
		math::MVector3 GetOrbitRelPosition();
		math::MQuaternion GetOrbitRelRotation();
		
	};
};

#endif //_GCOMP_H