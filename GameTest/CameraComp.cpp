#include "stdafx.h"

namespace ge
{
    void GCameraComp::Update(float deltaTime)
    {
        debug::Output(debug::EOutputType::Update, "Updating GCameraComp_%s ", GetCharName());
    }
    void GCameraComp::Render()
    {
        debug::Output(debug::EOutputType::Render, "Rendering GCameraComp_%s ", GetCharName());
    }

};
