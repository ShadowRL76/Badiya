#pragma once

#include "pch.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include "MeshLoader.h"
#include "Shader.h"

namespace Badiya {

	class Model
	{
	private:
		std::vector<Mesh> meshes;
		static std::string directory;

		void LoadModel(const std::string& path);
		void ProcessNode(const aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(const aiMesh* mesh, const aiScene* scene);
		static std::vector<Texture> LoadMaterialTextures(const aiMaterial* mat, aiTextureType type, const std::string& typeName);
	public:
		explicit Model(const std::string& path)
		{
			LoadModel(path);
		}
		static unsigned int TextureFromFile(const char* path, const std::string& directory);


		void Draw(Shader& shader);
	};
}