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
		RootComp->AttachedComps.push_back(Comp);

		Comp->Root = RootComp;
	}

	GComp* GComp::GetActorRoot()
	{
		if (Root != nullptr)
		{
			return Root->GetActorRoot();
		}

		return this;
	}

	math::MTransformData GComp::GetLocalTransformData() const
	{
		return Root->GetLocalTransformData();
	}
	math::MTransformData GComp::GetGlobalTransformData() const
	{
		return Root->GetGlobalTransformData();
	}

};
