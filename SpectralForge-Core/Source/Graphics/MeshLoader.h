#pragma once

#include "Shader.h"

namespace Badiya {
	struct Texture
	{
		unsigned int id;
		std::string type;
		std::string path;
	};

	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoord;
	};

	class Mesh {
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
		void Draw(Shader& shader) const;

	private:
		unsigned int VAO, VBO, EBO;
		unsigned int indexCount;
		std::vector<Texture> textures;
	};
}