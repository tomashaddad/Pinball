#version 330 core

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

#define MAX_POINT_LIGHTS 1
uniform PointLight pointLights[MAX_POINT_LIGHTS];

void main() {
	FragColor = vec4(pointLights[0].diffuse, 1.0);
}