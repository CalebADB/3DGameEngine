#ifndef _GSCENECOMP_H
#define _GSCENECOMP_H

namespace ge
{
	class GSceneComp : public GComp
	{
	public:
		math::MTransformData TransformData = math::MTransformData::Identity();

	public:
		GSceneComp(const std::string& Name) 
			: 
			GComp(Name)
		{}

	protected:
		virtual void Update(float deltaTime);
		virtual void Render();
		virtual void RenderSceneData();
	};
};

#endif //_GCOMP_H