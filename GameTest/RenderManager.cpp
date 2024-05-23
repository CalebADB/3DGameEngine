#include "stdafx.h"

namespace ge
{
	void GRenderManagerComp::Begin()
	{
		GManagerComp::Begin();
	}

	void GRenderManagerComp::AddShapeComp(GShapeComp* ShapeComp)
	{
		ShapeComps.push_back(ShapeComp);
	}

	void GRenderManagerComp::AssignGameCamera(GCameraComp* CameraComp)
	{
		this->GameCameraComp = CameraComp;
	}

    void GRenderManagerComp::Update(float deltaTime)
    {
        GComp::Update(deltaTime);
        
        //Pulse1 += PulseSpeed * deltaTime;
        //if (Pulse1 > PulseInterval)
        //{
        //    Pulse1 - PulseInterval;
        //}
        
    }
	void GRenderManagerComp::Render()
    {
        // Preliminary checks
        if (GameCameraComp == nullptr)
        {
            return;
        }
        DrawXAtPosition(80, 40);

        // Get camera orientation and position
        math::MQuaternion CamOrientation = GameCameraComp->GetGlobalTransformData().Rotation;
        math::MVector3 CamPosition = GameCameraComp->GetGlobalTransformData().Position; // Ensure this method exists in GSceneComp or GCameraComp

        // Define camera's target based on orientation
        math::MVector3 CamDirection = math::MVector3::ForwardVector().RotatedBy(CamOrientation); // Assuming ForwardVector gives the forward direction in world space
        math::MVector3 CamTarget = CamPosition + CamDirection;

        math::MVector3 CamUp = math::MVector3::UpVector().RotatedBy(CamOrientation);
        // Compute view matrix
        math::MMatrix4x4 ViewMatrix = math::MMatrix4x4::CreateViewMatrix(CamPosition, CamTarget, CamUp);

        // Parameters for the perspective projection
        float FOV = 90.0f; // Field of View, in degrees
        float AspectRatio = static_cast<float>(APP_VIRTUAL_WIDTH) / APP_VIRTUAL_HEIGHT; // Aspect ratio of the viewport
        float NearPlane = 0.1f; // Near clipping plane
        float FarPlane = 1000.0f; // Far clipping plane

        // Compute the perspective projection matrix
        math::MMatrix4x4 ProjectionMatrix = math::MMatrix4x4::CreatePerspectiveProjectionMatrix(FOV, AspectRatio, NearPlane, FarPlane);
        
        // Iterate over each sphere
        for (GShapeComp* ShapeComp : ShapeComps)
        {
            if (!ShapeComp->IsRendered())
            {
                continue;
            }

            GSphereShapeComp* SphereShapeComp = (GSphereShapeComp*)ShapeComp;
            if (SphereShapeComp == nullptr)
            {
                debug::Output(debug::EOutputType::Always, "Error: ShapeComp_%s is not a sphere", SphereShapeComp->GetCharName());
                continue;
            }
            
            // Transform sphere's position to camera's view space
            math::MVector3 spherePosition = SphereShapeComp->GetGlobalTransformData().Position;
            // Get the world coordinate of the sphere's center
            math::MVector3 SphereCenter = ShapeComp->GetGlobalTransformData().Position; // Assuming this method exists

            // Transform to view space
            SphereCenter.TransformPosition(ViewMatrix);

            // Transform to clip space
            SphereCenter.TransformPosition(ProjectionMatrix);

            // Perspective divide (if using a perspective projection)
            if (SphereCenter.Z != 0) // Avoid division by zero
            {
                SphereCenter.X /= SphereCenter.Z;
                SphereCenter.Y /= SphereCenter.Z;
            }
            // Calculate scale factor based on depth
            float ScaleFactor = 33 * SphereShapeComp->GetRadius() / SphereCenter.Z; // Adjust this formula as needed

            // Map from NDC to screen coordinates
            float ScreenX = (SphereCenter.X + 1) * APP_VIRTUAL_WIDTH * 0.5f;
            float ScreenY = (1 - SphereCenter.Y) * APP_VIRTUAL_HEIGHT * 0.5f;

            // Adjust the size of the sphere for drawing
            float SphereSize = 1 * ScaleFactor; // BaseSphereSize is the size of the sphere at depth 1

            // Draw the cross mark
            DrawXAtPosition(ScreenX, ScreenY);

            DrawCircle(ScreenX, ScreenY, SphereSize, 20,0,0,1);

            float SD = SphereShapeComp->GetSignedDistanceFrom(CamPosition);

            //int MaxPulse = std::ceil((SD / PulseInterval) + (SphereShapeComp->GetRadius() * 2));
            //for (int PulseIdx = std::floor(SD / PulseInterval); PulseIdx < MaxPulse; PulseIdx++)
            //{
            //    float Radius = CalculateCrossSectionRadius(SphereShapeComp->GetRadius(), Pulse1 + (PulseIdx * PulseInterval));

            //    DrawCircle(ScreenX, ScreenY, 33 * Radius / SphereCenter.Z, 20, 0.5,0.75,1);

            //}
        }
    }
	void GRenderManagerComp::DrawXAtPosition(float x, float y)
	{
		// Adjust these values as necessary for the size of the 'X'
		float size = 10.0f;
		App::DrawLine(x - size, y - size, x + size, y + size, 1, 0.5, 1); // Diagonal 1
		App::DrawLine(x - size, y + size, x + size, y - size, 1, 0.5, 1); // Diagonal 2
	}
    void GRenderManagerComp::DrawCircle(float centerX, float centerY, float radius, int edges, float r, float g, float b )
    {
        // Ensure that the number of edges is not too low
        if (edges < 3) edges = 3;

        // Angle between each line segment in radians
        float angleStep = 2 * math::M_PI / edges;

        // Store the first point
        float startX = centerX + radius * cos(0);
        float startY = centerY + radius * sin(0);
        float prevX = startX;
        float prevY = startY;

        // Draw the circle in segments
        for (int i = 1; i <= edges; ++i)
        {
            // Calculate the x and y coordinates of the end point
            float endX = centerX + radius * cos(i * angleStep);
            float endY = centerY + radius * sin(i * angleStep);

            // Draw a line from the previous endpoint to the new endpoint
            App::DrawLine(prevX, prevY, endX, endY, r, g, b);

            // Update the previous endpoint
            prevX = endX;
            prevY = endY;
        }

    }
    float GRenderManagerComp::CalculateCrossSectionRadius(float sphereRadius, float zDepth)
    {
        if (std::abs(zDepth) > sphereRadius) {
            return 0; // The slice is outside the sphere.
        }
        return std::sqrt(sphereRadius * sphereRadius - zDepth * zDepth);
    }


}
