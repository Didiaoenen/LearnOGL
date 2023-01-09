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

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

float colorValue = 0.1;
float specularValue = 64;

void main()
{
	//
	vec3 normal = texture(normalTex, fs_in.TexCoords).rgb;

	//
	normal = normalize(normal * 2.0f - 1.0);

	//
	vec3 color = texture(diffuseTex, fs_in.TexCoords).rgb;

	//
	vec3 ambient = colorValue * color;

	//
	vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentPos);
	vec3 diffuse = max(dot(lightDir, normal), 0.0) * color;

	//
	vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentPos);
	vec3 halfDir = normalize(lightDir + viewDir);
	vec3 specular = pow(max(dot(normal, halfDir), 0.0), specularValue) * lightColor;

	//
	FragColor = vec4(ambient + diffuse + specular, 1.0);
}