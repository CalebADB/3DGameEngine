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
	public:
		// World Managers
		GPhysicsManagerComp* PhysicsManagerComp = nullptr;
		bool bIsOpenGLTogglePressed = false;
		bool bShouldRenderWithUbisoftAPI = true;
		GRenderManagerComp* RenderManagerComp = nullptr;
		// Debug Timer
		GLfloat timer010;  // timer counting 0->1->0

	protected:
		int frame = 0;
		gm::glShaderManager SM;
		gm::glShader* shader;
		GLuint ProgramObject;
		clock_t time0, time1;
		bool bUp;        // flag if counting up or down.

		APlayer* Player = nullptr;
		GCameraComp* GameCameraComp = nullptr;
		std::list<GObject*> Objects;

		// World Level
		ASpherePlanet* SpherePlanet1 = nullptr;
		ATimeContainerProp* Prop1 = nullptr;
		ATimeContainerProp* Prop2 = nullptr;
		ATimeContainerProp* Prop3 = nullptr;
		AOrbitingBody* OrbitingBody = nullptr;
	public:
		AWorld(const std::string& Name) 
			: 
			AActor(Name) 
		{}

		void BeginWorld();
		void UndoInitializeOpenGLRender();
		void InitializeOpenGLRender();

		void UpdateWorld(float deltaTime);
		void RenderWorld();

		void RenderWorldUbisoftAPI();
		void RenderWorldOpenGL();

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

		template <typename GObjectSubclass>
		GObjectSubclass* NewObject(const std::string& Name)
		{
			static_assert(std::is_base_of<GObject, GObjectSubclass>::value, "GObjectSubclass must be a derived class of GObject");

			GObjectSubclass* ObjectInstance = new GObjectSubclass(Name);

			if (ObjectInstance == nullptr)
			{
				debug::Output(debug::EOutputType::Always, "Error: NewObject created a nullptr");

				return nullptr;
			}

			Objects.push_back(ObjectInstance);

			ObjectInstance->Begin();

			return ObjectInstance;
		}
	};
};

#endif //_GWORLD_H