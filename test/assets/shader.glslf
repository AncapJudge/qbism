#version 330 core

in vec2 TexCoord;
in float Light;

out vec4 color;

uniform sampler2D texture0;

void main() {
    color = Light * texture(texture0, TexCoord);
}