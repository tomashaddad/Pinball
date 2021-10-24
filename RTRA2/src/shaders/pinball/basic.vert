#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

out vData {
    vec3 position;
    vec3 normal;
    vec2 texcoord;
} vertexOut;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vertexOut.position = vec3(model * vec4(position, 1.0));
    vertexOut.normal = normalize(mat3(transpose(inverse(model))) * normal);
    vertexOut.texcoord = texcoord;

    gl_Position = projection * view * model * vec4(position, 1.0);
}