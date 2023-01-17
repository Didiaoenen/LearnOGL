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
	float height = texture(depthTex, texCoords).r;
	vec2 p = viewDir.xy / viewDir.z * (height * heightScale);
	return texCoords - p;
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
	
	vec3 halfDir = normalize(lightDir + normal);
	vec3 specular = pow(max(dot(normal, halfDir), 0.0), specularValue) * lightColor;

	FragColor = vec4(ambient + diffuse + specular, 1.0);
}