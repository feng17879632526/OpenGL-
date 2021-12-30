#pragma once

#include "Mesh.h"
#include <vector>
#include <assimp/scene.h>
#include <string>

class Model
{
public:

	Model(const char* filePath);
	void Draw(const Shader& shader);

private:

	std::vector<Mesh> meshes;
	std::string fileDirectory;

	void LoadModel(const char* filePath);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* material, aiTextureType aiType, TextureType textureType);

};