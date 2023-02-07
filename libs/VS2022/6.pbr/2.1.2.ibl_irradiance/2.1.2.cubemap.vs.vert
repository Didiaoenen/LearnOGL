#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTexCoords;

out vec3 WPos;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	WPos = aPos;

	gl_Position = projection * view * vec4(WPos, 1.0);
}