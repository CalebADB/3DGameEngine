#ifndef _GCOMP_H
#define _GCOMP_H

namespace ge
{
	class GComp : public GObject
	{
	private:
		const bool bIsUpdateComp;
		const bool bIsRenderComp;
	protected:
		GComp* Root = nullptr;
		std::list<GComp*> AttachedComps;

	public:
		GComp();
		GComp(const std::string& Name, bool bIsUpdateComp, bool bIsRenderComp);

	protected:
		virtual void Update(float deltaTime);
		virtual void Render();

	public:
		bool AttachComp(GComp* RootComp, GComp* Comp);
	};
};

#endif //_GComp_H