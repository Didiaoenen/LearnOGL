#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT
{
	vec3 WPos;
	vec3 Normal;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform bool invertedNormal;

void main()
{
	vec4 viewPos = view * model * vec4(aPos, 1.0);
	vs_out.WPos = viewPos.xyz;

	mat3 normalMatrix = transpose(inverse(mat3(view * model)));
	vs_out.Normal = normalMatrix * (invertedNormal ? -aNormal : aNormal);

	gl_Position = projection * viewPos;
}