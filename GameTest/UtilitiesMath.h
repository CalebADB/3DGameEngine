#ifndef _UTILITIESMATH_H
#define _UTILITIESMATH_H

namespace ge
{
    namespace math
    {
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

            MVector3 operator+(const MVector3& V2) const;
            MVector3 operator-(const MVector3& V2) const;
            MVector3 operator*(const GLfloat& F) const;
            MVector3 operator/(const GLfloat& F) const;
            

            GLfloat Magnitude() const;
            void Normalize();
            MVector3  Normalized() const;
            MVector3 RotatedBy(const MQuaternion& Q) const;
        };

        class MMatrix4x4 
        {
        public:
            GLfloat m[4][4] = { {0} };

            const float* Data() const { return &m[0][0]; }
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

            static MQuaternion FromAxisAngle(const MVector3& Axis, GLfloat Angle) 
            {
                GLfloat HalfAngle = Angle / 2;
                GLfloat s = sin(HalfAngle);
                return MQuaternion(cos(HalfAngle), Axis.X * s, Axis.Y * s, Axis.Z * s);
            }

            MQuaternion Normalized() const;

            MQuaternion operator*(const MQuaternion& Q) const;

            MQuaternion Conjugate() const;

            MQuaternion Inverse() const;

            MMatrix4x4 ToMatrix() const;

        };

        class MTransformData 
        {
        public:
            MVector3 Position;
            MQuaternion Rotation;
            MVector3 Scale;

            MTransformData() 
                : 
                MTransformData(MTransformData::Identity())
            {};
            MTransformData(MVector3 Position, MQuaternion Rotation, MVector3 Scale)
                :
                Position(Position), Rotation(Rotation), Scale(Scale)
            {};

            static MTransformData Identity() { return MTransformData(MVector3(0.0, 0.0, 0.0), MQuaternion::Identity(), MVector3(1.0, 1.0, 1.0)); }

            void Translate(MVector3 Displacement);
            void Rotate(MQuaternion Displacement);
            void Stretch(MVector3 Displacement);
            void StretchUniform(GLfloat Displacement);
        };
    }
};

#endif //_UTILITIESMATH_H
