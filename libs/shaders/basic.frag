#version 330 core

in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

const int lightMaxCount = 100;

struct Light
{
    vec4 lightPos;
    vec4 lightDir;
};

layout (std140) uniform LightInfo
{
    Light lights[lightMaxCount];
};

const float shadowRange = 0.5;
const vec3 diffuseColor = vec3(1.0, 1.0, 1.0);
const vec3 shadowColor = vec3(0.7, 0.7, 0.7);

out vec4 FragColor;

void main()
{   
    vec3 lightDir = normalize(lights[0].lightPos.xyz - WorldPos);
    float lambert = max(dot(normalize(Normal), lightDir), 0.0) * 0.5 + 0.5;
    vec3 diffuse = lambert > shadowRange ? diffuseColor : shadowColor;
    FragColor = vec4(lambert * diffuseColor, 1.0);
}