#ifndef _GCOMP_H
#define _GCOMP_H

namespace ge
{
	class GComp : public GObject
	{
	protected:
		GComp* Root = nullptr;
		std::list<GComp*> AttachedComps;

	public:
		GComp::GComp(const std::string& Name)
			:
			GObject(Name)
		{}

	protected:
		virtual void UpdateGlobalTransform();
		virtual void Update(float deltaTime);
		virtual void Render();

	public:
		bool AttachComp(GComp* RootComp, GComp* Comp);

	public:
		math::MTransformData GetLocalTransformData();
		math::MTransformData GetGlobalTransformData();

	};
};

#endif //_GComp_H