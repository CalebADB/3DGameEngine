#ifndef _GCOMP_H
#define _GCOMP_H

#include <string>
#include <list>
#include <concepts>

namespace ge
{
	class GComp : public GObject
	{
	protected:
		GComp* Root = nullptr;
		std::list<GComp*> AttachedComps;

	public:
		GComp(const std::string& Name)
			:
			GObject(Name)
		{}

	protected:
		virtual void UpdateGlobalTransform();
		virtual void Update(float deltaTime);
		virtual void Render();

	public:
		virtual bool AttachComp(GComp* RootComp, GComp* Comp);
		GComp* GetActorRoot();
		
		template<typename T>
		T* GetChildComponent();

	public:
		virtual math::MTransformData GetLocalTransformData() const;
		virtual math::MTransformData GetGlobalTransformData() const;

	};
};

#endif //_GComp_H