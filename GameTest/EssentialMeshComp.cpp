#include "stdafx.h"

namespace ge
{

    void GEssentialMeshComp::RenderSceneData()
    {
        GSceneComp::RenderSceneData();

        switch (Type)
        {
        case EEssentialShapeType::Sphere: 
        {
            glRotatef(90, 1, 0, 0);
            bIsSolid ? glutSolidSphere(1.0, 40, 20) : glutWireSphere(1.0, 20, 10);
            break;
        }
        case EEssentialShapeType::SphereLP:
        {
            glRotatef(90, 1, 0, 0);
            bIsSolid ? glutSolidSphere(1.0, 12, 4) : glutWireSphere(1.0, 12, 8);
            CheckPlanet();

            break;
        }
        case EEssentialShapeType::SpherePlanet:
        {
            CheckPlanet();
            break;
        }
        case EEssentialShapeType::Cube: bIsSolid ? glutSolidCube(1.0) : glutWireCube(1.0); break;
        case EEssentialShapeType::Cone: bIsSolid ? glutSolidCone(1.0, 2.0, 40, 20) : glutWireCone(1.0, 2.0, 20, 5); break;
        case EEssentialShapeType::Torus: bIsSolid ? glutSolidTorus(0.5, 1.0, 40, 20) : glutWireTorus(0.5, 1.0, 20, 20); break;
        case EEssentialShapeType::Dodecahedron: bIsSolid ? glutSolidDodecahedron() : glutWireDodecahedron(); break;
        case EEssentialShapeType::Octahedron: bIsSolid ? glutSolidOctahedron() : glutWireOctahedron(); break;
        case EEssentialShapeType::Tetrahedron: bIsSolid ? glutSolidTetrahedron() : glutWireTetrahedron(); break;
        case EEssentialShapeType::Icosahedron: bIsSolid ? glutSolidIcosahedron() : glutWireIcosahedron(); break;
        case EEssentialShapeType::Teapot: bIsSolid ? glutSolidTeapot(1.0) : glutWireTeapot(1.0);  break;
        default: bIsSolid ? glutSolidCube(1.0) : glutWireCube(1.0);
        }
    }

    void GEssentialMeshComp::SetEssentialShapeType(EEssentialShapeType Type, bool bIsSolid)
    {
        this->Type = Type;

        this->bIsSolid = bIsSolid;

        BuildMesh();
    }

    GSphereVertexMesh* GEssentialMeshComp::GetSphereVertexMesh()
    {
        return SphereVertexMesh;
    }

    void GEssentialMeshComp::BuildMesh()
    {
        switch (Type)
        {
        case EEssentialShapeType::SphereLP:
        case EEssentialShapeType::SpherePlanet:
        {
            SphereVertexMesh = GAMEWORLD->NewObject<GSphereVertexMesh>("SphereVertexMesh");
            SphereVertexMesh->NorthPoleVertex = GAMEWORLD->NewObject<GSphereVertex>("NorthPoleVertex");
            SphereVertexMesh->SouthPoleVertex = GAMEWORLD->NewObject<GSphereVertex>("SouthPoleVertex");

            SphereVertexMesh->NorthPoleDisplacement = math::MVector3::UpVector();
            SphereVertexMesh->NorthPoleVertex->RadialCoord = math::MQuaternion::Identity();
            SphereVertexMesh->SouthPoleVertex->RadialCoord = math::MQuaternion::RotationFromVectorToVector(math::MVector3::UpVector(), math::MVector3::DownVector());

            int LongitudeSliceCount = 20;
            math::MQuaternion LongitudeSliceDisplacement = math::MQuaternion::FromEuler(math::MVector3(0, 2 * math::M_PI / LongitudeSliceCount, 0));
            int LatitudeSliceCount = 20;
            math::MQuaternion LatitudeSliceDisplacement = math::MQuaternion::FromEuler(math::MVector3(math::M_PI / LatitudeSliceCount, 0, 0));

            math::MQuaternion LongitudeCoord = math::MQuaternion::Identity();
            for (int LongitudeSliceIdx = 0; LongitudeSliceIdx < LongitudeSliceCount; LongitudeSliceIdx++)
            {
                math::MQuaternion RadialCoord = LongitudeCoord;

                // North Connecting Vertex
                GSphereVertex* NorthVertex = SphereVertexMesh->NorthPoleVertex;
                GSphereVertex* SphereVertex = GAMEWORLD->NewObject<GSphereVertex>("SphereVertex");

                SphereVertex->NorthVertex = NorthVertex;

                RadialCoord = RadialCoord * LatitudeSliceDisplacement;
                SphereVertex->RadialCoord = RadialCoord;
                SphereVertexMesh->NorthPoleConnections.push_back(SphereVertex);

                // Middle Connecting Vertex
                for (int LongitudeSliceIdx = 1; LongitudeSliceIdx < LongitudeSliceCount - 1; LongitudeSliceIdx++)
                {
                    NorthVertex = SphereVertex;
                    SphereVertex = GAMEWORLD->NewObject<GSphereVertex>("SphereVertex");
                    
                    NorthVertex->SouthVertex = SphereVertex;
                    SphereVertex->NorthVertex = NorthVertex;

                    RadialCoord = RadialCoord * LatitudeSliceDisplacement;
                    SphereVertex->RadialCoord = RadialCoord;
                }

                SphereVertex->SouthVertex = SphereVertexMesh->SouthPoleVertex;

                // Set new LongitudeCoord for next iteration
                LongitudeCoord = LongitudeCoord * LongitudeSliceDisplacement;
            }

            for (int SphereVertexIdx = 0; SphereVertexIdx < SphereVertexMesh->NorthPoleConnections.size(); SphereVertexIdx ++)
            {
                int SphereVertexEastIdx = (SphereVertexIdx + 1) % SphereVertexMesh->NorthPoleConnections.size();

                GSphereVertex* SphereVertex = SphereVertexMesh->NorthPoleConnections[SphereVertexIdx];;
                GSphereVertex* SphereVertexEast = SphereVertexMesh->NorthPoleConnections[SphereVertexEastIdx];
                
                while (SphereVertex->SouthVertex != nullptr)
                {
                    SphereVertex->EastVertex = SphereVertexEast;
                    SphereVertexEast->WestVertex = SphereVertex;

                    SphereVertex = SphereVertex->SouthVertex;
                    SphereVertexEast = SphereVertexEast->SouthVertex;
                }
            }


            CheckPlanet();
            break;
        }
        }

    }

    void GEssentialMeshComp::CheckPlanet()
    {
        if (SphereVertexMesh == nullptr)
        {
            debug::Output(debug::EOutputType::Render, "SphereVertexMesh is null");
        }
        else
        {
            int LongituteSlice = 0;
            for (GSphereVertex* TopSphereVertex : SphereVertexMesh->NorthPoleConnections)
            {
                int LatitudeSlice = 0;
                GSphereVertex* SphereVertex = TopSphereVertex;
                while (SphereVertex->SouthVertex != nullptr)
                {
                    LatitudeSlice++;
                    math::MVector3 EulerCoord = math::MQuaternion::ToEuler(SphereVertex->RadialCoord);
                    //debug::Output(debug::EOutputType::Render, "LongituteSlice_%d, LatitudeSlice_%d: (%.2f, %.2f, %.2f)", LongituteSlice, LatitudeSlice, EulerCoord.X, EulerCoord.Y, EulerCoord.Z);
                    SphereVertex = SphereVertex->SouthVertex;
                }
                LongituteSlice++;
            }
        }
    }
    void GEssentialMeshComp::RenderPlanet()
    {
        float CenterX = 400;
        float CenterY = 400;
        int EdgeCount = 40;
        float Radius = SphereVertexMesh->NorthPoleDisplacement.Magnitude();

        if (SphereVertexMesh == nullptr)
        {
            debug::Output(debug::EOutputType::Render, "SphereVertexMesh is null");
        }
        else
        {
            int LongituteSlice = 0;
            for (GSphereVertex* TopSphereVertex : SphereVertexMesh->NorthPoleConnections)
            {
                int LatitudeSlice = 0;
                GSphereVertex* SphereVertex = TopSphereVertex;
                while (SphereVertex->SouthVertex != nullptr)
                {
                    LatitudeSlice++;
                    math::MVector3 EulerCoord = math::MQuaternion::ToEuler(SphereVertex->RadialCoord);
                    //debug::Output(debug::EOutputType::Render, "LongituteSlice_%d, LatitudeSlice_%d: (%.2f, %.2f, %.2f)", LongituteSlice, LatitudeSlice, EulerCoord.X, EulerCoord.Y, EulerCoord.Z);
                    SphereVertex = SphereVertex->SouthVertex;
//                    App::DrawLine(CenterX, CenterY, CenterX + X, CenterY + Y, 1, 0.2f, 1);

                }
                LongituteSlice++;

                break;
            }
        }
        



        //// Init Theta, X, Y
        //float Theta = math::MQuaternion::ToEuler(PlanetRotation).X; //math::M_PI
        //float XRadius = Radius * ((2.0f / math::M_PI) * math::MQuaternion::ToEuler(PlanetRotation).Y);
        //float YRadius = Radius * ((2.0f / math::M_PI) * math::MQuaternion::ToEuler(PlanetRotation).X);
        //float X = XRadius * sin(Theta);
        //float Y = Radius * cos(Theta);


    }
}
