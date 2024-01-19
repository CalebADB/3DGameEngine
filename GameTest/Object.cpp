#include "stdafx.h"

namespace ge
{
	void GObject::Begin()
	{
		bIsDead = true;
		bIsEnabled = true;

		debug::Output(debug::EOutputType::Initialize, "GObject_%s created", GetCharName());
	}

	void GObject::Destroy()
	{
		bIsEnabled = false;
		bIsDead = false;
	}

	std::string GObject::GetName() const
	{
		return Name;
	}
	const char* GObject::GetCharName() const
	{
		return Name.c_str();
	}
	bool GObject::GetIsEnabled() const
	{
		return bIsEnabled;
	}

	void GObject::SetIsEnabled(bool bIsEnabled)
	{
		if (bIsDead)
		{
			return;
		}

		this->bIsEnabled = bIsEnabled;
	}
};

