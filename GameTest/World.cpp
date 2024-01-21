#include "stdafx.h"

namespace ge
{
    void AWorld::BeginWorld()
    {
        AWorld::Begin();

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

        time0 = clock();
        timer010 = 1.0f;
        bUp = true;

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

        frame = -1;

        PhysicsManagerComp = NewComp<GPhysicsManagerComp>("PhysicsManagerComp");
        AttachComp(this, PhysicsManagerComp);

        Player = GAMEWORLD->SpawnActor<APlayer>(std::string("Player1"), this, math::MVector3::ZeroVector(), math::MQuaternion::Identity());

        //GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape1"), this, math::MVector3(0.0, 0.0, 0.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Cube, false);
        //GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape2"), this, math::MVector3(4.0, 0.0, 0.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Sphere, true);
        //GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape3"), this, math::MVector3(0.0, 0.0, 4.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Teapot, false);
        //GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape4"), this, math::MVector3(-4.0, 0.0, 0.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Torus, false);
        //GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape5"), this, math::MVector3(0.0, 0.0, -4.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Cone, false);

        SpherePlanet1 = GAMEWORLD->SpawnActor<ASpherePlanet>(std::string("SpherePlanet1"), this, math::MVector3::ZeroVector(), math::MQuaternion::Identity());
        SpherePlanet1->Initialize(1.0f, math::MVector3::ZeroVector(), math::MVector3::ZeroVector(), 4, 10, 24, math::MVector3(0, 0, 1));

        Prop1 = GAMEWORLD->SpawnActor<ATimeContainerProp>(std::string("TimeContainerProp1"), this, math::MVector3(11.0, -3.0, 0.0), math::MQuaternion::Identity());
        Prop1->Initialize(2.222f, math::MVector3::ZeroVector(), math::MVector3(3, 2, 9), 1, 2, math::MVector3(1, 1, 0));
        Prop2 = GAMEWORLD->SpawnActor<ATimeContainerProp>(std::string("TimeContainerProp2"), this, math::MVector3(0.0, 3.0, 13.0), math::MQuaternion::Identity());
        Prop2->Initialize(1.111f, math::MVector3::ZeroVector(), math::MVector3(12, -2, 0), 0.5, 1, math::MVector3(1, 1, 0));
        Prop3 = GAMEWORLD->SpawnActor<ATimeContainerProp>(std::string("TimeContainerProp3"), this, math::MVector3(6.0, 6.0, 0.0), math::MQuaternion::Identity());
        Prop3->Initialize(1.111f, math::MVector3::ZeroVector(), math::MVector3(-5, -5, 0), 0.5, 1, math::MVector3(1, 1, 0));


        OrbitingBody = GAMEWORLD->SpawnActor<AOrbitingBody>(std::string("Shape1"), SpherePlanet1, math::MVector3::ZeroVector(), math::MQuaternion::Identity());
        OrbitingBody->Initialize(5.0, 2.0);
        OrbitingBody->SetEssentialShapeType(EEssentialShapeType::Cone, false);


    }

    void AWorld::UpdateWorld(float deltaTime)
	{
        frame++;

        debug::Output(debug::EOutputType::Update, "____________");
        debug::Output(debug::EOutputType::Update, "Update_%05d ", frame);

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
        //UpdateGlobalTransform();
        //Render


        //Old OpenGL
        debug::Output(debug::EOutputType::Render, "____________");
        debug::Output(debug::EOutputType::Render, "Render_%05d ", frame);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();  // Save the current projection matrix
        {
            glLoadIdentity();
            gluPerspective(100.0, (float)APP_VIRTUAL_WIDTH / (float)APP_VIRTUAL_HEIGHT, 0.2, 550.0);
            
            glMatrixMode(GL_MODELVIEW);
            gluLookAt(15.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
    /*void AWorld::RenderWorld()
    //{
    //    debug::Output(debug::EOutputType::Render, "____________");
    //    debug::Output(debug::EOutputType::Render, "Render_%05d ", frame);

    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //    glMatrixMode(GL_PROJECTION);
    //    glLoadIdentity();
    //    //gluPerspective(45.0, APP_VIRTUAL_WIDTH / APP_VIRTUAL_HEIGHT, 0.1, 100.0);
    //    //gluPerspective(100.0, (float)APP_VIRTUAL_WIDTH / (float)APP_VIRTUAL_HEIGHT, 0.2, 550.0);

    //    //gluLookAt(32.0f * timer010, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    //    //timer010 = 0.09; //for screenshot!
    //    glPushMatrix();
    //    if (shader) shader->begin();
    //    glRotatef(timer010 * 360, 0.5, 1.0f, 0.1f);
    //    //Render();
    //    //glutSolidTeapot(1.0);
    //    //glutSolidTeapot(2.0);
    //    //glutSolidTeapot(4.0);
    //    //glutSolidTeapot(8.0);
    //    //glutSolidTeapot(16.0);
    //    //glutSolidTeapot(32.0);
    //    if (shader) shader->end();
    //    glutSwapBuffers();
    //    glPopMatrix();

    //    glPushMatrix();
    //    glPopMatrix();

    //    time1 = clock();
    //    float delta = static_cast<float>(static_cast<double>(time1 - time0) / static_cast<double>(CLOCKS_PER_SEC));
    //    delta = delta / 4;
    //    if (delta > 0.00005f)
    //    {
    //        time0 = clock();
    //        if (bUp)
    //        {
    //            timer010 += delta;
    //            if (timer010 >= 1.0f) { timer010 = 1.0f; bUp = false; }
    //        }
    //        else
    //        {
    //            timer010 -= delta;
    //            if (timer010 <= 0.0f) { timer010 = 0.0f; bUp = true; }
    //        }
    //    }
    //}
    */

};
