#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

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

uniform Light lights[4];
uniform sampler2D diffuseTex;
uniform vec3 lightColor;

float colorValue = 0.0;
vec3 value = vec3(0.2126, 0.7152, 0.0722);

void main()
{
    vec3 color = texture(diffuseTex, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);

    vec3 ambient = colorValue * lightColor;

    vec3 lighting = vec3(0.0);
    for(int i = 0; i < 4; i++)
    {
        vec3 lightDir = normalize(lights[i].Position - fs_in.WPos);
        vec3 diffuse = max(dot(lightDir, normal), 0.0) * lights[i].Color * color;      
        
        float dis = length(fs_in.WPos - lights[i].Position);
        vec3 result = diffuse * 1.0 / (dis * dis);
        lighting += result;
    }
    vec3 result = ambient + lighting;

    float brightness = dot(result, value);
    if(brightness > 1.0)
    {
        BrightColor = vec4(result, 1.0);
    }
    else
    {
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    FragColor = vec4(result, 1.0);
}