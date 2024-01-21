#ifndef _UTILITIESMATH_H
#define _UTILITIESMATH_H

namespace ge
{
    namespace math
    {
        static GLfloat M_PI = 3.14159265;
        static GLfloat M_DEG360 = M_PI * 2;
        static GLfloat M_DEG180 = M_PI;
        static GLfloat M_DEG90 = M_PI / 2;
        static GLfloat M_DEG45 = M_PI / 4;

        class MQuaternion;


        class MVector3 
        {
        public:
            GLfloat X;
            GLfloat Y;
            GLfloat Z;

            MVector3(GLfloat X, GLfloat Y, GLfloat Z) 
                : 
                X(X), Y(Y), Z(Z) 
            {}

            static MVector3 ZeroVector() { return MVector3(0, 0, 0); }
            static MVector3 OneVector() { return MVector3(1, 1, 1); }
            static MVector3 UpVector() { return MVector3(0, 1, 0); }
            static MVector3 RightVector() { return MVector3(1, 0, 0); }
            static MVector3 ForwardVector() { return MVector3(0, 0, 1); }

            static MVector3 FlipVector(MVector3 V) { return MVector3(-V.X, -V.Y, -V.Z); }
            static GLfloat CalcDotProduct(const MVector3& v1, const MVector3& v2)
            {
                return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
            }
            static bool IsOnSameSideAsNormal(const MVector3& vector, const MVector3& planeNormal) 
            {
                GLfloat dotProduct = CalcDotProduct(vector, planeNormal);
                return dotProduct >= 0;
            }
            static MVector3 ProjectOntoPlane(const MVector3& Vector, const MVector3& PlaneNormal)
            {
                GLfloat DotProduct = CalcDotProduct(Vector, PlaneNormal);
                GLfloat NormalMagnitudeSquared = CalcDotProduct(PlaneNormal, PlaneNormal);
                MVector3 Projection = PlaneNormal * (DotProduct / NormalMagnitudeSquared);
                return Vector - Projection;
            }

            // Helper function to calculate the dot product of two vectors
            MVector3 operator+(const MVector3& V2) const;
            MVector3 operator-(const MVector3& V2) const;
            MVector3 operator*(const GLfloat& F) const;
            MVector3 operator/(const GLfloat& F) const;
            

            GLfloat Magnitude() const;
            void Normalize();
            MVector3 Normalized() const;
            MVector3 RotatedBy(const MQuaternion& Q) const;
            MVector3 Cross(const MVector3& V2) const; 
        };

        class MMatrix4x4 
        {
        public:
            GLfloat m[4][4] = { {0} };

            const float* Data() const { return &m[0][0]; }

            MMatrix4x4 operator*(const MMatrix4x4& other) const;
        };


        class MQuaternion {
        public:
            GLfloat W;
            GLfloat X;
            GLfloat Y;
            GLfloat Z;

            MQuaternion(GLfloat W, GLfloat X, GLfloat Y, GLfloat Z) 
                : 
                W(W), X(X), Y(Y), Z(Z) 
            {}

            static MQuaternion Identity() { return MQuaternion(1, 0, 0, 0); }
            static MQuaternion FromAxisAngle(const MVector3& Axis, GLfloat Angle);
            static MMatrix4x4 FlipMatrix4x4();
            static MMatrix4x4 ToMatrix(const MQuaternion& Q);
            static MQuaternion FromMatrix(const MMatrix4x4& Matrix);
            static MVector3 MQuaternion::ToEuler(const MQuaternion& Q);
            static MQuaternion FromEuler(const MVector3& euler);
            static MQuaternion RotationFromVectorToVector(const MVector3& vector1, const MVector3& vector2);

            MQuaternion Normalized() const;
            MQuaternion operator*(const MQuaternion& Q) const;
            MQuaternion Conjugate() const;
            MQuaternion Inverse() const;
        };

        class MTransformData 
        {
        public:
            MVector3 Position;
            MQuaternion Rotation;
            MVector3 Scale;

            MTransformData(MVector3 Position, MQuaternion Rotation, MVector3 Scale)
                :
                Position(Position), Rotation(Rotation), Scale(Scale)
            {};

            static MTransformData Identity() { return MTransformData(MVector3(0.0, 0.0, 0.0), MQuaternion::Identity(), MVector3(1.0, 1.0, 1.0)); }

            MTransformData TransformedBy(MTransformData TransformData);
            void Translate(MVector3 Displacement);
            void Rotate(MQuaternion Displacement);
            void Stretch(MVector3 Displacement);
            void StretchUniform(GLfloat Displacement);
        };
    }
};

#endif //_UTILITIESMATH_H
