#ifndef _AACTOR_H
#define _AACTOR_H

namespace ge
{
	class AActor : public GSceneComp
	{
		friend class AWorld;
	private:
		AActor* Owner = nullptr;
		std::list<AActor*> AttachedActors;

	public:
		AActor(const std::string& Name) 
			:
			GSceneComp(Name)
		{}

	protected:
		virtual void UpdateGlobalTransform();
		virtual void Update(float deltaTime);
		virtual void Render();

		virtual void Destroy();

	public:
		bool AttachActor(AActor* Actor);
		bool DettachActor(AActor* Actor);
		AActor* GetOwner() const;

	protected:
		void CalcGlobalTransformData();
	};
};

#endif //_AACTOR_H