#pragma once
/**/

#include <string>
namespace Badiya {

	class Renderer
	{

	public:
		unsigned int* m_skyboxVAO{}, m_skyboxVBO{}, m_skyboxEBO{};
		unsigned int m_TextureID{};
		static unsigned int m_textureID;
		static int m_widthImg, m_heightImg, m_numColCh;

		static constexpr float skyboxVertices[]
		{
			-1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,
			-1.0f, 1.0f, -1.0f
		};

		static constexpr unsigned int skyboxIndices[]
		{
			// Right face
			1, 2, 6,
			6, 5, 1,
			// Left face
			0, 4, 7,
			7, 3, 0,
			// Top face
			4, 5, 6,
			6, 7, 4,
			// Bottom face
			0, 1, 2,
			2, 3, 0,
			// Back face
			3, 2, 6,
			6, 7, 3,
			// Front face
			0, 1, 5,
			5, 4, 0
		};
	public:
		enum class BufferType : uint8_t { Skybox, Object };

		Renderer() = default;
		Renderer(const float* vertices, size_t vertSize, const unsigned int* indices, size_t idxSize);

		unsigned int CreateSkyboxVAO(const float* vertices, size_t vertSize, const unsigned int* indices, size_t idxSize);
		static unsigned int LoadCubeMap(const std::string faces[6]);

		void Draw();
		static void BindBuffersAndGenBuffers(const BufferType type, GLsizei n, GLuint* arrays);

	};
}