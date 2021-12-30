#pragma once

enum TextureType { Diffuse, Specular };

class Texture
{
public:
	unsigned int ID;
	unsigned int Unit;
	TextureType Type;

	Texture(const char* filePath, unsigned int unit, TextureType type);

	void Bind() const;
	const char* GetTextureType() const;
private:
};