#version 460												

in vec4 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texSampler;
uniform vec4 color;

void main()
{
	vec4 fontColor = texture(texSampler, TexCoord);
	FragColor = vec4(color.rgb, color.a * fontColor.a);
}