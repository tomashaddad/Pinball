#include "Mesh.h"

#include <glad/glad.h>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
           std::vector<Texture> textures, Material material, BoundingBox boundingBox)
    : m_vertices(vertices)
    , m_indices(indices)
    , m_textures(textures)
    , m_material(material)
    , m_boundingBox(boundingBox)
    , m_VAO(0)
    , m_VBO(0)
    , m_EBO(0) {
    // create buffers/arrays
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0],
                 GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, texCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, bitangent));
    // ids
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, boneIDs));

    // weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, weights));
    glBindVertexArray(0);
}

#include <iostream>

void Mesh::draw(Shader& shader, GLuint skyboxTextureID) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    for (auto i = 0; i < m_textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        TextureType type = m_textures[i].type;

        switch (type) {
            case TextureType::DIFFUSE:
                shader.setInt(("texture_diffuse" + std::to_string(diffuseNr++)).c_str(), i);
                break;
            case TextureType::SPECULAR:
                shader.setInt(("texture_specular" + std::to_string(specularNr++)).c_str(), i);
                break;
            case TextureType::NORMAL:
                shader.setInt(("texture_normal" + std::to_string(normalNr++)).c_str(), i);
                break;
            case TextureType::HEIGHT:
                shader.setInt(("texture_height" + std::to_string(heightNr++)).c_str(), i);
                break;
        }
        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }

    // If this model is meant to reflect the skybox
    if (skyboxTextureID) {
        shader.setInt("skybox", m_textures.size());
        glActiveTexture(GL_TEXTURE0 + m_textures.size());
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
    }

    // shader.setMaterial("material", m_material);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);  // set back to default
}