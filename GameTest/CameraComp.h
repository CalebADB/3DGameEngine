#ifndef _GCAMERACOMP_H
#define _GCAMERACOMP_H

namespace ge
{
	class GCameraComp : public GSceneComp
	{
	public:
		GCameraComp(const std::string& Name) 
			: 
			GSceneComp(Name)
		{};
	
	protected:
		virtual void Update(float deltaTime);
		virtual void Render();
	};
};

#endif //_GCAMERACOMP_H