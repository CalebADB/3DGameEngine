#ifndef _GPLAYERCONTROLLER_H
#define _GPLAYERCONTROLLER_H

namespace ge
{
    class GPlayerControllerComp : public GComp
    {
    protected:
        GPhysicalComp* PhysicalComp = nullptr;

        GLfloat SurfaceSpeed = 40;
        GLfloat SpaceSpeed = 20;
        math::MVector3 Impulse = math::MVector3::ZeroVector();
        math::MVector3 LocalUp = math::MVector3::ZeroVector();

        bool bIsJumpQueued = false;
        float bIsJumpImpulseFactor = 20;

    public:
        GPlayerControllerComp(const std::string& Name)
            :
            GComp(Name)
        {}

        void Initialize(GPhysicalComp* PhysicalComp);
    protected:
        virtual void Update(float deltaTime);

    public:
        bool IsJumpQueued() const { return bIsJumpQueued; }
        void SetLocalUp(math::MVector3 LocalUp);
        math::MVector3 GetLinearDisplacement(float deltaTime);
        math::MVector3 GetJumpImpulse();

    private:
        void UpdateFrameImpulse(float deltaTime);
    };
}

#endif // _GPLAYERCONTROLLER_H
