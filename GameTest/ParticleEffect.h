#ifndef _APARTICLEEFFECT_H
#define _APARTICLEEFFECT_H

namespace ge
{
	class AParticleEffect : public AActor
	{
	private:
		std::vector<AParticle*> Particles;
		float ParticleLifetime = 0.5;
		float ParticleSpeed = 10;
		float ParticleSpawnRadius = 1;
		float EmissionDirectionVariance = 0.1;

		int QueuedParticleCount = 0;
		math::MVector3 EmissionDirection = math::MVector3::ZeroVector();

	public:
		AParticleEffect(const std::string& Name)
			:
			AActor(Name)
		{};

	protected:
		virtual void Update(float deltaTime);

	public:
		void DriveEffect(int QueuedParticleCount, math::MVector3 EmissionDirection);
	};
};

#endif //_APARTICLEEFFECT_H