#version 330 core

in VS_OUT
{
	vec3 WPos;
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentPos;
} vs_in;

uniform sampler2D diffuseTex;
uniform sampler2D normalTex;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	
}