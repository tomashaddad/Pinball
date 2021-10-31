#version 460 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main() {
	FragColor = texture(skybox, TexCoords);
	BrightColor = vec4(0.0f, 0.0f, 0.0f, 1.0f); // output nothing to blur
}