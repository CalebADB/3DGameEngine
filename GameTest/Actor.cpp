#include "stdafx.h"

namespace ge
{
    void AActor::UpdateGlobalTransform()
    {
        CalcGlobalTransformData();

        GSceneComp::UpdateGlobalTransform();

        auto ActorIter = AttachedActors.begin();
        while (ActorIter != AttachedActors.end())
        {
            AActor* Actor = *ActorIter;
            ActorIter++;

            Actor->UpdateGlobalTransform();
        }
    }
    void AActor::Update(float deltaTime)
    {
        GSceneComp::Update(deltaTime);

        auto ActorIter = AttachedActors.begin();
        while (ActorIter != AttachedActors.end())
        {
            AActor* Actor = *ActorIter;
            ActorIter++;

            Actor->Update(deltaTime);
        }
    }
    void AActor::Render()
    {
        glPushMatrix();
        {
            debug::Output(debug::EOutputType::Render, "%s: Attached comps:", GetCharName());
            GSceneComp::Render();

            debug::Output(debug::EOutputType::Render, "%s: Attached actors:", GetCharName());
            RenderSceneData();

            auto ActorIter = AttachedActors.begin();
            while (ActorIter != AttachedActors.end())
            {
                AActor* Actor = *ActorIter;
                ActorIter++;

                Actor->Render();
                debug::Output(debug::EOutputType::Render, "%s: Render Begins: ", Actor->GetCharName());
            }

            debug::Output(debug::EOutputType::Render, "%s: Render Ends: ", GetCharName());
        }
        glPopMatrix();
    }

    void AActor::Destroy()
    {
        Owner->DettachActor(this);

        GSceneComp::Destroy();
    }

    bool AActor::AttachActor(AActor* Actor)
    {
        if (std::find(AttachedActors.begin(), AttachedActors.end(), Actor) != AttachedActors.end())
        {
            debug::Output(debug::EOutputType::Initialize, "Warning: %s is already in %s's AttachedActors", Actor->GetCharName(), this->GetCharName());
            return false;
        }

        if (Actor->GetOwner() == nullptr)
        {
 
        }
        else if (Actor->GetOwner() != GAMEWORLD)
        {
            Actor->GetOwner()->DettachActor(Actor);
        }

        math::MTransformData OwnerTransformData = GetGlobalTransformData();

        math::MTransformData NewLocalTransformData = Actor->GetGlobalTransformData();
        NewLocalTransformData.Translate(OwnerTransformData.Position);

        Actor->SetLocalTransformData(NewLocalTransformData);

        // Briefly disconnect from world
        GAMEWORLD->RemoveActorFromWorld(Actor);

        // set Owner
        Actor->Owner = this;

        // add to list
        AttachedActors.push_back(Actor);

        return true;
    }

    bool AActor::DettachActor(AActor* Actor)
    {
        if (Actor->GetOwner() != this)
        {
            debug::Output(debug::EOutputType::Initialize, "Warning: %s is not Owned by %s", Actor->GetCharName(), this->GetCharName());
            return false;
        }
        
        if (std::find(AttachedActors.begin(), AttachedActors.end(), Actor) == AttachedActors.end())
        {
            debug::Output(debug::EOutputType::Initialize, "Warning: %s is not in %s's AttachedActors", Actor->GetCharName(), this->GetCharName());
            return false;
        }

        // remove from list
        AttachedActors.remove(Actor);

        // Put in global space
        GAMEWORLD->AttachActor(Actor);

        return true;
    }

    AActor* AActor::GetOwner() const
    {
        return Owner;
    }

    void AActor::CalcGlobalTransformData()
    {
        if (GetOwner() == nullptr)
        {
            return;
        }

        GlobalTransformData = GetOwner()->GetGlobalTransformData().TransformedBy(LocalTransformData);
    }
};
