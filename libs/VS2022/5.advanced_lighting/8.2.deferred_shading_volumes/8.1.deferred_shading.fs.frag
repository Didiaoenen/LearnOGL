#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D gPos;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

struct Light {
	vec3 Position;
	vec3 Color;
	float Linear;
	float Quadratic;
	float Radius;
};

const int lightCount = 32;

uniform Light lights[lightCount];
uniform vec3 viewPos;

float value = 0.0;
float specularValue = 16.0;

void main()
{
	vec3 FragPos = texture(gPos, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedo, TexCoords).rgb;
    float Specular = texture(gAlbedo, TexCoords).a;

	vec3 lighting  = Diffuse * value;
    vec3 viewDir  = normalize(viewPos - FragPos);
    for(int i = 0; i < lightCount; ++i)
    {
        float dis = length(lights[i].Position - FragPos);
        if(dis < lights[i].Radius)
        {
            //
            vec3 lightDir = normalize(lights[i].Position - FragPos);
            vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[i].Color;
            
            //
            vec3 halfwayDir = normalize(lightDir + viewDir);  
            vec3 specular = pow(max(dot(Normal, halfwayDir), 0.0), specularValue) * Specular * lights[i].Color;
            
            //
            float attenuation = 1.0 / (1.0 + lights[i].Linear * dis + lights[i].Quadratic * dis * dis);
            
            diffuse *= attenuation;
            specular *= attenuation;
            lighting += (diffuse + specular);
        }
    }    
    FragColor = vec4(lighting, 1.0);
}