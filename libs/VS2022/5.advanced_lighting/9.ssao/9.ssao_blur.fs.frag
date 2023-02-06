#version 330 core

in vec2 TexCoords;

out float FragColor;

uniform sampler2D ssaoInput;

float value = 4.0;

void main()
{
	vec2 texelSize = 1.0 / vec2(textureSize(ssaoInput, 0));

	float result = 0.0;
	for(int x = -2; x < 2; x++)
	{
		for(int y = -2; y < 2; y++)
		{
			vec2 offset = vec2(float(x), float(y)) * texelSize;
			result += texture(ssaoInput, TexCoords + offset).r;
		}
	}
	FragColor = result / (value * value);
}