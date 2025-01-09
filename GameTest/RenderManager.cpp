#include "stdafx.h"

namespace ge
{
	void GRenderManagerComp::Begin()
	{
		GManagerComp::Begin();
	}

    void GRenderManagerComp::AssignGameCamera(GCameraComp* CameraComp)
	{
		this->GameCameraComp = CameraComp;
	}

    void GRenderManagerComp::AddShapeComp(GShapeComp* ShapeComp)
    {
        ShapeComps.push_back(ShapeComp);
    }

    void GRenderManagerComp::RemoveShapeComp(GShapeComp* ShapeComp)
    {
        // Iterator for the vector
        auto ShapeCompIter = ShapeComps.begin();

        // Iterate through the vector
        while (ShapeCompIter != ShapeComps.end())
        {
            if (*ShapeCompIter == ShapeComp)
            {
                ShapeComps.erase(ShapeCompIter);
                return;
            }
            ShapeCompIter++;
        }

        debug::Output(debug::EOutputType::Always, "ERROR: PhysicalComp_%s was not in PhysicalComps", ShapeComp->GetCharName());
    }


    void GRenderManagerComp::Update(float deltaTime)
    {
        GComp::Update(deltaTime);
    }

	void GRenderManagerComp::Render()
    {
        // Preliminary checks
        if (GameCameraComp == nullptr)
        {
            return;
        }

        // Get camera orientation and position
        math::MQuaternion CamOrientation = GameCameraComp->GetGlobalTransformData().Rotation;
        math::MVector3 CamPosition = GameCameraComp->GetGlobalTransformData().Position; // Ensure this method exists in GSceneComp or GCameraComp

        // Define camera's target based on orientation
        math::MVector3 CamDirection = math::MVector3::ForwardVector().RotatedBy(CamOrientation); // Assuming ForwardVector gives the forward direction in world space
        math::MVector3 CamTarget = CamPosition + CamDirection;

        math::MVector3 CamUp = math::MVector3::UpVector().RotatedBy(CamOrientation);
        // Compute view matrix
        math::MMatrix4x4 ViewMatrix = math::MMatrix4x4::CreateViewMatrix(CamPosition, CamTarget, CamUp);

        math::MMatrix4x4 ProjectionMatrix = ProjectionMatrix2();

        APlayer* Player = GAMEWORLD->GetPlayer();
        math::MVector3 PlayerPosition = math::MVector3::ZeroVector();
        if (Player != nullptr)
        {
            PlayerPosition = Player->GetGlobalTransformData().Position;
        }
        else
        {
            debug::Output(debug::EOutputType::Always, "Error: Player is null");
        }

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
            
            // Get the world coordinate of the sphere's center
            math::MVector3 SphereCenter = ShapeComp->GetGlobalTransformData().Position; // Assuming this method exists
            math::MQuaternion SphereRotation = ShapeComp->GetGlobalTransformData().Rotation; // Assuming this method exists
            math::MVector3 Scale = ShapeComp->GetGlobalTransformData().Scale; // Assuming this method exists

            
            // hmm2
            // Get vertex locations
            GSphereVertexMesh* SphereVertexMesh = ShapeComp->GetSphereVertexMesh();
            math::MVector3 NorthPole = math::MVector3(SphereVertexMesh->NorthPoleDisplacement.X * Scale.X, SphereVertexMesh->NorthPoleDisplacement.Y * Scale.Y, SphereVertexMesh->NorthPoleDisplacement.Z * Scale.Z) * SphereShapeComp->GetRadius();

            std::vector<std::vector<math::MVector3>> GlobalVertexDisplacementss = {};
            int SmallestRotationLongitudeIdx = 0;
            int SmallestRotationLatitudeIdx = 0;
            GSphereVertex* PlanetFacingVertex = SphereVertexMesh->NorthPoleVertex;
            if (SphereVertexMesh != nullptr)
            {
                float SmallestRotation = math::M_PI;
                for (int TopSphereVertexIdx = 0; TopSphereVertexIdx < SphereVertexMesh->NorthPoleConnections.size(); TopSphereVertexIdx++)
                {
                    GlobalVertexDisplacementss.push_back({});

                    GSphereVertex* SphereVertex = SphereVertexMesh->NorthPoleConnections[TopSphereVertexIdx];
                    int LatitudeVertexIdx = 0;

                    while (SphereVertex != nullptr)
                    {
                        math::MVector3 LocalVertexDisplacement = NorthPole.RotatedBy(SphereVertex->RadialCoord);
                        math::MVector3 GlobalVertexDisplacement = SphereCenter + LocalVertexDisplacement;
                            
                        math::MVector3 DisplacementFromPlanetToCamera = PlayerPosition - SphereCenter;
                        math::MQuaternion RotationFromCamDirectionToGlobalVertexDisplacement = math::MQuaternion::RotationFromVectorToVector(DisplacementFromPlanetToCamera, LocalVertexDisplacement);
                        math::MVector3 EulerRotationFromCamDirectionToGlobalVertexDisplacement = math::MQuaternion::ToEuler(RotationFromCamDirectionToGlobalVertexDisplacement);

                        if (EulerRotationFromCamDirectionToGlobalVertexDisplacement.Magnitude() < SmallestRotation)
                        {
                            SmallestRotationLongitudeIdx = TopSphereVertexIdx;
                            SmallestRotationLatitudeIdx = LatitudeVertexIdx;
                            SmallestRotation = EulerRotationFromCamDirectionToGlobalVertexDisplacement.Magnitude();
                        }

                        GlobalVertexDisplacementss[TopSphereVertexIdx].push_back(GlobalVertexDisplacement);
                        
                        SphereVertex = SphereVertex->SouthVertex;
                        LatitudeVertexIdx++;
                    }
                }
            }
            // Project Locations
            //// Project vertices to screen points
            //// Draw line from center to projected points

            math::MVector3 LocalNorthPoleVertexDisplacement = NorthPole;
            math::MVector3 LocalSouthPoleVertexDisplacement = NorthPole * -1;
            math::MVector3 GlobalNorthPoleVertexDisplacement = SphereCenter + LocalNorthPoleVertexDisplacement;// LocalNorthPoleVertexDisplacement.RotatedBy(SphereRotation);
            math::MVector3 GlobalSouthPoleVertexDisplacement = SphereCenter + LocalSouthPoleVertexDisplacement;// LocalNorthPoleVertexDisplacement.RotatedBy(SphereRotation);

            GlobalNorthPoleVertexDisplacement.TransformPosition(ViewMatrix);
            GlobalSouthPoleVertexDisplacement.TransformPosition(ViewMatrix);

            GlobalNorthPoleVertexDisplacement.TransformPosition(ProjectionMatrix);
            GlobalSouthPoleVertexDisplacement.TransformPosition(ProjectionMatrix);

            // Perspective divide (if using a perspective projection)
            if (GlobalNorthPoleVertexDisplacement.Z != 0) // Avoid division by zero
            {
                GlobalNorthPoleVertexDisplacement.X /= GlobalNorthPoleVertexDisplacement.Z;
                GlobalNorthPoleVertexDisplacement.Y /= GlobalNorthPoleVertexDisplacement.Z;
            }

            // Perspective divide (if using a perspective projection)
            if (GlobalSouthPoleVertexDisplacement.Z != 0) // Avoid division by zero
            {
                GlobalSouthPoleVertexDisplacement.X /= GlobalSouthPoleVertexDisplacement.Z;
                GlobalSouthPoleVertexDisplacement.Y /= GlobalSouthPoleVertexDisplacement.Z;
            }

            // Map from NDC to screen coordinates
            float NorthPoleVertexScreenX = (GlobalNorthPoleVertexDisplacement.X + 1) * APP_VIRTUAL_WIDTH * 0.5f;
            float NorthPoleVertexScreenY = (1 - GlobalNorthPoleVertexDisplacement.Y) * APP_VIRTUAL_HEIGHT * 0.5f;

            // Map from NDC to screen coordinates
            float SouthPoleVertexScreenX = (GlobalSouthPoleVertexDisplacement.X + 1) * APP_VIRTUAL_WIDTH * 0.5f;
            float SouthPoleVertexScreenY = (1 - GlobalSouthPoleVertexDisplacement.Y) * APP_VIRTUAL_HEIGHT * 0.5f;

            math::MVector3 SphereCenterRenderPosition = SphereCenter;
            // Transform to view space
            SphereCenterRenderPosition.TransformPosition(ViewMatrix);

            // Transform to clip space
            SphereCenterRenderPosition.TransformPosition(ProjectionMatrix);

            // Perspective divide (if using a perspective projection)
            if (SphereCenterRenderPosition.Z != 0) // Avoid division by zero
            {
                SphereCenterRenderPosition.X /= SphereCenterRenderPosition.Z;
                SphereCenterRenderPosition.Y /= SphereCenterRenderPosition.Z;
            }
            // Calculate scale factor based on depth
            float ScaleFactor = 25 * SphereShapeComp->GetRadius() / SphereCenterRenderPosition.Z; // Adjust this formula as needed

            // Map from NDC to screen coordinates
            float ScreenX = (SphereCenterRenderPosition.X + 1) * APP_VIRTUAL_WIDTH * 0.5f;
            float ScreenY = (1 - SphereCenterRenderPosition.Y) * APP_VIRTUAL_HEIGHT * 0.5f;

            // Adjust the size of the sphere for drawing
            float SphereSize = ScaleFactor; // BaseSphereSize is the size of the sphere at depth 1

            // Draw the cross mark
            DrawXAtPosition(ScreenX, ScreenY);
            DrawCircle(ScreenX, ScreenY, SphereSize, 20, ShapeComp->GetShapeColor().X, ShapeComp->GetShapeColor().Y, ShapeComp->GetShapeColor().Z);

            // Project Locations
            //// Project vertices to screen points
            //// Draw line from center to projected points
            App::DrawLine(ScreenX, ScreenY, NorthPoleVertexScreenX, NorthPoleVertexScreenY, 1.0f, 0.0f, 0.0f);

            for (int LongitudeGlobalVertexDisplacementIdx = 0; LongitudeGlobalVertexDisplacementIdx < GlobalVertexDisplacementss.size(); LongitudeGlobalVertexDisplacementIdx++)
            {
                float NorthVertexScreenX = NorthPoleVertexScreenX;
                float NorthVertexScreenY = NorthPoleVertexScreenY;

                for (int GlobalVertexDisplacementIdx = 0; GlobalVertexDisplacementIdx < GlobalVertexDisplacementss[LongitudeGlobalVertexDisplacementIdx].size(); GlobalVertexDisplacementIdx++)
                {
                    math::MVector3 GlobalVertexDisplacement = GlobalVertexDisplacementss[LongitudeGlobalVertexDisplacementIdx][GlobalVertexDisplacementIdx];
                    math::MVector3 GlobalEastVertexDisplacement = GlobalVertexDisplacementss[(LongitudeGlobalVertexDisplacementIdx + 1) % GlobalVertexDisplacementss.size()][GlobalVertexDisplacementIdx];

                    math::MVector3 FacingVector = PlayerPosition - SphereCenter;
                    math::MVector3 VertexVector = GlobalVertexDisplacement - SphereCenter;

                    math::MVector3 Rotation = math::MQuaternion::ToEuler(math::MQuaternion::RotationFromVectorToVector(FacingVector, VertexVector));
                    float RotationTotal = std::abs(Rotation.X) + std::abs(Rotation.Y) + std::abs(Rotation.Z);

                    bool bIsVisible = false;
                    if (RotationTotal < 1.5f)
                    {
                        bIsVisible = true;
                    }

                    GlobalVertexDisplacement.TransformPosition(ViewMatrix);
                    GlobalEastVertexDisplacement.TransformPosition(ViewMatrix);
                    GlobalVertexDisplacement.TransformPosition(ProjectionMatrix);
                    GlobalEastVertexDisplacement.TransformPosition(ProjectionMatrix);

                    // Perspective divide (if using a perspective projection)
                    if (GlobalVertexDisplacement.Z != 0) // Avoid division by zero
                    {
                        GlobalVertexDisplacement.X /= GlobalVertexDisplacement.Z;
                        GlobalVertexDisplacement.Y /= GlobalVertexDisplacement.Z;
                    }

                    // Perspective divide (if using a perspective projection)
                    if (GlobalEastVertexDisplacement.Z != 0) // Avoid division by zero
                    {
                        GlobalEastVertexDisplacement.X /= GlobalEastVertexDisplacement.Z;
                        GlobalEastVertexDisplacement.Y /= GlobalEastVertexDisplacement.Z;
                    }

                    // Map from NDC to screen coordinates
                    float VertexScreenX = (GlobalVertexDisplacement.X + 1) * APP_VIRTUAL_WIDTH * 0.5f;
                    float VertexScreenY = (1 - GlobalVertexDisplacement.Y) * APP_VIRTUAL_HEIGHT * 0.5f;

                    // Map from NDC to screen coordinates
                    float EastVertexScreenX = (GlobalEastVertexDisplacement.X + 1) * APP_VIRTUAL_WIDTH * 0.5f;
                    float EastVertexScreenY = (1 - GlobalEastVertexDisplacement.Y) * APP_VIRTUAL_HEIGHT * 0.5f;

                    if (true)
                    {
                        if (bIsVisible)
                        {
                            App::DrawLine(VertexScreenX, VertexScreenY, NorthVertexScreenX, NorthVertexScreenY, 1.0f, 0.0f, 1.0f);
                            App::DrawLine(VertexScreenX, VertexScreenY, EastVertexScreenX, EastVertexScreenY, 1.0f, 0.0f, 1.0f);
                        }
                    }
                    else
                    {
                        if (SmallestRotationLongitudeIdx == LongitudeGlobalVertexDisplacementIdx
                            &&
                            SmallestRotationLatitudeIdx == GlobalVertexDisplacementIdx)
                        {
                            App::DrawLine(VertexScreenX, VertexScreenY, NorthVertexScreenX, NorthVertexScreenY, 1.0f, 0.0f, 0.0f);
                            App::DrawLine(VertexScreenX, VertexScreenY, EastVertexScreenX, EastVertexScreenY, 1.0f, 0.0f, 0.0f);
                        }
                        else
                        {
                            App::DrawLine(VertexScreenX, VertexScreenY, NorthVertexScreenX, NorthVertexScreenY, 0.0f, 1.0f, 1.0f);
                            App::DrawLine(VertexScreenX, VertexScreenY, EastVertexScreenX, EastVertexScreenY, 0, 1.0f, 1.0f);
                        }
                    }

                    NorthVertexScreenX = VertexScreenX;
                    NorthVertexScreenY = VertexScreenY;
                }

                App::DrawLine(NorthVertexScreenX, NorthVertexScreenY, SouthPoleVertexScreenX, SouthPoleVertexScreenY, 0, 1.0f, 1.0f);
            }
        }
    } 
    math::MMatrix4x4 GRenderManagerComp::ProjectionMatrix1()
    {
        // Parameters for the perspective projection
        float FOV = 100.0f; // Field of View, in degrees
        float AspectRatio = static_cast<float>(APP_VIRTUAL_WIDTH) / APP_VIRTUAL_HEIGHT; // Aspect ratio of the viewport
        float NearPlane = 0.1f; // Near clipping plane
        float FarPlane = 1000.0f; // Far clipping plane

        // Compute the perspective projection matrix
        return math::MMatrix4x4::CreatePerspectiveProjectionMatrix(FOV, AspectRatio, NearPlane, FarPlane);
    }
    math::MMatrix4x4 GRenderManagerComp::ProjectionMatrix2()
    {
        // Define orthographic projection parameters
        float left = -20.0f;
        float right = 20.0f;
        float bottom = -20.0f * APP_VIRTUAL_HEIGHT / APP_VIRTUAL_WIDTH;
        float top = 20.0f * APP_VIRTUAL_HEIGHT / APP_VIRTUAL_WIDTH;
        float nearPlane = 0.1f;
        float farPlane = 1000.0f;

        // Compute the orthographic projection matrix
        return math::MMatrix4x4::CreateOrthographicProjectionMatrix(left, right, bottom, top, nearPlane, farPlane);
    }

	void GRenderManagerComp::DrawXAtPosition(float X, float Y)
	{
		// Adjust these values as necessary for the size of the 'X'
		float size = 10.0f;
		App::DrawLine(X - size, Y - size, X + size, Y + size, 1, 0.5, 1); // Diagonal 1
		App::DrawLine(X - size, Y + size, X + size, Y - size, 1, 0.5, 1); // Diagonal 2
	}
    void GRenderManagerComp::DrawCircle(float CenterX, float CenterY, float Radius, int Edges, float r, float g, float b )
    {
        // Ensure that the number of edges is not too low
        if (Edges < 3) Edges = 3;

        // Angle between each line segment in radians
        float angleStep = 2 * math::M_PI / Edges;

        // Store the first point
        float StartX = CenterX + Radius * cos(0);
        float StartY = CenterY + Radius * sin(0);
        float PrevX = StartX;
        float PrevY = StartY;

        // Draw the circle in segments
        for (int i = 1; i <= Edges; ++i)
        {
            // Calculate the x and y coordinates of the end point
            float EndX = CenterX + Radius * cos(i * angleStep);
            float EndY = CenterY + Radius * sin(i * angleStep);

            // Draw a line from the previous endpoint to the new endpoint
            App::DrawLine(PrevX, PrevY, EndX, EndY, r, g, b);

            // Update the previous endpoint
            PrevX = EndX;
            PrevY = EndY;
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
