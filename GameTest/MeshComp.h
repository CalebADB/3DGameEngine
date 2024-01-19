#ifndef _GMESHCOMP_H
#define _GMESHCOMP_H

namespace ge
{
	class GMeshComp : public GSceneComp
	{
	private:

	public:
		GMeshComp(const std::string& Name)
			:
			GSceneComp(Name)
		{};

	protected:
		virtual void Update(float deltaTime);
		virtual void ApplySceneData();

	private:
		bool LoadMeshDataFromFile(const std::string& filename, std::vector<float>& vertices, std::vector<unsigned int>& indices);
		GLuint LoadMesh(const std::vector<float>&vertices, const std::vector<unsigned int>&indices);
		void DrawMesh(GLuint VAO, int indexCount);
	};
};

#endif //_GMESHCOMP_H