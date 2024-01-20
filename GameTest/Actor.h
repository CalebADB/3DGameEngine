#ifndef _GACTOR_H
#define _GACTOR_H

namespace ge
{
	class AActor : public GSceneComp
	{
	private:
		AActor* Owner = nullptr;
		std::list<AActor*> AttachedActors;

	public:
		AActor(const std::string& Name) 
			:
			GSceneComp(Name)
		{}

		virtual void Begin();
	protected:
		virtual void UpdateGlobalTransform();
		virtual void Update(float deltaTime);
		virtual void Render();

	public:
		bool AttachActor(AActor* Actor);
		bool DettachActor(AActor* Actor);
		AActor* GetOwner() const;

	protected:
		void CalcGlobalTransformData();
	};
};

#endif //_GACTOR_H