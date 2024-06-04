#ifndef _GPLANETNAVIGATORCOMP_H
#define _GPLANETNAVIGATORCOMP_H

namespace ge
{
    class APlanet;

    // Main physics component class
    class GPlanetNavigationComp : public GComp
    {
    protected:
        // Navigator Propertied
        AActor* Navigator = nullptr;
        GPhysicalComp* PhysicalComp = nullptr;
        GLfloat GroundDisplacement = 0.0;

        // Planet Properties
        APlanet* Planet = nullptr;

        math::MVector3 PlanetNorthPole = math::MVector3::UpVector();
        math::MQuaternion SphericalLocation = math::MQuaternion::Identity();
        math::MQuaternion Direction = math::MQuaternion::Identity();
        GLfloat PlanetRadius = 0.0f;
        GLfloat NavigatorTangentialSpeed = 0.0f;

    public:
        GPlanetNavigationComp(const std::string& Name)
            :
            GComp(Name)
        {};

        virtual void Begin();
        void Initialize(GPhysicalComp* PhysicalComp, GLfloat GroundDisplacement);
    protected:
        virtual void Update(float deltaTime);

        virtual void Destroy();

    public:
        bool IsEmbarked() const { return PhysicalComp->GetPhysicsType() == EPhysicsType::PlanetSurface; }
        virtual void EmbarkOn(APlanet* Planet, math::MVector3 NavigatorVelocity);
        virtual void Disembark(GPhysicalComp* InstigatingPhysicalComp, math::MVector3 Impulse);
        math::MTransformData GetLocalTransformData();

        math::MVector3 GetNavigatorUp();
        APlanet* GetEmbarkedPlanet() const;
    };
}

#endif // _GPLANETNAVIGATORCOMP_H
