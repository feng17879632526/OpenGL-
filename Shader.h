#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include <fstream>

class Shader
{
public:
	/// <summary>
	/// Program ID
	/// </summary>
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void Use() const;
	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetVec3(const std::string& name, float x, float y, float z) const;
	void SetVec3(const std::string& name, const glm::vec3 value) const;
};
#endif