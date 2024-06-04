#ifndef _APARTICLE_h
#define _APARTICLE_h

namespace ge
{
	class AParticle : public AActor
	{
	private:
		GSphereShapeComp* ShapeComp = nullptr;

		float bShouldDie = false;
		float TimeUntilDeath = 0;
		math::MVector3 Velocity = math::MVector3::ZeroVector();

	public:
		AParticle(const std::string& Name)
			:
			AActor(Name)
		{};

		virtual void Begin();
		void Initialize(float timeUntilDeath, math::MVector3 Velocity);

	protected:
		virtual void Update(float deltaTime);
		virtual void Render();

	public:
		bool GetShouldDie() const;
	};
};

#endif //_APARTICLE_h