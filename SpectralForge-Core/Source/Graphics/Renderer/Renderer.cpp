
#include "pch.h"
#include "Renderer.h"


namespace Badiya {

	Renderer::Renderer(const float* vertices, size_t vertSize, const unsigned int* indices, size_t idxSize)
	{
	}

	unsigned int Renderer::m_textureID = 0;
	int Renderer::m_widthImg, Renderer::m_heightImg, Renderer::m_numColCh = 0;



	void Renderer::BindBuffersAndGenBuffers(const BufferType type, GLsizei n, GLuint* arrays)
	{
		glGenVertexArrays(1, &arrays[0]);
		glGenBuffers(1, &arrays[1]);
		glGenBuffers(1, &arrays[2]);

		glBindVertexArray(arrays[0]);

		// Bind and set vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, arrays[1]);

		if (type == BufferType::Skybox)
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
			glEnableVertexAttribArray(0);

			// Bind and set index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arrays[2]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), skyboxIndices, GL_STATIC_DRAW);
		}
		else if (type == BufferType::Object)
		{

			unsigned char* bytes = stbi_load("../SpectralForge-Core/resources/dylan.jpg",
				&m_widthImg, &m_heightImg, &m_numColCh, 0);

			if (!bytes) {
				spdlog::error("Failed to load image: ../SpectralForge-Core/resources/dylan.jpg");
				return;
			}

			spdlog::info("Image loaded: {}x{} channels: {}", m_widthImg, m_heightImg, m_numColCh);

			glGenTextures(1, &arrays[0]);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, arrays[0]);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
				m_widthImg, m_heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(bytes);
			glBindTexture(GL_TEXTURE_2D, 0);

		}
		glBindVertexArray(0);
	}


	unsigned int Renderer::CreateSkyboxVAO(const float* vertices, size_t vertSize, const unsigned int* indices, size_t idxSize)
	{
		return 0;
	}

	unsigned int Renderer::LoadCubeMap(const std::string faces[6])
	{

		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);


		for (unsigned int i = 0; i < 6; i++)
		{
			int width, height, nrChannels;
			unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				spdlog::info("Loaded texture '{}'", faces[i]);
				stbi_set_flip_vertically_on_load(false);
				glTexImage2D
				(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0,
					GL_RGB,
					width,
					height,
					0,
					GL_RGB,
					GL_UNSIGNED_BYTE,
					data
				);
				stbi_image_free(data);
			}
			else
			{
				spdlog::error("[CubeMap] Failed to load texture '{}', index {}.", faces[i], i);
				stbi_image_free(data);
			}
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return m_textureID;
	}


	void Renderer::Draw()
	{

	}
}