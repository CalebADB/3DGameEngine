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
    }

}
