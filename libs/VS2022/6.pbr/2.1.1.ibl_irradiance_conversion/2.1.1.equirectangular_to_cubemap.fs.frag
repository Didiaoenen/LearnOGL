#version 330 core

out vec4 FragColor;

in vec3 WPos;

uniform sampler2D equirectangularTex;

const vec2 invAtan = vec2(0.1591, 0.3183);

vec2 SampleSphericalMap(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= invAtan;
    uv += 0.5;
    return uv;
}

void main()
{
	vec2 uv = SampleSphericalMap(normalize(WPos));
	vec3 color = texture(equirectangularTex, uv).rgb;

	FragColor = vec4(color, 1.0);
}