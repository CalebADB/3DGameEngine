#include "stdafx.h"

namespace ge
{
    void GSceneComp::UpdateGlobalTransform()
    {
        CalcGlobalTransformData();

        GComp::UpdateGlobalTransform();
    }
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

        glTranslatef(LocalTransformData.Position.X, LocalTransformData.Position.Y, LocalTransformData.Position.Z);
        glMultMatrixf(LocalTransformData.Rotation.ToMatrix().Data());
        glScalef(LocalTransformData.Scale.X, LocalTransformData.Scale.Y, LocalTransformData.Scale.Z);
    }

    math::MTransformData GSceneComp::GetLocalTransformData() const
    {
        return LocalTransformData;
    }
    math::MTransformData GSceneComp::GetGlobalTransformData() const
    {
        return GlobalTransformData;
    }

    void GSceneComp::SetLocalTransformData(math::MTransformData LocalTransformData)
    {
        this->LocalTransformData = LocalTransformData;
    }

    void GSceneComp::CalcGlobalTransformData()
    {
        if (Root == nullptr)
        {
            // if root is nullptr then this object is an instance of AActor which already calculates the global transform data
            return;
        }

        GlobalTransformData = Root->GetGlobalTransformData().TransformedBy(LocalTransformData);
    }

};
