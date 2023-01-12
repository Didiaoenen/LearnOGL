#version 330 core

out vec4 FragColor;

in VS_OUT
{
	vec3 WPos;
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentPos;
} fs_in;

uniform sampler2D diffuseTex;
uniform sampler2D normalTex;
uniform sampler2D depthTex;

uniform float heightScale;

void main()
{

}