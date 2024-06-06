#include "stdafx.h"

namespace ge
{
	void GGravityWellComp::Begin()
	{
		GSceneComp::Begin(); 
		
		GAMEWORLD->PhysicsManagerComp->AddGravityWellComp(this);
	}
	void GGravityWellComp::Initialize(GLfloat Strength)
	{
		this->Strength = Strength;
	}

	void GGravityWellComp::Update(float deltaTime)
	{
		GSceneComp::Update(deltaTime);
	}

	void GGravityWellComp::Destroy()
	{
		GAMEWORLD->PhysicsManagerComp->RemoveGravityWellComp(this);

		GSceneComp::Destroy();
	}

	void GSphereGravityWellComp::Begin()
	{
		GGravityWellComp::Begin();

		Type = EGravityWellType::Sphere;

		SphereShapeComp = GAMEWORLD->NewComp<GSphereShapeComp>(std::string("SphereGravityWellShapeComp"));
		AttachComp(this, SphereShapeComp);
	}
	void GSphereGravityWellComp::Initialize(GLfloat Strength, GLfloat GravityReachRadius, math::MVector3 Color)
	{
		GGravityWellComp::Initialize(Strength);

		SphereShapeComp->Initialize(GravityReachRadius, false, Color);
	}
	void GSphereGravityWellComp::RenderSceneData()
	{
		GLfloat RadiusMin = 5;
		GLfloat RadiusDiff = 1;
		GLfloat LayerRadius = 2;

		int SliceCount = 5;
		int RowCount = 5;
		int LayerCount = 2;

		GLfloat CurEulerSliceAngle;
		GLfloat CurEulerRowAngle;

		// Rotating through the longitude lines
		for (int Slice = 0; Slice <= SliceCount; Slice++)
		{
			CurEulerSliceAngle = (GLfloat)Slice * (math::M_DEG360 / SliceCount); // Angle for each slice

			// Convert angle to quaternion and then to matrix
			math::MQuaternion SliceRotation = math::MQuaternion::FromAxisAngle(ge::math::MVector3::UpVector(), CurEulerSliceAngle);
			math::MMatrix4x4 SliceMatrix = math::MQuaternion::ToMatrix(SliceRotation);

			glPushMatrix();
			glMultMatrixf(SliceMatrix.Data());

			// Rotating through the latitude lines
			for (int Row = 0; Row < RowCount; Row++)
			{
				if (Slice != 0 && (Row == 0 || Row == RowCount - 1))
				{
					continue;
				}
				CurEulerRowAngle = (GLfloat)Row * (math::M_DEG180 / (RowCount - 1)) - math::M_DEG90; // Angle for each row

				// Convert angle to quaternion and then to matrix
				math::MQuaternion RowRotation = math::MQuaternion::FromAxisAngle(ge::math::MVector3(1,0,0), CurEulerRowAngle);
				math::MMatrix4x4 RowMatrix = math::MQuaternion::ToMatrix(RowRotation);

				glPushMatrix();
				glMultMatrixf(RowMatrix.Data());
				for (int Layer = 0; Layer < LayerCount; Layer++)
				{
					glPushMatrix();
					GLfloat Radius = RadiusMin + (GAMEWORLD->timer010 * RadiusDiff) + (Layer * LayerRadius);
					glTranslatef(0.0f, 0.0f, Radius); // Translate along Z-axis by radius amount
					glPushMatrix();
					glMultMatrixf(math::MQuaternion::FlipMatrix4x4().Data());
					glutSolidCone(0.5, 0.5, 10, 2);
					glPushMatrix();
					glTranslatef(0.0f, 0.0f, -0.5);
					glutWireCylinder(0.1, 0.5, 10, 1);
					glPopMatrix();
					glPopMatrix();
					glPopMatrix();
				}
				glPopMatrix();
			}
			glPopMatrix();
		}


	}
	math::MVector3 GSphereGravityWellComp::GetGravityAtPosition(math::MVector3 GlobalPosition)
	{
		GLfloat SignedDistance = SphereShapeComp->GetSignedDistanceFrom(GlobalPosition);
		if (SignedDistance > 0) return math::MVector3::ZeroVector();
		//debug::Output(debug::EOutputType::Physics, "Physics: GravityWell_%s has sign distance %.3f Pos_(%.3f, %.3f, %.3f)", GetCharName(), (float)SignedDistance, GlobalPosition.X, GlobalPosition.Y, GlobalPosition.Z);
		return (GetGlobalTransformData().Position - GlobalPosition).Normalized() * Strength;
	}
};
