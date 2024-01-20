#include "stdafx.h"

namespace ge
{
    void GPhysicsManagerComp::Update(float deltaTime)
    {
        debug::Output(debug::EOutputType::Update, "Updating GComp_%s ", GetCharName());
    }
    void GPhysicsManagerComp::Render()
    {
        debug::Output(debug::EOutputType::Render, "Rendering GComp_%s ", GetCharName());
    }

};
