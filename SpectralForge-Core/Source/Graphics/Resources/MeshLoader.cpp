// Mesh.cpp
#include "pch.h"
#include "MeshLoader.h"

namespace Badiya {

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures) : VAO(), VBO(), EBO()
	{
		indexCount = static_cast<unsigned int>(indices.size());

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
			&indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Position)));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Normal)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, TexCoord)));

		glBindVertexArray(0);

	}

	void Mesh::Draw(Shader& shader) const
	{
		unsigned int diffuseNr = 0;
		unsigned int normalNr = 0;

		for (unsigned int i = 0; i < textures.size(); ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding

			std::string name = textures[i].type; // e.g., "diffuseMap", "normalMap"

			// assign texture number for multiple textures of same type
			if (name == "diffuseMap")
				name += std::to_string(diffuseNr++);
			else if (name == "normalMap")
				name += std::to_string(normalNr++);

			// set sampler uniform
			glUniform1i(glGetUniformLocation(shader.ID, name.c_str()), i);

			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		// Now draw your mesh geometry
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		// reset active texture
		glActiveTexture(GL_TEXTURE0);
	}
}