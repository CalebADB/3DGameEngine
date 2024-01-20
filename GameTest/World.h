#ifndef _GWORLD_H
#define _GWORLD_H

#include "glsl.h"
#include "Player.h"

namespace ge
{
	//class AWorld;
	//extern AWorld* GAMEWORLD;

	class AWorld : public AActor
	{
	protected:
		int frame = 0;
		gm::glShaderManager SM;
		gm::glShader* shader;
		GLuint ProgramObject;
		clock_t time0, time1;
		GLfloat timer010;  // timer counting 0->1->0
		bool bUp;        // flag if counting up or down.

		APlayer* Player;
		std::list<GObject*> Objects;

		// World Level
		AEssentialShape* MajorBody = nullptr;
		AOrbitingBody* OrbitingBody = nullptr;
	public:
		AWorld(const std::string& Name) 
			: 
			AActor(Name) 
		{}

		void BeginWorld();
		void UpdateWorld(float deltaTime);
		void RenderWorld();

	protected:
		//virtual void Begin();
		//virtual void Destroy();

	public:
		template <typename AActorSubclass>
		AActorSubclass* SpawnActor(const std::string& Name, AActor* Owner, math::MVector3 LocalPosition, math::MQuaternion LocalRotation)
		{
			static_assert(std::is_base_of<AActor, AActorSubclass>::value, "AActorSubclass must be a derived class of AActor");
			AActorSubclass* ActorInstance = new AActorSubclass(Name);

			if (ActorInstance == nullptr)
			{
				debug::Output(debug::EOutputType::Always, "Error: SpawnActor created a nullptr");

				return nullptr;
			}

			Owner->AttachActor(ActorInstance);

			Objects.push_back(ActorInstance);

			ActorInstance->SetLocalTransformData(math::MTransformData(LocalPosition, LocalRotation, math::MVector3::OneVector()));
			ActorInstance->Begin();

			return ActorInstance;
		}

		template <typename GCompSubclass>
		GCompSubclass* NewComp(const std::string& Name)
		{
			static_assert(std::is_base_of<GComp, GCompSubclass>::value, "GCompSubclass must be a derived class of GComp");

			GCompSubclass* CompInstance = new GCompSubclass(Name);

			if (CompInstance == nullptr)
			{
			    debug::Output(debug::EOutputType::Always, "Error: NewComp created a nullptr");
			    
			    return nullptr;
			}

			Objects.push_back(CompInstance);

			CompInstance->Begin();

			return CompInstance;
		}

	};
};

#endif //_GWORLD_H