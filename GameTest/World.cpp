#include "stdafx.h"

namespace ge
{
    void AWorld::BeginWorld()
    {
        Begin();

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

        Player = GAMEWORLD->SpawnActor<APlayer>(std::string("Player1"), this, math::MVector3::ZeroVector(), math::MQuaternion::Identity());

        GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape1"), this, math::MVector3(0.0, 0.0, 0.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Teapot, false);
        GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape2"), this, math::MVector3(2.0, 0.0, 0.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Sphere, false);
        GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape4"), this, math::MVector3(0.0, 0.0, 2.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Cube, false);
        GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape3"), this, math::MVector3(-2.0, 0.0, 0.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Dodecahedron, false);
        GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape5"), this, math::MVector3(0.0, 0.0, -2.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Cone, false);
    }

    void AWorld::UpdateWorld(float deltaTime)
	{
        frame++;

        debug::Output(debug::EOutputType::Update, "____________");
        debug::Output(debug::EOutputType::Update, "Update_%05d ", frame);

        Update(deltaTime);
	}
    void AWorld::RenderWorld()
    {
        debug::Output(debug::EOutputType::Render, "____________");
        debug::Output(debug::EOutputType::Render, "Render_%05d ", frame);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();  // Save the current projection matrix
        {
            glLoadIdentity();
            gluPerspective(100.0, (float)APP_VIRTUAL_WIDTH / (float)APP_VIRTUAL_HEIGHT, 0.2, 550.0);
            gluLookAt((5.0 * timer010) + 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

            glPushMatrix();
            {
                if (shader) shader->begin();
                glRotatef(timer010 * 360, 0.5, 1.0f, 0.1f);
                Render();
                if (shader) shader->end();
                
                glutSwapBuffers();
            }
            glPopMatrix();

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
    template<typename AActorSubclass>
    AActorSubclass* AWorld::SpawnActor(const std::string& Name, AActor* Owner, math::MVector3 Position, math::MQuaternion Rotation)
    {
        static_assert(std::is_base_of<AActor, AActorSubclass>::value, "AActorSubclass must be a derived class of AActor");
        math::MTransformData TransformData = math::MTransformData(Position, Rotation, math::MVector3::OneVector());
        AActorSubclass* ActorInstance = new AActorSubclass(Name);

        if (ActorInstance == nullptr)
        {
            debug::Output(debug::EOutputType::Always, "Error: SpawnActor created a nullptr");
            
            return nullptr;
        }

        Owner->AttachActor(ActorInstance);

        Objects.push_back(ActorInstance);

        ActorInstance->Begin();

        return ActorInstance;
    }
    
    template <typename GCompSubclass>
    GCompSubclass* AWorld::NewComp(const std::string& Name)
    {
        //static_assert(std::is_base_of<GComp, GCompSubclass>::value, "GCompSubclass must be a derived class of GComp");

        //GCompSubclass* CompInstance = new GCompSubclass(Name);

        //if (CompInstance == nullptr)
        //{
        //    debug::Output(debug::EOutputType::Always, "Error: NewComp created a nullptr");
        //    
        //    return nullptr;
        //}

        //Objects.push_back(CompInstance);

        //CompInstance->Begin();

        //return CompInstance;

        return nullptr;
    }

};
