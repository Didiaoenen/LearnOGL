#version 330 core
layout (location = 0) out vec3 gPos;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedo;

in VS_OUT
{
	vec3 WPos;
	vec3 Normal;
	vec2 TexCoords;
} fs_in;

uniform sampler2D diffuseTex;
uniform sampler2D specularTex;

void main()
{
	gPos = fs_in.WPos;
	gNormal = normalize(fs_in.Normal);
	gAlbedo.rgb = texture(diffuseTex, fs_in.TexCoords).rgb;
	gAlbedo.a = texture(specularTex, fs_in.TexCoords).r;
}