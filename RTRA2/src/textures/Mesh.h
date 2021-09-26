#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "api/Shader.h"

#include "Material.h"
#include "Vertex.h"
#include "Texture.h"

class Mesh {
public:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Texture> m_textures;
	Material m_material;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material material);
	void draw(Shader& shader);

public:
	unsigned int m_VAO;

private:
	unsigned int m_VBO;
	unsigned int m_EBO;
};