#include "stdafx.h"

namespace ge
{
	void GComp::UpdateGlobalTransform()
	{
		for (GComp* Comp : AttachedComps)
		{
			Comp->UpdateGlobalTransform();
		}
	}
	void GComp::Update(float deltaTime)
	{
		for (GComp* Comp : AttachedComps)
		{
			Comp->Update(deltaTime);
		}
	}
	void GComp::Render()
	{
		for (GComp* Comp : AttachedComps)
		{
			Comp->Render();
		}
	}

	bool GComp::AttachComp(GComp* RootComp, GComp* Comp)
	{
		if (Comp == nullptr)
		{
			debug::Output(debug::EOutputType::Initialize, "Warning: GComp_%s attempted to attach a nullptr Comp", this->GetCharName());
			return false;
		}

		AttachedComps.push_back(Comp);		
	}

	math::MTransformData GComp::GetLocalTransformData()
	{
		return Root->GetLocalTransformData();
	}
	math::MTransformData GComp::GetGlobalTransformData()
	{
		return Root->GetGlobalTransformData();
	}

};
