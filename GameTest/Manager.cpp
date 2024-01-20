#include "stdafx.h"

namespace ge
{
    void GManagerComp::Update(float deltaTime)
    {
        debug::Output(debug::EOutputType::Update, "Updating GComp_%s ", GetCharName());
    }
    void GManagerComp::Render()
    {
        debug::Output(debug::EOutputType::Render, "Rendering GComp_%s ", GetCharName());
    }

};
