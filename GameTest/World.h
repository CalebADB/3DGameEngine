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
	public:
		AWorld(const std::string& Name) 
			: 
			AActor(Name) 
		{};

		void BeginWorld();
		void UpdateWorld(float deltaTime);
		void RenderWorld();

	protected:
		//virtual void Begin();
		//virtual void Destroy();

	public:
		template <typename AActorSubclass>
		AActorSubclass* SpawnActor(const std::string& Name, AActor* Owner, math::MVector3 Position, math::MQuaternion Rotation);

		template <typename GCompSubclass>
		GCompSubclass* NewComp(const std::string& Name);
	};
};

#endif //_GWORLD_H