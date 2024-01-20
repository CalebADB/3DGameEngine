#ifndef _GPHYSICALCOMP_H
#define _GPHYSICALCOMP_H

namespace ge 
{
    // Main physics component class
    class GPhysicalComp : GSceneComp
    {
    private:
        GSphereShapeComp* MaxCollisionBound;
        std::list<GShapeComp*> Shapes;

        GLfloat Mass = 1.0;
        math::MVector3 Acceleration = math::MVector3::ZeroVector();
        math::MVector3 Velocity = math::MVector3::ZeroVector();

    public:
        GPhysicalComp(const std::string& Name) 
            : 
            GSceneComp(Name)
        {};

        virtual void Begin();
        void Initialize(GLfloat Mass, math::MVector3 Acceleration, math::MVector3 Velocity);
    protected:
        virtual void Update(float deltaTime);
        virtual void Displace() = 0;
    public:
        void AddShape(GShapeComp* RootShape, GShapeComp* Shape, GLfloat Mass = 0);
        virtual void SetGravity(math::MVector3 Gravity);
        virtual bool CheckCollisionWith(GPhysicalComp* PhysicalComp);
        void AddLinearImpulse(math::MVector3 Impulse);

    };
}


#endif // _GPHYSICALCOMP_H
