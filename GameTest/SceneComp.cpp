#include "stdafx.h"

namespace ge
{
    void GSceneComp::Update(float deltaTime)
    {
        
    }
    void GSceneComp::Render()
    {
        glPushMatrix();
            ApplySceneData();
            GComp::Render();
        glPopMatrix();
    }
    void GSceneComp::ApplySceneData()
    {
        //glTranslatef(TransformData.Position.X, TransformData.Position.Y, TransformData.Position.Z);
        //glMultMatrixf(TransformData.Rotation.ToMatrix().Data());
        //glScalef(TransformData.Scale.X, TransformData.Scale.Y, TransformData.Scale.Z);
    }
};
