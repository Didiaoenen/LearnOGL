#version 330 core

out vec4 FragColor;

in VS_OUT
{
	vec3 WPos;
	vec3 WNormal;
	vec2 TexCoords;
	vec4 LightSpacePos;
} fs_in;

uniform sampler2D diffuseTex;
uniform sampler2D depthMap;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

float colorValue = 0.3;
float specularValue = 64.0;

float ShadowCalculation(vec4 lightSpacePos)
{
	vec3 projCoords = lightSpacePos.xyz / lightSpacePos.w;
	projCoords = projCoords * 0.5 + 0.5;
	vec3 normal = normalize(fs_in.WNormal);
	vec3 lightDir = normalize(lightPos - fs_in.WPos);
	float bias = max(0.05 * (1.0 - dot(lightDir, normal)), 0.005);

	float shadow = projCoords.z - bias > texture(depthMap, projCoords.xy).r ? 1.0f : 0.0f;
	if(projCoords.z > 1.0)
        shadow = 0.0;

	return shadow;
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
	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfDir = normalize(lightDir + viewDir);
	vec3 specular = pow(max(dot(normal, halfDir), 0.0), specularValue) * lightColor;

	//
	float shadow = ShadowCalculation(fs_in.LightSpacePos);
	vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

	FragColor = vec4(lighting, 1.0);
}