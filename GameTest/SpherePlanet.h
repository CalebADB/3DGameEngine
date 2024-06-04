#ifndef _ASPHEREPLANET_h
#define _ASPHEREPLANET_h

namespace ge
{
	class ASpherePlanet : public APlanet
	{
	private:
		GSphereGravityWellComp* GravityWellComp = nullptr;
		GSphereShapeComp* ShapeComp = nullptr;

	public:
		ASpherePlanet(const std::string& Name)
			:
			APlanet(Name)
		{};

		virtual void Begin();
		void Initialize(GLfloat Mass, math::MVector3 Acceleration, math::MVector3 Velocity, GLfloat SurfaceRadius, GLfloat GravityStrength, GLfloat GravityReachRadius, math::MVector3 Color);
	protected:
		virtual void Update(float deltaTime);
		virtual void Render();

	public:
		GLfloat GetRadius() const { return ShapeComp->GetRadius(); }
	};
};

#endif //_APLANET_h