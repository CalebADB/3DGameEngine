#include "stdafx.h"

namespace ge
{
    void GEssentialMeshComp::Update(float deltaTime)
    {

    }
    void GEssentialMeshComp::ApplySceneData()
    {
        GSceneComp::ApplySceneData();
    }

    void GEssentialMeshComp::SetEssentialShapeType(EEssentialShapeType Type, bool bIsWired)
    {
        switch (Type)
        {
        case EEssentialShapeType::Sphere: bIsWired ? glutSolidSphere(1.0, 1.0, 1.0) : glutWireSphere(1.0, 1.0, 1.0); break;
        case EEssentialShapeType::Cube: bIsWired ? glutSolidCube(1.0): glutWireCube(1.0); break;
        case EEssentialShapeType::Cone: bIsWired ? glutSolidCone(1.0, 1.0, 1.0, 1.0): glutWireCone(1.0, 1.0, 1.0, 1.0); break;
        case EEssentialShapeType::Torus: bIsWired ? glutSolidTorus(1.0, 1.0, 1.0, 1.0): glutWireTorus(1.0, 1.0, 1.0, 1.0); break;
        case EEssentialShapeType::Dodecahedron: bIsWired ? glutSolidDodecahedron(): glutWireDodecahedron(); break;
        case EEssentialShapeType::Octahedron: bIsWired ? glutSolidOctahedron(): glutWireOctahedron(); break;
        case EEssentialShapeType::Tetrahedron: bIsWired ? glutSolidTetrahedron(): glutWireTetrahedron(); break;
        case EEssentialShapeType::Icosahedron: bIsWired ? glutSolidIcosahedron(): glutWireIcosahedron(); break;
        case EEssentialShapeType::Teapot: bIsWired ? glutSolidTeapot(1.0) : glutWireTeapot(1.0);  break;
        default: glutSolidCube(1.0);
        }

    }

}
