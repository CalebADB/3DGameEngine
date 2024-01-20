#ifndef _GMANAGERCOMP_H
#define _GMANAGERCOMP_H

namespace ge
{
	class GManagerComp : public GComp
	{
	private:
		// singleton stuff
	public:
		GManagerComp(const std::string& Name) 
			: 
			GComp(Name) 
		{}

	protected:
		virtual void Update(float deltaTime);
		virtual void Render();
	};
};

#endif //_GCOMP_H