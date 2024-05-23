#include "stdafx.h"

namespace ge
{
    void AWorld::BeginWorld()
    {
        AWorld::Begin();

        time0 = clock();
        timer010 = 1.0f;
        bUp = true;

        frame = -1;

        PhysicsManagerComp = NewComp<GPhysicsManagerComp>("PhysicsManagerComp");
        AttachComp(this, PhysicsManagerComp);
        RenderManagerComp = NewComp<GRenderManagerComp>("RenderManagerComp");
        AttachComp(this, RenderManagerComp);
        

        Player = GAMEWORLD->SpawnActor<APlayer>(std::string("Player1"), this, math::MVector3(-10, 0, 0), math::MQuaternion::Identity());
        Player->Initialize(1.0f, math::MVector3::ZeroVector(), math::MVector3(0, 0, 10), 1, 1, math::MVector3(1, 1, 0));
        RenderManagerComp->AssignGameCamera(Player->FirstPersonCameraComp);

        //GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape1"), this, math::MVector3(0.0, 0.0, 0.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Cube, false);
        //GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape2"), this, math::MVector3(4.0, 0.0, 0.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Sphere, true);
        //GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape3"), this, math::MVector3(0.0, 0.0, 4.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Teapot, false);
        //GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape4"), this, math::MVector3(-4.0, 0.0, 0.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Torus, false);
        //GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape5"), this, math::MVector3(0.0, 0.0, -4.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Cone, false);

        SpherePlanet1 = GAMEWORLD->SpawnActor<ASpherePlanet>(std::string("SpherePlanet1"), this, math::MVector3::ZeroVector(), math::MQuaternion::Identity());
        SpherePlanet1->Initialize(1.0f, math::MVector3::ZeroVector(), math::MVector3::ZeroVector(), 4, 10, 24, math::MVector3(0, 0, 1));

        Prop1 = GAMEWORLD->SpawnActor<ATimeContainerProp>(std::string("TimeContainerProp1"), this, math::MVector3(11.0, -3.0, 0.0), math::MQuaternion::Identity());
        Prop1->Initialize(2.222f, math::MVector3::ZeroVector(), math::MVector3(3, 2, 9), 1, 2, math::MVector3(1, 1, 0));
        //Prop2 = GAMEWORLD->SpawnActor<ATimeContainerProp>(std::string("TimeContainerProp2"), this, math::MVector3(0.0, 3.0, 13.0), math::MQuaternion::Identity());
        //Prop2->Initialize(1.111f, math::MVector3::ZeroVector(), math::MVector3(12, -2, 0), 0.5, 1, math::MVector3(1, 1, 0));
        //Prop3 = GAMEWORLD->SpawnActor<ATimeContainerProp>(std::string("TimeContainerProp3"), this, math::MVector3(0.0, 6.0, 6.0), math::MQuaternion::Identity());
        //Prop3->Initialize(1.111f, math::MVector3::ZeroVector(), math::MVector3(0, -5, -5), 0.5, 1, math::MVector3(0, 1, 1));


        //OrbitingBody = GAMEWORLD->SpawnActor<AOrbitingBody>(std::string("Shape1"), SpherePlanet1, math::MVector3::ZeroVector(), math::MQuaternion::Identity());
        //OrbitingBody->Initialize(5.0, 2.0);
        //OrbitingBody->SetEssentialShapeType(EEssentialShapeType::Cone, false);


        //if(bShouldRenderOpenGL) InitializeOpenGLRender();
    }

    void AWorld::UpdateWorld(float deltaTime)
	{
        frame++;

        debug::Output(debug::EOutputType::Update, "____________");
        debug::Output(debug::EOutputType::Update, "Update_%05d ", frame);

        if (bIsOpenGLTogglePressed)
        {
            if (!App::IsKeyPressed(VK_F2))
            {
                bIsOpenGLTogglePressed = false;
                bShouldRenderOpenGL = !bShouldRenderOpenGL;
            }
        }
        else
        {
            if (App::IsKeyPressed(VK_F2))
            {
                bIsOpenGLTogglePressed = true;
            }
        }
            
            

        //
        UpdateGlobalTransform();
        Update(deltaTime);
        UpdateGlobalTransform();
        PhysicsManagerComp->HandleForces(deltaTime);
        PhysicsManagerComp->HandleDisplacement(deltaTime);
        UpdateGlobalTransform();
        PhysicsManagerComp->CheckCollisions();
    }
    void AWorld::RenderWorld()
    {
        RenderWorldUbisoft();
        //if (bShouldRenderOpenGL) RenderWorldOpenGL();
    }
    void AWorld::RenderWorldUbisoft()
    {
        UpdateGlobalTransform();
        RenderManagerComp->Render();

    }
};
