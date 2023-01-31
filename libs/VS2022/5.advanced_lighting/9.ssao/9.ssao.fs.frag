#version 330 core

in vec2 TexCoords;

out float FragColor;

uniform sampler2D gPos;
uniform sampler2D gNormal;
uniform sampler2D texNoise;

int kernelSize = 64;
float radius = 0.5;
float bias = 0.025;
const vec2 noiseScale = vec2(800.0 / 4.0, 600.0 / 4.0); 

uniform vec3 samples[64];
uniform mat4 projection;

void main()
{
    vec3 fragPos = texture(gPos, TexCoords).xyz;
    vec3 normal = normalize(texture(gNormal, TexCoords).rgb);
    vec3 randomVec = normalize(texture(texNoise, TexCoords * noiseScale).xyz);
    
    vec3 tangent = normalize(randomVec - normal * dot(randomVec, normal));
    vec3 biTangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, biTangent, normal);
    
    float occlusion = 0.0;
    for(int i = 0; i < kernelSize; i++)
    {
        vec3 samplePos = TBN * samples[i];
        samplePos = fragPos + samplePos * radius; 
        
        vec4 offset = vec4(samplePos, 1.0);
        offset = projection * offset;
        offset.xyz /= offset.w;
        offset.xyz = offset.xyz * 0.5 + 0.5;
        
        float sampleDepth = texture(gPos, offset.xy).z;
        
        float rangeCheck = smoothstep(0.0, 1.0, radius / abs(fragPos.z - sampleDepth));
        occlusion += (sampleDepth >= samplePos.z + bias ? 1.0 : 0.0) * rangeCheck;     
    }

    occlusion = 1.0 - (occlusion / kernelSize);
    FragColor = occlusion;
}