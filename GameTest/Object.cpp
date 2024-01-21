#include "stdafx.h"

namespace ge
{
	void GObject::Begin()
	{
		//if(!bIsBegun) debug::Output(debug::EOutputType::Always, "Error: GObject_%s attempted GObject::Begin() while begun is true", GetCharName());
		bIsBegun = true;
		bIsEnabled = true;

		debug::Output(debug::EOutputType::Initialize, "GObject_%s created", GetCharName());
	}

	void GObject::Destroy()
	{
		bIsEnabled = false;
		bIsAlive = false;
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
		if (bIsAlive)
		{
			return;
		}

		this->bIsEnabled = bIsEnabled;
	}
};

