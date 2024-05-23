#include "stdafx.h"

namespace ge
{
    void GCameraComp::Begin()
    {
        GSceneComp::Begin();

        //EssentialMeshComp = GAMEWORLD->NewComp<GEssentialMeshComp>(std::string("EssentialMeshComp"));
        //AttachComp(this, EssentialMeshComp);
        //EssentialMeshComp->SetEssentialShapeType(EEssentialShapeType::Cone, false);

        GetCursorPos(&lastMousePos);
    }
    void GCameraComp::Update(float deltaTime)
    {
        GSceneComp::Update(deltaTime);

        if (!bIsMouseCaptured)
        {
            CaptureMouse();
            return;
        }
        ReleaseMouse();

        float MouseDeltaX, MouseDeltaY;
        GetMouseDelta(MouseDeltaX, MouseDeltaY);

        // Apply rotation to the camera using the utility function
       
        math::MTransformData TransformData = GetLocalTransformData();
        TransformData.Rotation = CalcCameraOrientation(deltaTime, MouseDeltaX, MouseDeltaY, Sensitivity);

        SetLocalTransformData(TransformData);
    }

    void GCameraComp::CaptureMouse()
    {
        float MouseX;
        float MouseY;
        App::GetMousePos(MouseX, MouseY);
        if (0 < MouseX && MouseX < APP_INIT_WINDOW_WIDTH
            &&
            0 < MouseY && MouseY < APP_INIT_WINDOW_HEIGHT)
        {
            if (App::IsKeyPressed(VK_LBUTTON) || App::IsKeyPressed(VK_RBUTTON))
            {
                ShowCursor(false);
                bIsMouseCaptured = true;
            }
        }
}

    void GCameraComp::ReleaseMouse()
    {
        if (App::IsKeyPressed(VK_F1))
        {
            ShowCursor(true);
            bIsMouseCaptured = false;
        }
    }

    math::MQuaternion GCameraComp::CalcCameraOrientation(GLfloat deltaTime, GLfloat MouseDeltaX, GLfloat MouseDeltaY, GLfloat Sensitivity)
    {
        CameraYaw += -MouseDeltaX * deltaTime * Sensitivity;
        while (CameraYaw > math::M_DEG360) CameraYaw -= math::M_DEG360;
        while (CameraYaw < 0) CameraYaw += math::M_DEG360;

        CameraPitch += -MouseDeltaY * deltaTime * Sensitivity;
        if (CameraPitch > math::M_DEG90) CameraPitch = math::M_DEG90;
        if (CameraPitch < -math::M_DEG90) CameraPitch = -math::M_DEG90;

        return math::MQuaternion::Identity()
            * math::MQuaternion::FromAxisAngle(math::MVector3::UpVector(), CameraYaw)
            * math::MQuaternion::FromAxisAngle(math::MVector3::RightVector(), CameraPitch);
    }

    void GCameraComp::GetMouseDelta(float& MouseDeltaX, float& MouseDeltaY)
    {
        POINT currentMousePos;
        if (GetCursorPos(&currentMousePos))
        {
            // Calculate the delta values
            MouseDeltaX = static_cast<float>(currentMousePos.x - lastMousePos.x);
            MouseDeltaY = static_cast<float>(currentMousePos.y - lastMousePos.y);

            // Recenter the mouse cursor
            if (bIsMouseCaptured)
            {
                int centerX = APP_INIT_WINDOW_WIDTH / 2;
                int centerY = APP_INIT_WINDOW_HEIGHT / 2;
                SetCursorPos(centerX, centerY);
                lastMousePos.x = centerX;
                lastMousePos.y = centerY;
            }
            else
            {
                // Update the last mouse position
                lastMousePos = currentMousePos;
            }
        }
    }
};
