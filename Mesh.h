#pragma once

#include "glm/glm.hpp"
#include "Texture.h"
#include <vector>
#include "Shader.h"

struct Vertex
{
	glm::vec3 Postion;
	glm::vec3 Normal;
	glm::vec2 TextureCoordinates;
};

class Mesh
{
public:
	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;
	std::vector<Texture> Textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	void Draw(const Shader& shader);

private:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;

	void SetupMesh();
};