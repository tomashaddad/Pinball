#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
                                   glm::vec3 direction)
    : ambient(ambient)
    , diffuse(diffuse)
    , specular(specular)
    , direction(direction) {}