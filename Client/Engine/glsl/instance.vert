#version 460

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in mat4 instanceModel;

out vec4 vertexColor;
out vec2 TexCoord;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * instanceModel * vec4(pos, 1.0);
	vertexColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
	TexCoord = tex;
}