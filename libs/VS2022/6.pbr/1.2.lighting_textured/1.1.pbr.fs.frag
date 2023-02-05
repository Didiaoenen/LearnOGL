#version 330 core

out vec4 FragColor;

in VS_OUT
{
	vec3 WPos;
	vec3 Normal;
	vec2 TexCoords;
} fs_in;

uniform sampler2D albedoTex;
uniform sampler2D normalTex;
uniform sampler2D matallicTex;
uniform sampler2D roughnessTex;
uniform sampler2D aoTex;

uniform vec3 lightPositionp[4];
uniform vec3 lightColor[4];

uniform vec3 camPos;

const float PI = 3.14159265359;

vec3 getNormalFromTex()
{
	vec3 tangentNormal = texture(normalTex, fs_in.TexCoords).xyz * 2.0 - 1.0;

	vec3 Q1 = dFdx(fs_in.WPos);
	vec3 Q2 = dFdy(fs_in.WPos);
	vec2 st1 = dFdx(fs_in.TexCoords);
	vec2 st2 = dFdx(fs_in.TexCoords);

	vec3 N = normalize(fs_in.Normal);
	vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
	vec3 B = -normalize(cross(N, T));
	mat3 TBN = mat3(T, B, N);

	return normalize(TBN * tangentNormal);
}

float DistibutionGGX(vec3 N, vec3 H, float roughness)
{
	float a = roughness * roughness;
	float a2 = a * a;
	float NdotH = max(dot(N, H), 0.0);
	float NdotH2 = NdotH * NdotH;

	float nom = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return nom / denom;
}

float GeometrySchlichGGX(float NdotV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r * r) / 8.0;

	float nom = NdotV;
	float denom = NdotV * (1.0 - k) + k;

	return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
	float NdotV = max(dot(N, V), 0.0);
	float NdotL = max(dot(N, L), 0.0);
	float ggx1 = GeometrySchlichGGX(NdotV, roughness);
	float ggx2 = GeometrySchlichGGX(NdotL, roughness);
	return ggx1 * ggx2;
}

vec3 fresnelSchick(float cosTheta, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

void main()
{
	vec3 albedo = pow(texture(albedoTex, fs_in.TexCoords).rgb, vec3(2.0));
	float metallic = texture(matallicTex, fs_in.TexCoords).r;
	float roughness = texture(roughnessTex, fs_in.TexCoords).r;
	float ao = texture(aoTex, fs_in.TexCoords).r;

	vec3 N = getNormalFromTex();
	vec3 V = normalize(camPos - fs_in.WPos);

	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);

	vec3 Lo = vec3(0.0);
	for(int i = 0; i < 4; i++)
	{
		vec3 L = normalize(lightPositionp[i] - fs_in.WPos);
		vec3 H = normalize(V + L);
		float dis = length(lightPositionp[i] - fs_in.WPos);
		float attenuation = 1.0 / (dis * dis);
		vec3 radiance = lightColor[i] * attenuation;
		
		float NDF = DistibutionGGX(N, H, roughness);
		float G = GeometrySmith(N, V, L, roughness);
		vec3 F = fresnelSchick(max(dot(H, V), 0.0), F0);

		vec3 numerator = NDF * G * F;
		float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
		vec3 specular = numerator / denominator;

		vec3 kS = F;
		vec3 kD = vec3(1.0) - kS;
		kD *= 1.0 - metallic;

		float NdotL = max(dot(N, L), 0.0);

		Lo += (kD * albedo / PI + specular) * radiance * NdotL;
	}

	vec3 amblient = vec3(0.03) * albedo * ao;

	vec3 color = amblient + Lo;

	color = color / (color + vec3(1.0));
	color = pow(color, vec3(1.0 / 2.2));

	FragColor = vec4(color, 1.0);
}