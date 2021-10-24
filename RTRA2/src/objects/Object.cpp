#include "Object.h"

Object::Object(Model model, ShaderPath path, Collider collider)
    : m_model(model)
    , m_shader({path.vertexShader, path.fragmentShader, path.geometryShader})
    , m_collider(collider) {}