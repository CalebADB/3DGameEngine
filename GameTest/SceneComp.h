#ifndef _GSCENECOMP_H
#define _GSCENECOMP_H

namespace ge
{
	class GSceneComp : public GComp
	{
		friend class AActor;
	private:
		math::MTransformData LocalTransformData = math::MTransformData::Identity();
		math::MTransformData GlobalTransformData = math::MTransformData::Identity();

	public:
		GSceneComp(const std::string& Name) 
			: 
			GComp(Name)
		{}

	protected:
		virtual void UpdateGlobalTransform();
		virtual void Update(float deltaTime);
		virtual void Render();
		virtual void RenderSceneData();


	public:
		math::MTransformData GetLocalTransformData() const;
		math::MTransformData GetGlobalTransformData() const;

		void SetLocalTransformData(math::MTransformData TransformData);

	protected:
		void CalcGlobalTransformData();
	};
};

#endif //_GCOMP_H