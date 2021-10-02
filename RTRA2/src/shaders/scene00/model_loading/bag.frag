#version 330 core
out vec4 fragment;

struct Material {
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
	float shininess;
};

in vData {
	vec3 position;
    vec3 normal;
    vec2 texcoord;
} vertexOut;

uniform Material material;
uniform sampler2D texture_diffuse1;

uniform vec3 cameraPosition;
uniform samplerCube skybox;

void main() {
	vec3 incident = normalize(vertexOut.position - cameraPosition);
	vec3 reflection = reflect(incident, normalize(vertexOut.normal));
    // fragment = texture(texture_diffuse1, vertexOut.texcoord);
	fragment = vec4(texture(skybox, reflection).rgb, 1.0);
}