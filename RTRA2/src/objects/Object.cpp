#include "Object.h"

Object::Object(Model model, ShaderPath path)
    : m_model(model)
    , m_shader({path.vertexShader, path.fragmentShader, path.geometryShader}) {}