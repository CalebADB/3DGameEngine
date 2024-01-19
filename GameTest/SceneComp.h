#ifndef _GSCENECOMP_H
#define _GSCENECOMP_H

namespace ge
{
	class GSceneComp : public GComp
	{
	private:
		math::MTransformData TransformData = math::MTransformData::Identity();

	public:
		GSceneComp(const std::string& Name) 
			: 
			GComp(Name, true, true)
		{};

	protected:
		virtual void Update(float deltaTime);
		virtual void Render();
		virtual void ApplySceneData();
	};
};

#endif //_GCOMP_H