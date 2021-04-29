#version 450

layout(location = 0) out vec4 color;

uniform float red;

void main() {
	color = vec4(red, 0.0f, 0.0f, 1.0f);
};