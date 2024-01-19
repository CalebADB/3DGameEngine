#include "stdafx.h"

namespace ge
{
    namespace math
    {
        MVector3 MVector3::operator+(const MVector3& V2) const
        {
            return MVector3(X + V2.X, Y + V2.Y, Z + V2.Z);
        }
        MVector3 MVector3::operator*(const GLfloat& F) const
        {
            return MVector3(X * F, Y * F, Z * F);
        }

        MQuaternion MQuaternion::Normalized() const
        {
            GLfloat Len = sqrt(W * W + X * X + Y * Y + Z * Z);
            return MQuaternion(W / Len, X / Len, Y / Len, Z / Len);
        }
        MQuaternion MQuaternion::operator*(const MQuaternion& Q) const
        {
            return MQuaternion(
                W * Q.W - X * Q.X - Y * Q.Y - Z * Q.Z,
                W * Q.X + X * Q.W + Y * Q.Z - Z * Q.Y,
                W * Q.Y - X * Q.Z + Y * Q.W + Z * Q.X,
                W * Q.Z + X * Q.Y - Y * Q.X + Z * Q.W
            ).Normalized();
        }
        MMatrix4x4 MQuaternion::ToMatrix() const
        {
            MMatrix4x4 Matrix;

            Matrix.m[0][0] = 1 - 2 * Y * Y - 2 * Z * Z;
            Matrix.m[0][1] = 2 * X * Y - 2 * Z * W;
            Matrix.m[0][2] = 2 * X * Z + 2 * Y * W;
            Matrix.m[0][3] = 0;

            Matrix.m[1][0] = 2 * X * Y + 2 * Z * W;
            Matrix.m[1][1] = 1 - 2 * X * X - 2 * Z * Z;
            Matrix.m[1][2] = 2 * Y * Z - 2 * X * W;
            Matrix.m[1][3] = 0;

            Matrix.m[2][0] = 2 * X * Z - 2 * Y * W;
            Matrix.m[2][1] = 2 * Y * Z + 2 * X * W;
            Matrix.m[2][2] = 1 - 2 * X * X - 2 * Y * Y;
            Matrix.m[2][3] = 0;

            Matrix.m[3][0] = 0;
            Matrix.m[3][1] = 0;
            Matrix.m[3][2] = 0;
            Matrix.m[3][3] = 1;

            return Matrix;
        }

        void MTransformData::Translate(MVector3 Displacement)
        {
            Scale = Scale + Displacement;
        }
        void MTransformData::Rotate(MQuaternion Displacement)
        {
            Rotation = Rotation * Displacement;
        }
        void MTransformData::Stretch(MVector3 Displacement)
        {
            Scale.X *= Displacement.X;
            Scale.Y *= Displacement.Y;
            Scale.Z *= Displacement.Z;
        }
        void MTransformData::StretchUniform(GLfloat Displacement)
        {
            Scale = Scale * Displacement;
        }
    }
};
