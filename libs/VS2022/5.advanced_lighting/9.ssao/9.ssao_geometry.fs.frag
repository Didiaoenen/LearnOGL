#version 330 core
layout (location = 0) out vec3 gPos;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gAlbedo;

in VS_OUT
{
	vec3 WPos;
	vec3 Normal;
} fs_in;

uniform vec3 albedoColor;

void main()
{
	gPos = fs_in.WPos;
	gNormal = normalize(fs_in.Normal);
	gAlbedo.rgb = albedoColor;
}