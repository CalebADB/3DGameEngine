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
        MVector3 MVector3::Cross(const MVector3& V2) const
        {
            return MVector3(
                Y * V2.Z - Z * V2.Y,
                Z * V2.X - X * V2.Z,
                X * V2.Y - Y * V2.X
            );
        }
        void MVector3::TransformPosition(const MMatrix4x4& Matrix)
        {
            // Calculate the transformed position without the perspective divide
            float newX = X * Matrix.m[0][0] + Y * Matrix.m[1][0] + Z * Matrix.m[2][0] + Matrix.m[3][0];
            float newY = X * Matrix.m[0][1] + Y * Matrix.m[1][1] + Z * Matrix.m[2][1] + Matrix.m[3][1];
            float newZ = X * Matrix.m[0][2] + Y * Matrix.m[1][2] + Z * Matrix.m[2][2] + Matrix.m[3][2];
            float newW = X * Matrix.m[0][3] + Y * Matrix.m[1][3] + Z * Matrix.m[2][3] + Matrix.m[3][3];

            // Perspective divide (if w is not 0 or very close to 0)
            if (std::abs(newW) > std::numeric_limits<float>::epsilon())
            {
                newX /= newW;
                newY /= newW;
                newZ /= newW;
            }

            // Updating the vector's components
            X = newX;
            Y = newY;
            Z = newZ;
        }
        MMatrix4x4 MMatrix4x4::CreateViewMatrix(const MVector3& camPosition, const MVector3& targetPosition, const MVector3& upVector)
        {
            // Calculate the forward direction (normalized)
            MVector3 forward = (targetPosition - camPosition).Normalized();

            // Calculate the right vector (normalized)
            MVector3 right = forward.Cross(upVector).Normalized();

            // Recalculate the up vector (normalized)
            MVector3 up = right.Cross(forward);

            // Constructing the view matrix
            MMatrix4x4 viewMatrix;

            viewMatrix.m[0][0] = right.X;
            viewMatrix.m[1][0] = right.Y;
            viewMatrix.m[2][0] = right.Z;
            viewMatrix.m[3][0] = -MVector3::CalcDotProduct(right, camPosition);

            viewMatrix.m[0][1] = up.X;
            viewMatrix.m[1][1] = up.Y;
            viewMatrix.m[2][1] = up.Z;
            viewMatrix.m[3][1] = -MVector3::CalcDotProduct(up, camPosition);

            viewMatrix.m[0][2] = -forward.X;
            viewMatrix.m[1][2] = -forward.Y;
            viewMatrix.m[2][2] = -forward.Z;
            viewMatrix.m[3][2] = MVector3::CalcDotProduct(forward, camPosition);

            viewMatrix.m[0][3] = 0;
            viewMatrix.m[1][3] = 0;
            viewMatrix.m[2][3] = 0;
            viewMatrix.m[3][3] = 1;

            return viewMatrix;
        }
        MMatrix4x4 MMatrix4x4::CreatePerspectiveProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane)
        {
            MMatrix4x4 matrix;
            float tanHalfFOV = tan(fov / 2.0f * M_DEG_TO_RAD);

            matrix.m[0][0] = 1.0f / (aspectRatio * tanHalfFOV);
            matrix.m[1][1] = 1.0f / tanHalfFOV;
            matrix.m[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
            matrix.m[2][3] = -1.0f;
            matrix.m[3][2] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);

            return matrix;
        }
        MMatrix4x4 MMatrix4x4::operator*(const MMatrix4x4& Other) const
        {
            MMatrix4x4 Result;

            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    Result.m[i][j] = m[i][0] * Other.m[0][j] +
                        m[i][1] * Other.m[1][j] +
                        m[i][2] * Other.m[2][j] +
                        m[i][3] * Other.m[3][j];
                }
            }

            return Result;
        }

        MQuaternion MQuaternion::FromAxisAngle(const MVector3& Axis, GLfloat Angle)
        {
            GLfloat HalfAngle = Angle / 2;
            GLfloat S = sin(HalfAngle);
            return MQuaternion(cos(HalfAngle), Axis.X * S, Axis.Y * S, Axis.Z * S);
        }
        MMatrix4x4 MQuaternion::FlipMatrix4x4()
        {
            MMatrix4x4 Matrix4x4;
            Matrix4x4.m[0][0] = 1;
            Matrix4x4.m[1][1] = -1;
            Matrix4x4.m[2][2] = -1;
            Matrix4x4.m[3][3] = 1;
            return Matrix4x4;
        }
        MMatrix4x4 MQuaternion::ToMatrix(const MQuaternion& Q)
        {
            MMatrix4x4 Matrix;

            Matrix.m[0][0] = 1 - 2 * Q.Y * Q.Y - 2 * Q.Z * Q.Z;
            Matrix.m[0][1] = 2 * Q.X * Q.Y - 2 * Q.Z * Q.W;
            Matrix.m[0][2] = 2 * Q.X * Q.Z + 2 * Q.Y * Q.W;
            Matrix.m[0][3] = 0;

            Matrix.m[1][0] = 2 * Q.X * Q.Y + 2 * Q.Z * Q.W;
            Matrix.m[1][1] = 1 - 2 * Q.X * Q.X - 2 * Q.Z * Q.Z;
            Matrix.m[1][2] = 2 * Q.Y * Q.Z - 2 * Q.X * Q.W;
            Matrix.m[1][3] = 0;

            Matrix.m[2][0] = 2 * Q.X * Q.Z - 2 * Q.Y * Q.W;
            Matrix.m[2][1] = 2 * Q.Y * Q.Z + 2 * Q.X * Q.W;
            Matrix.m[2][2] = 1 - 2 * Q.X * Q.X - 2 * Q.Y * Q.Y;
            Matrix.m[2][3] = 0;

            Matrix.m[3][0] = 0;
            Matrix.m[3][1] = 0;
            Matrix.m[3][2] = 0;
            Matrix.m[3][3] = 1;

            return Matrix;
        }
        MQuaternion MQuaternion::FromMatrix(const MMatrix4x4& Matrix)
        {
            GLfloat TR = Matrix.m[0][0] + Matrix.m[1][1] + Matrix.m[2][2];

            if (TR > 0) {
                GLfloat S = sqrt(TR + 1.0) * 2; // S=4*qw 
                return MQuaternion(
                    0.25 * S,
                    (Matrix.m[2][1] - Matrix.m[1][2]) / S,
                    (Matrix.m[0][2] - Matrix.m[2][0]) / S,
                    (Matrix.m[1][0] - Matrix.m[0][1]) / S
                );
            }
            else if ((Matrix.m[0][0] > Matrix.m[1][1]) & (Matrix.m[0][0] > Matrix.m[2][2])) {
                GLfloat S = sqrt(1.0 + Matrix.m[0][0] - Matrix.m[1][1] - Matrix.m[2][2]) * 2; // S=4*qx 
                return MQuaternion(
                    (Matrix.m[2][1] - Matrix.m[1][2]) / S,
                    0.25 * S,
                    (Matrix.m[0][1] + Matrix.m[1][0]) / S,
                    (Matrix.m[0][2] + Matrix.m[2][0]) / S
                );
            }
            else if (Matrix.m[1][1] > Matrix.m[2][2]) {
                GLfloat S = sqrt(1.0 + Matrix.m[1][1] - Matrix.m[0][0] - Matrix.m[2][2]) * 2; // S=4*qy
                return MQuaternion(
                    (Matrix.m[0][2] - Matrix.m[2][0]) / S,
                    (Matrix.m[0][1] + Matrix.m[1][0]) / S,
                    0.25 * S,
                    (Matrix.m[1][2] + Matrix.m[2][1]) / S
                );
            }
            else {
                GLfloat S = sqrt(1.0 + Matrix.m[2][2] - Matrix.m[0][0] - Matrix.m[1][1]) * 2; // S=4*qz
                return MQuaternion(
                    (Matrix.m[1][0] - Matrix.m[0][1]) / S,
                    (Matrix.m[0][2] + Matrix.m[2][0]) / S,
                    (Matrix.m[1][2] + Matrix.m[2][1]) / S,
                    0.25 * S
                );
            }
        }
        MVector3 MQuaternion::ToEuler(const MQuaternion& Q)
        {
            MVector3 Euler = MVector3::ZeroVector();

            // Roll (x-axis rotation)
            GLfloat sinr_cosp = 2 * (Q.W * Q.X + Q.Y * Q.Z);
            GLfloat cosr_cosp = 1 - 2 * (Q.X * Q.X + Q.Y * Q.Y);
            Euler.X = atan2(sinr_cosp, cosr_cosp);

            // Pitch (y-axis rotation)
            GLfloat sinp = 2 * (Q.W * Q.Y - Q.Z * Q.X);
            if (abs(sinp) >= 1)
                Euler.Y = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
            else
                Euler.Y = asin(sinp);

            // Yaw (z-axis rotation)
            GLfloat siny_cosp = 2 * (Q.W * Q.Z + Q.X * Q.Y);
            GLfloat cosy_cosp = 1 - 2 * (Q.Y * Q.Y + Q.Z * Q.Z);
            Euler.Z = atan2(siny_cosp, cosy_cosp);

            return Euler;
        }
        MQuaternion MQuaternion::FromEuler(const MVector3& Euler)
        {
            GLfloat Roll = Euler.X;
            GLfloat Pitch = Euler.Y;
            GLfloat Yaw = Euler.Z;

            GLfloat CR = cos(Roll * 0.5);
            GLfloat SR = sin(Roll * 0.5);
            GLfloat CP = cos(Pitch * 0.5);
            GLfloat SP = sin(Pitch * 0.5);
            GLfloat CY = cos(Yaw * 0.5);
            GLfloat SY = sin(Yaw * 0.5);

            return MQuaternion(
                CR * CP * CY + SR * SP * SY,
                SR * CP * CY - CR * SP * SY,
                CR * SP * CY + SR * CP * SY,
                CR * CP * SY - SR * SP * CY
            );
        }

        MQuaternion MQuaternion::RotationFromVectorToVector(const MVector3& Vector1, const MVector3& Vector2)
        {
            MVector3 V1 = Vector1.Normalized();
            MVector3 V2 = Vector2.Normalized();

            GLfloat Dot = MVector3::CalcDotProduct(V1, V2);

            // Check if vectors are parallel or opposite
            if (Dot > 0.999999) {
                // Vectors are parallel
                return MQuaternion::Identity();
            }
            else if (Dot < -0.999999) {
                // Vectors are opposite, find orthogonal vector for axis
                MVector3 axis = MVector3::UpVector().Cross(V1);
                if (axis.Magnitude() < 0.000001) // Check if they are collinear
                    axis = MVector3::OneVector().Cross(V1);

                axis.Normalize();
                return MQuaternion::FromAxisAngle(axis, M_DEG180);
            }

            GLfloat S = sqrt((1 + Dot) * 2);
            GLfloat Invs = 1 / S;

            MVector3 C = V1.Cross(V2);

            return MQuaternion(
                S * 0.5f,
                C.X * Invs,
                C.Y * Invs,
                C.Z * Invs
            );
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
