#include "stdafx.h"

namespace ge
{
	void GMeshComp::Update(float deltaTime)
	{

	}
	void GMeshComp::RenderSceneData()
	{
		GSceneComp::RenderSceneData();

		// DrawMesh(GLuint VAO, int indexCount);
	}

    bool GMeshComp::LoadMeshDataFromFile(const std::string& filename, std::vector<float>& vertices, std::vector<unsigned int>& indices) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "v") {
                float x, y, z;
                iss >> x >> y >> z;
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
            }
            else if (prefix == "f") {
                unsigned int vertexIndex[3];
                for (int i = 0; i < 3; ++i) {
                    iss >> vertexIndex[i];
                    indices.push_back(vertexIndex[i] - 1); // OBJ indices are 1-based
                }
            }
        }

        return true;
    }

    GLuint GMeshComp::LoadMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) 
    {
        GLuint VAO, VBO, EBO;

        // Generate and bind the Vertex Array Object
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // Generate and bind the Vertex Buffer Object
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        // Generate and bind the Element Buffer Object
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // Set vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind VBO, VAO, and EBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        return VAO;
    }
	void GMeshComp::DrawMesh(GLuint VAO, int indexCount) 
	{
		glPushMatrix();

		// Bind the Vertex Array Object
		glBindVertexArray(VAO);

		// Draw the mesh
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

		// Unbind the VAO
		glBindVertexArray(0);

		glPopMatrix();
	}
}
