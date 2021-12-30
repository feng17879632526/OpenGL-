#include "Model.h"

#include<assimp/Importer.hpp>
#include<assimp/postprocess.h>
#include <iostream>
#include <string>


Model::Model(const char* filePath)
{
	LoadModel(filePath);
}

void Model::Draw(const Shader& shader)
{
	for (int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(shader);
}

void Model::LoadModel(const char* filePath)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (scene==NULL || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode==NULL)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
   
    fileDirectory = filePath;
    fileDirectory = fileDirectory.substr(0, fileDirectory.find_last_of('/')).c_str();

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    for (int i = 0; i < node->mNumMeshes; i++)
    {
      meshes.push_back(ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene));
    }

    for (int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> meshVertices;
    std::vector<unsigned int> meshIndices;
    std::vector<Texture> textures;

    //Vertices import
    for (int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex newVertex;
        newVertex.Postion = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        newVertex.Normal= glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        
        // does the mesh contain texture coordinates?
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            newVertex.TextureCoordinates = vec;
        }
        else
            newVertex.TextureCoordinates = glm::vec2(0.0f, 0.0f);
        meshVertices.push_back(newVertex);
    }

    //Indices import
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            meshIndices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material,aiTextureType_DIFFUSE, Diffuse);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = LoadMaterialTextures(material,aiTextureType_SPECULAR, Specular);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

	return Mesh(meshVertices,meshIndices,textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* material, aiTextureType aiType, TextureType textureType)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < material->GetTextureCount(aiType); i++)
    {
        aiString str;
        material->GetTexture(aiType, i, &str);
        Texture texture(str.C_Str(),GL_TEXTURE0+i,textureType);
        textures.push_back(texture);
    }
    return textures;
}
