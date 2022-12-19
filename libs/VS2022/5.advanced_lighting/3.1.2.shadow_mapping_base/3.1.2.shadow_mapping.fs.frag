#version 330 core

in VS_OUT
{
	vec3 WPos;
	vec3 WNormal;
	vec2 TexCoords;
	vec4 LightSpacePos;
} vs_out;

uniform sampler2D diffuseTex;
uniform sampler2D depthMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	
}