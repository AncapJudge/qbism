#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in float light;

uniform mat4 matrix;
out vec2 TexCoord;
out float Light;

void main() {
	gl_Position = matrix * vec4(position,1);
	TexCoord = texCoord;
	Light = light;
}