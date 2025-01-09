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
        
        Player = GAMEWORLD->SpawnActor<APlayer>(std::string("Player1"), this, math::MVector3(-10, 0, 10), math::MQuaternion::FromEuler(math::MVector3(0, -math::M_PI / 2, 0)));
        Player->Initialize(1.0f, math::MVector3::ZeroVector(), math::MVector3(0, 0, 10), 1, 1, math::MVector3(0, 1, 0));
        RenderManagerComp->AssignGameCamera(Player->FirstPersonCameraComp);
        GameCameraComp = Player->FirstPersonCameraComp;

        //GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape1"), this, math::MVector3(0.0, 0.0, 0.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Cube, false);
        //GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape2"), this, math::MVector3(4.0, 0.0, 0.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Sphere, true);
        //GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape3"), this, math::MVector3(0.0, 0.0, 4.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Teapot, false);
        //GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape4"), this, math::MVector3(-4.0, 0.0, 0.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Torus, false);
        //GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape5"), this, math::MVector3(0.0, 0.0, -4.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Cone, false);

        SpherePlanet1 = GAMEWORLD->SpawnActor<ASpherePlanet>(std::string("SpherePlanet1"), this, math::MVector3(0, 0, 10), math::MQuaternion::Identity());
        SpherePlanet1->Initialize(1.0f, math::MVector3::ZeroVector(), math::MVector3::ZeroVector(), 4, 10, 24, math::MVector3(0, 0, 1));

        Prop1 = GAMEWORLD->SpawnActor<ATimeContainerProp>(std::string("TimeContainerProp1"), this, math::MVector3(11.0, -3.0, 10), math::MQuaternion::Identity());
        Prop1->Initialize(2.222f, math::MVector3::ZeroVector(), math::MVector3(3, 2, 9), 1, 2, math::MVector3(1, 1, 0));

        SpherePlanet2 = GAMEWORLD->SpawnActor<ASpherePlanet>(std::string("SpherePlanet2"), this, math::MVector3(40.0, -3.0, 0.0), math::MQuaternion::Identity());
        SpherePlanet2->Initialize(1.0f, math::MVector3::ZeroVector(), math::MVector3::ZeroVector(), 4, 10, 24, math::MVector3(0, 0, 1));

        Prop2 = GAMEWORLD->SpawnActor<ATimeContainerProp>(std::string("TimeContainerProp2"), this, math::MVector3(61.0, -3.0, 0.0), math::MQuaternion::Identity());
        Prop2->Initialize(2.222f, math::MVector3::ZeroVector(), math::MVector3(3, 2, 9), 1, 2, math::MVector3(1, 1, 0));


        //Prop2 = GAMEWORLD->SpawnActor<ATimeContainerProp>(std::string("TimeContainerProp2"), this, math::MVector3(0.0, 3.0, 13.0), math::MQuaternion::Identity());
        //Prop2->Initialize(1.111f, math::MVector3::ZeroVector(), math::MVector3(12, -2, 0), 0.5, 1, math::MVector3(1, 1, 0));
        //Prop3 = GAMEWORLD->SpawnActor<ATimeContainerProp>(std::string("TimeContainerProp3"), this, math::MVector3(0.0, 6.0, 6.0), math::MQuaternion::Identity());
        //Prop3->Initialize(1.111f, math::MVector3::ZeroVector(), math::MVector3(0, -5, -5), 0.5, 1, math::MVector3(0, 1, 1));


        //OrbitingBody = GAMEWORLD->SpawnActor<AOrbitingBody>(std::string("Shape1"), SpherePlanet1, math::MVector3::ZeroVector(), math::MQuaternion::Identity());
        //OrbitingBody->Initialize(5.0, 2.0);
        //OrbitingBody->SetEssentialShapeType(EEssentialShapeType::Cone, false);


        if(!bShouldRenderWithUbisoftAPI) InitializeOpenGLRender();
    }

    void AWorld::UndoInitializeOpenGLRender()
    {
    }

    void AWorld::InitializeOpenGLRender()
    {
        glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);

        shader = SM.loadfromFile("vertexShader.txt", "fragmentShader.txt"); // load (and compile, link) from file
        if (shader == 0)
            ge::debug::Output(debug::EOutputType::Always, "Error: Loading, compiling or linking shader");
        else
        {
            ProgramObject = shader->GetProgramObject();
        }
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);

        // Light model parameters:
        // -------------------------------------------

        GLfloat lmKa[] = { 0.0, 0.0, 0.0, 0.0 };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);

        glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
        glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

        // -------------------------------------------
        // Spotlight Attenuation

        GLfloat spot_direction[] = { 1.0, -1.0, -1.0 };
        GLint spot_exponent = 30;
        GLint spot_cutoff = 180;

        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
        glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
        glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

        GLfloat Kc = 1.0;
        GLfloat Kl = 0.0;
        GLfloat Kq = 0.0;

        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Kc);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);


        // ------------------------------------------- 
        // Lighting parameters:

        GLfloat light_pos[] = { 0.0f, 5.0f, 5.0f, 1.0f };
        GLfloat light_Ka[] = { 1.0f, 0.5f, 0.5f, 1.0f };
        GLfloat light_Kd[] = { 1.0f, 0.1f, 0.1f, 1.0f };
        GLfloat light_Ks[] = { 1.0f, 1.0f, 1.0f, 1.0f };

        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

        // -------------------------------------------
        // Material parameters:

        GLfloat material_Ka[] = { 0.5f, 0.0f, 0.0f, 1.0f };
        GLfloat material_Kd[] = { 0.4f, 0.4f, 0.5f, 1.0f };
        GLfloat material_Ks[] = { 0.8f, 0.8f, 0.0f, 1.0f };
        GLfloat material_Ke[] = { 0.1f, 0.0f, 0.0f, 0.0f };
        GLfloat material_Se = 20.0f;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
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
                bShouldRenderWithUbisoftAPI = !bShouldRenderWithUbisoftAPI;
            }
        }
        else
        {
            if (App::IsKeyPressed(VK_F2))
            {
                bIsOpenGLTogglePressed = true;
            }
        }
            
        if (bIsPausedPressed)
        {
            if (!App::IsKeyPressed(VK_F3))
            {
                bIsPausedPressed = false;
                bIsPaused = !bIsPaused;
            }
        }
        else
        {
            if (App::IsKeyPressed(VK_F3))
            {
                bIsPausedPressed = true;
            }
        }

        //
        UpdateGlobalTransform();
        Update(deltaTime);
        UpdateGlobalTransform();
        if (!bIsPaused)
        {
            PhysicsManagerComp->HandleForces(deltaTime);
            PhysicsManagerComp->HandleDisplacement(deltaTime);
        }
        UpdateGlobalTransform();
        PhysicsManagerComp->CheckCollisions();
        EmptyGarbage();
    }
    void AWorld::RenderWorld()
    {        
        if (bShouldRenderWithUbisoftAPI) RenderWorldUbisoftAPI();
        else RenderWorldOpenGL();
    }
    void AWorld::RenderWorldUbisoftAPI()
    {
        UpdateGlobalTransform();
        RenderManagerComp->Render();
    }
    void AWorld::RenderWorldOpenGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();  // Save the current projection matrix
        {
            glLoadIdentity();

            //gluPerspective(100.0, (float)APP_VIRTUAL_WIDTH / (float)APP_VIRTUAL_HEIGHT, 0.1, 1000.0);
            glOrtho(-20.0f, 20.0f, -20.0f * APP_VIRTUAL_HEIGHT / APP_VIRTUAL_WIDTH, 20.0f * APP_VIRTUAL_HEIGHT / APP_VIRTUAL_WIDTH, -100.1f, 50.f);

            glMatrixMode(GL_MODELVIEW);
            if (GameCameraComp)
            {
                // Get the global transform of the camera
                math::MTransformData camTransform = GameCameraComp->GetGlobalTransformData();

                // Extract the position of the camera
                math::MVector3 camPosition = camTransform.Position;

                // Calculate the forward direction based on the camera's orientation
                math::MVector3 forwardDirection = math::MVector3::BackwardVector().RotatedBy(camTransform.Rotation);

                // Calculate the center position the camera is looking at
                math::MVector3 centerPosition = camPosition + forwardDirection;

                // Transform the up vector by the camera's orientation
                math::MVector3 upVector = math::MVector3::UpVector().RotatedBy(camTransform.Rotation);;

                // Use these values in gluLookAt
                gluLookAt(camPosition.X, camPosition.Y, camPosition.Z,
                    centerPosition.X, centerPosition.Y, centerPosition.Z,
                    upVector.X, upVector.Y, upVector.Z);
            }
            //gluLookAt(15.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            //gluLookAt((15.0 * 1) + 5.0, (10.0 * 1) + 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            //gluLookAt((15.0 * timer010) + 5.0, (10.0 * timer010) + 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

            glPushMatrix();
            {
                if (shader) shader->begin();
                //glRotatef(timer010 * 360.0f, 0, 1.0f, 0);
                Render();
                if (shader) shader->end();

                glutSwapBuffers();
            }
            glPopMatrix();
            glMatrixMode(GL_PROJECTION);
            glutSwapBuffers();
        }
        glPopMatrix();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        time1 = clock();
        float delta = static_cast<float>(static_cast<double>(time1 - time0) / static_cast<double>(CLOCKS_PER_SEC));
        delta = delta / 4;
        if (delta > 0.00005f)
        {
            time0 = clock();
            if (bUp)
            {
                timer010 += delta;
                if (timer010 >= 1.0f) { timer010 = 1.0f; bUp = false; }
            }
            else
            {
                timer010 -= delta;
                if (timer010 <= 0.0f) { timer010 = 0.0f; bUp = true; }
            }
        }
    }

    void AWorld::RemoveActorFromWorld(AActor* Actor)
    {
        AttachedActors.remove(Actor);
    }

    APlayer* AWorld::GetPlayer()
    {
        return Player;
    }

    void AWorld::GarbageObject(GObject* Object)
    {
        auto AttachedActorIter = AttachedActors.begin();

        // Iterate through the vector
        while (AttachedActorIter != AttachedActors.end())
        {
            if (*AttachedActorIter == Object)
            {
                AttachedActors.erase(AttachedActorIter);
                return;
            }
            AttachedActorIter++;
        }

        // Iterator for the vector
        auto ObjectIter = Objects.begin();

        // Iterate through the vector
        while (ObjectIter != Objects.end())
        {
            if (*ObjectIter == Object)
            {
                Objects.erase(ObjectIter);
                return;
            }
            ObjectIter++;
        }

        debug::Output(debug::EOutputType::Always, "ERROR: Object_%s was not in Objects", Object->GetCharName());

        Garbage.push_back(Object);
    }
    void AWorld::EmptyGarbage()
    {
        auto GarbageIter = Garbage.begin();

        while (GarbageIter != Garbage.end())
        {
            delete* GarbageIter;
            
            GarbageIter = Garbage.erase(GarbageIter);
        }
    }
};
