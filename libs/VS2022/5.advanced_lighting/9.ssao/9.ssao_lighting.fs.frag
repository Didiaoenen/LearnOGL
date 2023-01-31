#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D gPos;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D ssao;

struct Light
{
	vec3 Position;
	vec3 Color;
	float Linear;
	float Quadratic;
};

uniform Light light;
uniform vec3 viewPos;

float specularValue = 8.0;

void main()
{
	vec3 Pos = texture(gPos, TexCoords).rgb;
	vec3 Normal = texture(gNormal, TexCoords).rgb;
	vec3 Diffuse = texture(gAlbedo, TexCoords).rgb;
	float AmbientOcclusion = texture(ssao, TexCoords).r;
	
	vec3 ambient = vec3(0.3 * Diffuse * AmbientOcclusion);
	vec3 lighting = ambient;
	vec3 viewDir = normalize(viewPos - Pos);

	vec3 lightDir = normalize(light.Position - Pos);
	vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * light.Color;

	vec3 halfDir = normalize(lightDir + viewDir);
	vec3 specular = pow(max(dot(Normal, halfDir), 0.0), specularValue) * light.Color;

	float dis = length(light.Position - Pos);
	float attenuation = 1.0 / (1.0 + light.Linear * dis + light.Quadratic * dis * dis);
	diffuse *= attenuation;
	specular *= attenuation;
	lighting += (attenuation + specular);

	FragColor = vec4(lighting, 1.0);
}