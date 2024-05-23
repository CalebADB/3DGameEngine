#ifndef _GPLAYERPLANETNAVIGATORCOMP_H
#define _GPLAYERPLANETNAVIGATORCOMP_H

namespace ge
{
    class APlanet;

    // Main physics component class
    class GPlayerPlanetNavigationComp : public GPlanetNavigationComp
    {
    private:
        GPlayerControllerComp* PlayerControllerComp;

    public:
        GPlayerPlanetNavigationComp(const std::string& Name)
            :
            GPlanetNavigationComp(Name)
        {};

        void Initialize(GPhysicalComp* PhysicalComp, GLfloat GroundDisplacement, GPlayerControllerComp * PlayerControllerComp);

    public:
        virtual void EmbarkOn(APlanet* Planet, math::MVector3 NavigatorVelocity) override;
        virtual void Disembark(GPhysicalComp* InstigatingPhysicalComp, math::MVector3 Impulse) override;
    };
}

#endif // _GPLAYERPLANETNAVIGATORCOMP_H
