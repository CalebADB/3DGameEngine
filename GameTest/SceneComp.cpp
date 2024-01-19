#include "stdafx.h"

namespace ge
{
    void GSceneComp::Update(float deltaTime)
    {

        GComp::Update(deltaTime);
    }
    void GSceneComp::Render()
    {
        glPushMatrix();
            RenderSceneData();
            GComp::Render();
        glPopMatrix();
    }
    void GSceneComp::RenderSceneData()
    {
        debug::Output(debug::EOutputType::Render, "ApplySceneData_%s", GetCharName());

        glTranslatef(TransformData.Position.X, TransformData.Position.Y, TransformData.Position.Z);
        glMultMatrixf(TransformData.Rotation.ToMatrix().Data());
        //glScalef(TransformData.Scale.X, TransformData.Scale.Y, TransformData.Scale.Z);
    }
};
