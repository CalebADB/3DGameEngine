#ifndef _GOBJECT_H
#define _GOBJECT_H

namespace ge
{
	class GObject
	{
	private:
		const std::string Name;

		bool bIsEnabled = false;
		bool bIsDead = false;

	public:
		GObject()
			:
			Name(std::string("NullName"))
		{ debug::Output(debug::EOutputType::Always, "Error: GObject default contstructor called"); }
		GObject(const std::string& Name)
			:
			Name(Name)
		{}

	public:
		virtual void Begin();
		virtual void Destroy();

		std::string GetName() const;
		const char* GetCharName() const;
		bool GetIsEnabled() const;

		void SetIsEnabled(bool bInIsEnabled);
	};
};

#endif //_GOBJECT_H