#version 330 core

in VS_OUT
{
	vec3 WPos;
	vec3 WNormal;
	vec2 TexCoords;
} fs_in;

out vec4 FragColor;

uniform sampler2D diffuseTex;
uniform samplerCube depthMap;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform float farPlane;

float colorValue = 0.1;
float specularValue = 64.0;

float ShadowCalculation(vec3 fragPos)
{
	vec3 fragToLight = fragPos - lightPos;
	float depth = texture(depthMap, fragToLight).r;
	return length(fragToLight) - 0.05f > depth * farPlane ? 1.0 : 0.0;
}

void main()
{
	vec3 color = texture(diffuseTex, fs_in.TexCoords).rgb;
	vec3 normal = normalize(fs_in.WNormal);

	//
	vec3 ambient = colorValue * lightColor;

	//
	vec3 lightDir = normalize(lightPos - fs_in.WPos);
	vec3 diffuse = max(dot(lightDir, normal), 0.0) * lightColor;

	//
	vec3 viewDir = normalize(viewPos - fs_in.WPos);
	vec3 halfDir = normalize(lightDir + viewDir);
	vec3 specular = pow(max(dot(normal, halfDir), 0.0), specularValue) * lightColor;

	//
	float shadow = ShadowCalculation(fs_in.WPos);
	vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

	FragColor = vec4(lighting, 1.0);
}
