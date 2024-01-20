#include "stdafx.h"

namespace ge
{
    namespace math
    {
        MVector3 MVector3::operator+(const MVector3& V2) const
        {
            return MVector3(X + V2.X, Y + V2.Y, Z + V2.Z);
        }
        MVector3 MVector3::operator-(const MVector3& V2) const
        {
            return MVector3(X - V2.X, Y - V2.Y, Z - V2.Z);
        }
        MVector3 MVector3::operator*(const GLfloat& F) const
        {
            return MVector3(X * F, Y * F, Z * F);
        }
        MVector3 MVector3::operator/(const GLfloat& F) const
        {
            return MVector3(X / F, Y / F, Z / F);
        }
        GLfloat MVector3::Magnitude() const
        {
            return sqrt(X * X + Y * Y + Z * Z);
        }
        void MVector3::Normalize()
        {
            GLfloat M = Magnitude();
            X /= M;
            Y /= M;
            Z /= M;
        }
        MVector3 MVector3::Normalized() const
        {
            return MVector3(X, Y, Z) / Magnitude();
        }
        MVector3 MVector3::RotatedBy(const MQuaternion& Q) const
        {
            MQuaternion vecAsQ(0, X, Y, Z);
            MQuaternion resQ = Q * vecAsQ * Q.Conjugate();
            return MVector3(resQ.X, resQ.Y, resQ.Z) * Magnitude();
        }

        MQuaternion MQuaternion::Normalized() const
        {
            GLfloat Len = sqrt(W * W + X * X + Y * Y + Z * Z);
            return MQuaternion(W / Len, X / Len, Y / Len, Z / Len);
        }
        MQuaternion MQuaternion::operator*(const MQuaternion& Q2) const
        {
            return MQuaternion(
                W * Q2.W - X * Q2.X - Y * Q2.Y - Z * Q2.Z,
                W * Q2.X + X * Q2.W + Y * Q2.Z - Z * Q2.Y,
                W * Q2.Y - X * Q2.Z + Y * Q2.W + Z * Q2.X,
                W * Q2.Z + X * Q2.Y - Y * Q2.X + Z * Q2.W
            ).Normalized();
        }
        MQuaternion MQuaternion::Conjugate() const
        {
            return MQuaternion(W, -X, -Y, -Z);
        }
        MQuaternion MQuaternion::Inverse() const
        {
            GLfloat norm = W * W + X * X + Y * Y + Z * Z;
            if (norm > 0.0)
            {
                GLfloat invNorm = 1.0 / norm;
                return MQuaternion(W * invNorm, -X * invNorm, -Y * invNorm, -Z * invNorm);
            }
            return MQuaternion(0, 0, 0, 0); // Return zero quaternion if norm is zero
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

        MTransformData MTransformData::TransformedBy(MTransformData TransformData)
        {
            return MTransformData(
                Position + TransformData.Position, 
                Rotation * TransformData.Rotation, 
                MVector3(Scale.X * TransformData.Scale.X, Scale.Y * TransformData.Scale.Y, Scale.Z * TransformData.Scale.Z)
            );
        }
        void MTransformData::Translate(MVector3 Displacement)
        {
            Position = Position + Displacement;
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
