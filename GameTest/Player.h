#ifndef _GPLAYER_H
#define _GPLAYER_H

namespace ge
{
	class APlayer : public AActor
	{
	public:
		APlayer(const std::string& Name) 
			: 
			AActor(Name) 
		{};
	
	public:
		//virtual void Begin();
	protected:
		void Update(float deltaTime);
		void Render();
	};
};

#endif //_GPLAYER_H