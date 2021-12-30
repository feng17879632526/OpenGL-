#pragma once

void SetUpLightShader(Shader& lightShader, glm::vec3& color);

void SetupLitShader(Shader& litShader, const glm::vec3& lightPos, Texture& diffuseMap, Texture& specularMap);

void DrawCube(Shader& shader, unsigned int VAO, glm::mat4&  model, glm::mat4& view, glm::mat4& projection);

void DeltaTimeCalculation();

