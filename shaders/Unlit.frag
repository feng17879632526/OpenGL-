#version 330 core
out vec4 FragColor;

uniform sampler2D _texture;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


void main()
{   
    FragColor = vec4(1.0f,0.5f,1.0f, 1.0);
}