#ifndef _GTIMECONTAINERPROP_h
#define _GTIMECONTAINERPROP_h

namespace ge
{
	class ATimeContainerProp : public AProp
	{
	private:
		GSphereShapeComp* ShapeComp = nullptr;


	public:
		ATimeContainerProp(const std::string& Name)
			:
			AProp(Name)
		{};

		virtual void Begin();
		void Initialize(GLfloat Mass, math::MVector3 Velocity, math::MVector3 Acceleration, GLfloat GroundDisplacement, GLfloat BoxEdgeLength, math::MVector3 Color);

	protected:
		virtual void Update(float deltaTime);
		virtual void Render();
	};
};

#endif //_GTIMECONTAINERPROP_h