#ifndef _GCAMERACOMP_H
#define _GCAMERACOMP_H

namespace ge
{
	class GCameraComp : public GSceneComp
	{
	private:
		GEssentialMeshComp* EssentialMeshComp = nullptr;
		math::MVector3 CameraUp = math::MVector3::UpVector();

		float Sensitivity = 0.25;

		GLfloat CameraPitch = math::M_DEG90;
		GLfloat CameraYaw = 0;
		math::MQuaternion CameraOrientation = math::MQuaternion::Identity();

		POINT lastMousePos; // Struct to store the last mouse position
		bool bIsMouseCaptured = false;


	public:
		GCameraComp(const std::string& Name) 
			: 
			GSceneComp(Name)
		{};

		virtual void Begin();
	
	protected:
		virtual void Update(float deltaTime);

	public:
		math::MQuaternion GetCameraOrientation() const { return CameraOrientation; }
	private:
		void CaptureMouse();
		void ReleaseMouse();
		math::MQuaternion CalcCameraOrientation(GLfloat deltaTime, GLfloat MouseDeltaX, GLfloat MouseDeltaY, GLfloat Sensitivity);
		void GetMouseDelta(float& MouseDeltaX, float& MouseDeltaY);

	};
};

#endif //_GCAMERACOMP_H