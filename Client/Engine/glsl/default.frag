#version 460												

in vec4 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texSampler;

void main()
{
	vec4 texColor = texture(texSampler, TexCoord);
	FragColor = texColor;
}