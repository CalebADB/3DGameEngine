#include "stdafx.h"

namespace ge
{
    void GPhysicsManagerComp::Begin()
    {
        Octree = GAMEWORLD->NewObject<GOctree>("Octree");
        Octree->Initialize(math::MVector3::ZeroVector(), 200.0f);
    }
    void GPhysicsManagerComp::AddPlayerControllerComp(GPlayerControllerComp* PlayerControllerComp)
    {
        PlayerControllerComps.push_back(PlayerControllerComp);
    }
    void GPhysicsManagerComp::AddPhysicalComp(GPhysicalComp* PhysicalComp)
    {
        PhysicalComps.push_back(PhysicalComp);
        Octree->Insert(PhysicalComp);
    }

    void GPhysicsManagerComp::AddPlanetNavigationComp(GPlanetNavigationComp* PlanetNavigationComp)
    {
        PlanetNavigationComps.push_back(PlanetNavigationComp);
    }

    void GPhysicsManagerComp::AddGravityWellComp(GGravityWellComp* GravityWellComp)
    {
        GravityWellComps.push_back(GravityWellComp);
    }

    void GPhysicsManagerComp::RemovePlayerControllerComp(GPlayerControllerComp* PlayerControllerComp)
    {
        // Iterator for the vector
        auto it = PlayerControllerComps.begin();

        // Iterate through the vector
        while (it != PlayerControllerComps.end())
        {
            if (*it == PlayerControllerComp)
            {
                PlayerControllerComps.erase(it);

                return;
            }
            it++;
        }

        debug::Output(debug::EOutputType::Always, "ERROR: PlayerControllerComp_%s was not in PlayerControllerComps", PlayerControllerComp->GetCharName());
    }

    void GPhysicsManagerComp::RemovePhysicalComp(GPhysicalComp* PhysicalComp)
    {
        // Iterator for the vector
        auto it = PhysicalComps.begin();

        // Iterate through the vector
        while (it != PhysicalComps.end())
        {
            if (*it == PhysicalComp)
            {
                Octree->Remove(PhysicalComp);
                PhysicalComps.erase(it);
                return;
            }
            it++;
        }

        debug::Output(debug::EOutputType::Always, "ERROR: PhysicalComp_%s was not in PhysicalComps", PhysicalComp->GetCharName());
    }

    void GPhysicsManagerComp::RemovePlanetNavigationComp(GPlanetNavigationComp* PlanetNavigationComp)
    {
        // Iterator for the vector
        auto it = PlanetNavigationComps.begin();

        // Iterate through the vector
        while (it != PlanetNavigationComps.end())
        {
            if (*it == PlanetNavigationComp)
            {
                PlanetNavigationComps.erase(it);

                return;
            }
            it++;
        }

        debug::Output(debug::EOutputType::Always, "ERROR: PlanetNavigationComp_%s was not in PlanetNavigationComps", PlanetNavigationComp->GetCharName());
    }

    void GPhysicsManagerComp::RemoveGravityWellComp(GGravityWellComp* GravityWellComp)
    {

    }

    void GPhysicsManagerComp::HandleForces(float deltaTime)
    {
        for (GPlayerControllerComp* PlayerControllerComp : PlayerControllerComps)
        {
            //Determine down based on gravity so that 
            PlayerControllerComp->SetLocalUp(math::MVector3::FlipVector(GetGravityAtPosition(PlayerControllerComp->GetGlobalTransformData().Position)).Normalized());

            math::MVector3 Displacement = PlayerControllerComp->GetLinearDisplacement(deltaTime);
            AActor* Actor = (AActor*)PlayerControllerComp->GetActorRoot();
            if (Actor == nullptr)
            {
                debug::Output(debug::EOutputType::Always, "Error: PlayerControllerComp_%s does not have a root actor", PlayerControllerComp->GetCharName());
                continue;
            }

            math::MTransformData LocalTransformData = Actor->GetLocalTransformData();
            LocalTransformData.Translate(Displacement);
            Actor->SetLocalTransformData(LocalTransformData);

            if (PlayerControllerComp->IsJumpQueued())
            {
                GPlanetNavigationComp* PlanetNavigationComp = ((APlayer*)(PlayerControllerComp->GetActorRoot()))->PlanetNavigationComp;
                PlanetNavigationComp->Disembark(PlanetNavigationComp->GetEmbarkedPlanet()->GetPhysicalComp(), PlayerControllerComp->GetJumpImpulse());
            }
        }
        for (GPhysicalComp* PhysicalComp : PhysicalComps)
        {
            switch (PhysicalComp->GetPhysicalType())
            {
            case EPhysicalType::Planet:
            {
                break;
            }
            case EPhysicalType::Player:
            {
                PhysicalComp->SetGravity(GetGravityAtPosition(PhysicalComp->GetGlobalTransformData().Position));

                break;
            }
            case EPhysicalType::Projectile:
            {
                PhysicalComp->SetGravity(GetGravityAtPosition(PhysicalComp->GetGlobalTransformData().Position));

                break;
            }
            case EPhysicalType::Prop:
            {
                PhysicalComp->SetGravity(GetGravityAtPosition(PhysicalComp->GetGlobalTransformData().Position));

                break;
            }
            }
        }
    }

    void GPhysicsManagerComp::HandleDisplacement(float deltaTime)
    {

        for (GPhysicalComp* PhysicalComp : PhysicalComps)
        {
            if (PhysicalComp->GetPhysicsType() == EPhysicsType::PlanetSurface)
            {
                continue;
            }

            math::MVector3 Displacement = PhysicalComp->GetLinearDisplacement(deltaTime);
            AActor* Actor = (AActor*)PhysicalComp->GetActorRoot();
            if (Actor == nullptr)
            {
                debug::Output(debug::EOutputType::Always, "Error: PhysicalComp_%s does not have a root actor", PhysicalComp->GetCharName());
                continue;
            }

            math::MTransformData LocalTransformData = Actor->GetLocalTransformData();
            LocalTransformData.Translate(Displacement);
            Actor->SetLocalTransformData(LocalTransformData);
        }

        for (GPlanetNavigationComp* PlanetNavigationComp : PlanetNavigationComps)
        {
            if (!PlanetNavigationComp->IsEmbarked())
            {
                continue;
            }

            AActor* Actor = (AActor*)PlanetNavigationComp->GetActorRoot();
            if (Actor == nullptr)
            {
                debug::Output(debug::EOutputType::Always, "Error: PlanetNavigationComp_%s does not have a root actor", PlanetNavigationComp->GetCharName());
                continue;
            }

            math::MTransformData LocalTransformData = PlanetNavigationComp->GetLocalTransformData();
            //math::MVector3 udh = math::MQuaternion::ToEuler(LocalTransformData.Rotation);
            Actor->SetLocalTransformData(LocalTransformData);
        }

        
    }

    math::MVector3 GPhysicsManagerComp::GetGravityAtPosition(math::MVector3 Position)
    {
        math::MVector3 Gravity = math::MVector3::ZeroVector();
        
        for (GGravityWellComp* GravityWellComp : GravityWellComps)
        {
            Gravity = Gravity + GravityWellComp->GetGravityAtPosition(Position);
        }
        return Gravity;
    }

    void GPhysicsManagerComp::CheckCollisions()
    {
        // Iterate through all physical components
        for (GPhysicalComp* PhysicalComp1 : PhysicalComps)
        {
            for (GPhysicalComp* PhysicalComp2 : Octree->GetPossibleCollisions(PhysicalComp1))
            {
                if (PhysicalComp1 == PhysicalComp2) continue; 

                if (!GPhysicalComp::CalcCollision(PhysicalComp1, PhysicalComp2)) continue;

                HandleCollision(PhysicalComp1, PhysicalComp2);
            }
        }

        for (GPhysicalComp* PhysicalComp : PhysicalComps)
        {
            PhysicalComp->HandleOngoingCollisions();
        }

    }

    void GPhysicsManagerComp::HandleCollision(GPhysicalComp* PhysicalComp1, GPhysicalComp* PhysicalComp2)
    {
        math::MVector3 Impulse = GPhysicalComp::CalcImpulse(PhysicalComp2, PhysicalComp1);

        switch (PhysicalComp1->GetPhysicalType())
        {
        case EPhysicalType::Planet: HandlePlanetCollisionImpact((GPlanetPhysicalComp*)PhysicalComp1); break;
        case EPhysicalType::Player: HandlePlayerCollisionImpact((GPlayerPhysicalComp*)PhysicalComp1, PhysicalComp2, Impulse); break;
        case EPhysicalType::PressureWave: HandlePressureWaveCollisionImpact((GPressureWavePhysicalComp*)PhysicalComp1); break;
        case EPhysicalType::Projectile: HandleProjectileCollisionImpact((GProjectilePhysicalComp*)PhysicalComp1, Impulse); break; 
        case EPhysicalType::Prop: HandlePropCollisionImpact((GPropPhysicalComp*)PhysicalComp1, PhysicalComp2, Impulse); break;
        }

        switch (PhysicalComp2->GetPhysicalType())
        {
        case EPhysicalType::Planet: HandlePlanetCollisionImpact((GPlanetPhysicalComp*)PhysicalComp2); break;
        case EPhysicalType::Player: HandlePlayerCollisionImpact((GPlayerPhysicalComp*)PhysicalComp2, PhysicalComp1, math::MVector3::FlipVector(Impulse)); break;
        case EPhysicalType::PressureWave: HandlePressureWaveCollisionImpact((GPressureWavePhysicalComp*)PhysicalComp1); break;
        case EPhysicalType::Projectile: HandleProjectileCollisionImpact((GProjectilePhysicalComp*)PhysicalComp2, math::MVector3::FlipVector(Impulse)); break;
        case EPhysicalType::Prop: HandlePropCollisionImpact((GPropPhysicalComp*)PhysicalComp2, PhysicalComp1, math::MVector3::FlipVector(Impulse)); break;
        }
    }

    void GPhysicsManagerComp::HandlePlanetCollisionImpact(GPlanetPhysicalComp* TargetPhysicalComp)
    {
        APlanet* Planet = (APlanet*)TargetPhysicalComp->GetActorRoot();
        if (Planet == nullptr)
        {
            debug::Output(debug::EOutputType::Always, "Error: TargetPhysicalComp_%s does not have a root APlanet", TargetPhysicalComp->GetCharName());
            return;
        }

        // Planets shouldn't need much impact handling because they're big and should be static or is static orbits. Levels should be designed to avoid planet collision

        // ... but maybe one day this is where breakable planets would go
    }

    void GPhysicsManagerComp::HandlePlayerCollisionImpact(GPlayerPhysicalComp* TargetPhysicalComp, GPhysicalComp* InstigatingPhysicalComp, math::MVector3 Impulse)
    {
        APlayer* Player = (APlayer*)TargetPhysicalComp->GetActorRoot();
        if (Player == nullptr)
        {
            debug::Output(debug::EOutputType::Always, "Error: TargetPhysicalComp_%s does not have a root APlayer", TargetPhysicalComp->GetCharName());
            return;
        }

        switch (InstigatingPhysicalComp->GetPhysicalType())
        {
        case EPhysicalType::Planet:
        {
            APlanet* Planet = (APlanet*)InstigatingPhysicalComp->GetActorRoot();
            if (Planet == nullptr)
            {
                debug::Output(debug::EOutputType::Always, "Error: InstigatingPhysicalComp_%s does not have a root APlanet", InstigatingPhysicalComp->GetCharName());
                return;
            }

            switch (TargetPhysicalComp->GetPhysicsType())
            {
            case EPhysicsType::Space:
            {
                if (TargetPhysicalComp->CheckOngoingCollision(Planet->GetPhysicalComp()))
                {
                    return;
                }

                Player->PlanetNavigationComp->EmbarkOn(Planet, TargetPhysicalComp->GetVelocity()); break;
                break;
            }
            }

            break;
        }        
        case EPhysicalType::Player:
        {
            switch (TargetPhysicalComp->GetPhysicsType())
            {
            case EPhysicsType::Space: TargetPhysicalComp->AddLinearImpulse(InstigatingPhysicalComp, Impulse); break;
            case EPhysicsType::PlanetSurface: Player->PlanetNavigationComp->Disembark(InstigatingPhysicalComp, Impulse); break;
            }

            break;
        }
        case EPhysicalType::PressureWave:
        {
            switch (TargetPhysicalComp->GetPhysicsType())
            {
            case EPhysicsType::Space: TargetPhysicalComp->AddLinearImpulse(InstigatingPhysicalComp, Impulse); break;
            case EPhysicsType::PlanetSurface: Player->PlanetNavigationComp->Disembark(InstigatingPhysicalComp, Impulse); break;
            }

            break;
        }
        case EPhysicalType::Projectile:
        {
            switch (TargetPhysicalComp->GetPhysicsType())
            {
            case EPhysicsType::Space: TargetPhysicalComp->AddLinearImpulse(InstigatingPhysicalComp, Impulse); break;
            case EPhysicsType::PlanetSurface: Player->PlanetNavigationComp->Disembark(InstigatingPhysicalComp, Impulse); break;
            }

            break;
        }
        case EPhysicalType::Prop:
        {
            switch (TargetPhysicalComp->GetPhysicsType())
            {
            case EPhysicsType::Space: TargetPhysicalComp->AddLinearImpulse(InstigatingPhysicalComp, Impulse); break;
            case EPhysicsType::PlanetSurface: Player->PlanetNavigationComp->Disembark(InstigatingPhysicalComp, Impulse); break;
            }

            break;
        }
        }
    }

    void GPhysicsManagerComp::HandlePressureWaveCollisionImpact(GPressureWavePhysicalComp* TargetPhysicalComp)
    {
        APressureWave* PressureWave = (APressureWave*)TargetPhysicalComp->GetActorRoot();
        if (PressureWave == nullptr)
        {
            debug::Output(debug::EOutputType::Always, "Error: TargetPhysicalComp_%s does not have a root APressureWave", TargetPhysicalComp->GetCharName());
            return;
        }

        // Planets shouldn't need much impact handling because they're big and should be static or is static orbits. Levels should be designed to avoid planet collision

        // ... but maybe one day this is where breakable planets would go
    }

    void GPhysicsManagerComp::HandleProjectileCollisionImpact(GProjectilePhysicalComp* TargetPhysicalComp, math::MVector3 Impulse)
    {
        AProjectile* Projectile = (AProjectile*)TargetPhysicalComp->GetActorRoot();
        if (Projectile == nullptr)
        {
            debug::Output(debug::EOutputType::Always, "Error: TargetPhysicalComp_%s does not have a root AProjectile", TargetPhysicalComp->GetCharName());
            return;
        }
    }

    void GPhysicsManagerComp::HandlePropCollisionImpact(GPropPhysicalComp* TargetPhysicalComp, GPhysicalComp* InstigatingPhysicalComp, math::MVector3 Impulse)
    {
        AProp* Prop = (AProp*)TargetPhysicalComp->GetActorRoot();
        if (Prop == nullptr)
        {
            debug::Output(debug::EOutputType::Always, "Error: TargetPhysicalComp_%s does not have a root AProp ", TargetPhysicalComp->GetCharName());
            return;
        }

        switch (InstigatingPhysicalComp->GetPhysicalType())
        {
        case EPhysicalType::Planet:
        {
            APlanet* Planet = (APlanet*)InstigatingPhysicalComp->GetActorRoot();
            if (Planet == nullptr)
            {
                debug::Output(debug::EOutputType::Always, "Error: InstigatingPhysicalComp_%s does not have a root APlanet", InstigatingPhysicalComp->GetCharName());
                return;
            }

            switch (TargetPhysicalComp->GetPhysicsType())
            {
            case EPhysicsType::Space: Prop->PlanetNavigationComp->EmbarkOn(Planet, TargetPhysicalComp->GetVelocity()); break;
            }

            break;
        }
        case EPhysicalType::Player:
        {
            switch (TargetPhysicalComp->GetPhysicsType())
            {
            case EPhysicsType::Space: TargetPhysicalComp->AddLinearImpulse(InstigatingPhysicalComp, Impulse); break;
            case EPhysicsType::PlanetSurface: Prop->PlanetNavigationComp->Disembark(InstigatingPhysicalComp, Impulse); break;
            }

            break;
        }
        case EPhysicalType::PressureWave:
        {
            switch (TargetPhysicalComp->GetPhysicsType())
            {
            case EPhysicsType::Space: TargetPhysicalComp->AddLinearImpulse(InstigatingPhysicalComp, Impulse); break;
            case EPhysicsType::PlanetSurface: Prop->PlanetNavigationComp->Disembark(InstigatingPhysicalComp, Impulse); break;
            }

            break;
        }
        case EPhysicalType::Projectile:
        {
            switch (TargetPhysicalComp->GetPhysicsType())
            {
            case EPhysicsType::Space: TargetPhysicalComp->AddLinearImpulse(InstigatingPhysicalComp, Impulse); break;
            case EPhysicsType::PlanetSurface: Prop->PlanetNavigationComp->Disembark(InstigatingPhysicalComp, Impulse); break;
            }

            break;
        }
        case EPhysicalType::Prop:
        {
            switch (TargetPhysicalComp->GetPhysicsType())
            {
            case EPhysicsType::Space: TargetPhysicalComp->AddLinearImpulse(InstigatingPhysicalComp, Impulse); break;
            case EPhysicsType::PlanetSurface: Prop->PlanetNavigationComp->Disembark(InstigatingPhysicalComp, Impulse); break;
            }

            break;
        }
        }
    }
};
