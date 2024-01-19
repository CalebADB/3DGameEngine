#include "stdafx.h"

namespace ge
{
    void AActor::Update(float deltaTime)
    {
        for (AActor* Actor : AttachedActors)
        {
            Actor->Update(deltaTime);
        }
    }
    void AActor::Render()
    {
        glPushMatrix();
        {
            ApplySceneData();

            GSceneComp::Render();

            for (AActor* Actor : AttachedActors)
            {
                Actor->Render();
            }
        }
        glPopMatrix();
    }

    bool AActor::AttachActor(AActor* Actor)
    {
        if (std::find(AttachedActors.begin(), AttachedActors.end(), Actor) != AttachedActors.end())
        {
            debug::Output(debug::EOutputType::Initialize, "Warning: %s is already in %s's AttachedActors", Actor->GetCharName(), this->GetCharName());
            return false;
        }

        if (Actor->GetOwner() != nullptr)
        {
            debug::Output(debug::EOutputType::Always, "Error: %s is already owned by %s", Actor->GetCharName(), this->GetCharName());
            return false;
        }

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

        // nullify Owner
        Actor->Owner = nullptr;


        return true;
    }

    AActor* AActor::GetOwner() const
    {
        return Owner;
    }
};
