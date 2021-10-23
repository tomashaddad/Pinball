#version 330 core
out vec4 fragment;

in vData {
	vec3 position;
    vec3 normal;
    vec2 texcoord;
} vertexOut;

struct DirectionalLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

#define MAX_POINT_LIGHTS 4
uniform int lightNumber;
uniform vec3 viewPos;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec3 viewDir = normalize(viewPos - vertexOut.position);

    vec3 result = calculateDirectionalLight(directionalLight, vertexOut.normal, viewDir);

    for (int i = 0; i < lightNumber; ++i) {
        result += calculatePointLight(pointLights[i], vertexOut.normal, vertexOut.position, viewDir);
    }

	fragment = vec4(result, 1.0);
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    
    // Ambient
    vec3 ambient = light.ambient * texture(texture_diffuse1, vertexOut.texcoord).rgb;

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(texture_diffuse1, vertexOut.texcoord).rgb;

    // Specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 128);
    vec3 specular = light.specular * spec * texture(texture_specular1, vertexOut.texcoord).rgb;

    return ambient + diffuse + specular;
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - vertexOut.position);

    // Ambient
    vec3 ambient = light.ambient * texture(texture_diffuse1, vertexOut.texcoord).rgb;

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(texture_diffuse1, vertexOut.texcoord).rgb;

    // Specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 128);
    vec3 specular = light.specular * spec * texture(texture_specular1, vertexOut.texcoord).rgb;

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}