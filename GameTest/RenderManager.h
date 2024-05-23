#ifndef _GRENDERMANAGERCOMP_H
#define _GRENDERMANAGERCOMP_H

namespace ge
{
	class GRenderManagerComp : public GManagerComp
	{
	private:
		std::list<GShapeComp*> ShapeComps;
		GCameraComp* GameCameraComp = nullptr;

		float PulseSpeed = 2;
		float PulseInterval = 2;
		float Pulse1 = 0;


	public:
		GRenderManagerComp(const std::string& Name)
			:
			GManagerComp(Name)
		{}

		virtual void Begin();

	protected:
		virtual void Update(float deltaTime);
	public:
		void AddShapeComp(GShapeComp* ShapeComp);
		void AssignGameCamera(GCameraComp* CameraComp);

		void Render();

	private:
		void DrawXAtPosition(float x, float y);
		void DrawCircle(float centerX, float centerY, float radius, int edges, float r = 1.0f, float g = 1.0f, float b = 1.0f);
		float CalculateCrossSectionRadius(float sphereRadius, float zDepth);

	};
};

#endif //_GRENDERMANAGERCOMP_H