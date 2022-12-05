#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D roughnessTex;
uniform sampler2D specularTex;

void main()
{    
    FragColor = texture(diffuseTex, TexCoords);
}