#version 330 core

out vec4 FragColor;

in VS_OUT 
{
    vec3 WPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

struct Light 
{
    vec3 Position;
    vec3 Color;
};

uniform Light lights[16];
uniform vec3 lightColor;
uniform sampler2D diffuseTex;

float colorValue = 0.1;

void main()
{           
    vec3 color = texture(diffuseTex, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);

    vec3 ambient = colorValue * lightColor;

    vec3 lighting = vec3(0.0);
    for(int i = 0; i < 16; i++)
    {
        vec3 lightDir = normalize(lights[i].Position - fs_in.WPos);
        vec3 diffuse = max(dot(lightDir, normal), 0.0) * lights[i].Color * color;    
        
        float dis = length(fs_in.WPos - lights[i].Position);
        vec3 result = diffuse * 1.0 / (dis * dis);
        lighting += result;
    }

    FragColor = vec4(color, 1.0);
}