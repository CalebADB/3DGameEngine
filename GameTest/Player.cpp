#include "stdafx.h"

namespace ge
{
    //void APlayer::Begin()
    //{
    //    GAMEWORLD->SpawnActor<AEssentialShape>(std::string("Shape10"), this, math::MVector3(0.0, 0.0, 0.0), math::MQuaternion::Identity())->SetEssentialShapeType(EEssentialShapeType::Teapot, false);;
    //}
    void APlayer::Update(float deltaTime)
    {
        debug::Output(debug::EOutputType::Update, "Updating APlayer_%s ", GetCharName());

        AActor::Update(deltaTime);
    }
    void APlayer::Render()
    {
        debug::Output(debug::EOutputType::Render, "Rendering APlayer_%s ", GetCharName());

        AActor::Render();
    }

};
