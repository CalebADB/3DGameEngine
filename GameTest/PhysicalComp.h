#ifndef _GPHYSICALCOMP_H
#define _GPHYSICALCOMP_H

namespace ge 
{
    enum struct EPhysicalType
    {
        Null,
        Planet,
        Player,
        PressureWave,
        Projectile,
        Prop
    };
    enum struct EPhysicsType
    {
        Space,
        PlanetSurface
    };

    // Main physics component class
    class GPhysicalComp : public GComp
    {
    protected:
        GLfloat MaxCollisionBound = 0.0;
        std::list<GShapeComp*> Shapes;
        std::vector<GPhysicalComp*> OngoingCollidingPhysicalComps;

        EPhysicalType PhysicalType = EPhysicalType::Null;
        EPhysicsType PhysicsType = EPhysicsType::Space;
        GLfloat Mass = 1.0;
        math::MVector3 Acceleration = math::MVector3::ZeroVector();
        std::list<math::MVector3> Impulses; //Velocity = Velocity + (Impulse / Mass);
        math::MVector3 Velocity = math::MVector3::ZeroVector();

    public:
        GPhysicalComp(const std::string& Name) 
            : 
            GComp(Name)
        {};

        virtual void Begin();
        void Initialize(GLfloat Mass, math::MVector3 Acceleration, math::MVector3 Velocity);

        static bool CalcCollision(GPhysicalComp* PhysicalComp1, GPhysicalComp* PhysicalComp2);
        static math::MVector3 CalcImpulse(GPhysicalComp* PhysicalComp1, GPhysicalComp* PhysicalComp2);

    protected:
        virtual void Update(float deltaTime);

    public:
        EPhysicalType GetPhysicalType() const { return PhysicalType; }
        EPhysicsType GetPhysicsType() const { return PhysicsType; }
        void SetPhysicsType(const EPhysicsType PhysicsType);
        GLfloat GetMass() const { return Mass; }
        math::MVector3 GetVelocity() const { return Velocity; }
        virtual GLfloat GetMaxSize() const { return MaxCollisionBound; }
        virtual void AddShape(GShapeComp* Shape);
        void SetGravity(math::MVector3 Gravity);
        math::MVector3 GetLinearDisplacement(float deltaTime);
        void AddLinearImpulse(GPhysicalComp* InstigatingPhysicalComp, math::MVector3 Impulse);
        bool CheckOngoingCollision(GPhysicalComp* InstigatingPhysicalComp);
        void HandleOngoingCollisions();


    };

    class GPlanetPhysicalComp : public GPhysicalComp
    {

    public:
        GPlanetPhysicalComp(const std::string& Name)
            :
            GPhysicalComp(Name)
        {};
        virtual void Begin();

    protected:
        virtual void Update(float deltaTime);
    };
    
    class GPlayerPhysicalComp : public GPhysicalComp
    {

    public:
        GPlayerPhysicalComp(const std::string& Name)
            :
            GPhysicalComp(Name)
        {};
        virtual void Begin();

    protected:
        virtual void Update(float deltaTime);
    };

    class GPressureWavePhysicalComp : public GPhysicalComp
    {

    public:
        GPressureWavePhysicalComp(const std::string& Name)
            :
            GPhysicalComp(Name)
        {};
        virtual void Begin();

    protected:
        virtual void Update(float deltaTime);
    };

    class GProjectilePhysicalComp : public GPhysicalComp
    {

    public:
        GProjectilePhysicalComp(const std::string& Name)
            :
            GPhysicalComp(Name)
        {};
        virtual void Begin();

    protected:
        virtual void Update(float deltaTime);
    };

    class GPropPhysicalComp : public GPhysicalComp
    {

    public:
        GPropPhysicalComp(const std::string& Name)
            :
            GPhysicalComp(Name)
        {};
        virtual void Begin();

    protected:
        virtual void Update(float deltaTime);
    };
}


#endif // _GPHYSICALCOMP_H
