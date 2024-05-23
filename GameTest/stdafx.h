// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include "glew.h"

// TODO: reference additional headers your program requires here
#include "App/App.h"
#include "App/AppSettings.h"

#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <type_traits>
#include <fstream>
#include <sstream>
#include <memory>
#include <typeinfo>

#include <GL/gl.h>
#include <GL/glu.h>
#include "../glut/include/GL/freeglut.h"
#include "glTape.h" // I MADE THIS BECAUSE IT DOESNT WORK AS WELL AS GLEW BUT IT GETS THE JOB DONE (DO YOU GET IT (GLUE vs TAPE))
#include "glsl.h"

#include "UtilitiesDebug.h"
#include "UtilitiesMath.h"
#include "UtilitiesGameGlobals.h"

#include "Object.h"

#include "Comp.h"

#include "SceneComp.h"
#include "MeshComp.h"
#include "EssentialMeshComp.h"
#include "ShapeComp.h"
#include "GravityWellComp.h"
#include "PhysicalComp.h"
#include "PlanetNavigationComp.h"
#include "PlayerControllerComp.h"
#include "PlayerPlanetNavigationComp.h"
#include "OrbitComp.h"
#include "CameraComp.h"

#include "Manager.h"
#include "Octree.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
//#include "MemoryManager.h"

#include "Actor.h"
#include "Planet.h"
#include "PressureWave.h"
#include "Projectile.h"
#include "Prop.h"
#include "Player.h"

#include "SpherePlanet.h"
#include "TimeContainerProp.h"

#include "EssentialShape.h"
#include "OrbitingBody.h"

#include "World.h"
