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

uniform vec3 lightColor;
uniform float heightScale;

float colorValue = 0.1;
float specularValue = 32.0;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{
	const float minLayers = 8;
	const float maxLayers = 32;
	float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));
	float layerDepth = 1.0 / numLayers;

	vec2 P = viewDir.xy / viewDir.z * heightScale;
	vec2 deltaTexCoords = P / numLayers;

	vec2 currentTexCoords = texCoords;
	float currentDepthMapValue = texture(depthTex, currentTexCoords).r;

	float currentLayerDepth = 0.0;
	while(currentLayerDepth < currentDepthMapValue)
	{
		currentTexCoords -= deltaTexCoords;
		currentDepthMapValue = texture(depthTex, currentTexCoords).r;
		currentLayerDepth += layerDepth;
	}

	//
	vec2 prevTexCoords = currentTexCoords + deltaTexCoords;
	
	float afterDepth = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = texture(depthTex, prevTexCoords).r - (currentLayerDepth - layerDepth);

	float weight = afterDepth / (afterDepth - beforeDepth);
	return prevTexCoords * weight + currentTexCoords * (1.0 - weight);
}

void main()
{
	vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentPos);
	vec2 texCoords = fs_in.TexCoords;

	texCoords = ParallaxMapping(fs_in.TexCoords, viewDir);
	if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
		discard;

	vec3 normal = texture(normalTex, texCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	vec3 color = texture(diffuseTex, texCoords).rgb;

	vec3 ambient = colorValue * lightColor;

	vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentPos);
	vec3 diffuse = max(dot(lightDir, normal), 0.0) * color;

	vec3 halfDir = normalize(lightDir + viewDir);
	vec3 specular = pow(max(dot(normal, halfDir), 0.0), specularValue) * lightColor;

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}