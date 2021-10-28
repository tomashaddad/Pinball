#version 330 core

out vec4 fragment;

uniform vec3 colour;

void main() {
	fragment = vec4(colour, 1.0);
}