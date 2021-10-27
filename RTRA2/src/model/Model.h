#pragma once

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <memory>
#include <string>
#include <vector>

#include "Mesh.h"
#include "Texture.h"
#include "api/Shader.h"

class Model {
public:
    Model(const std::string& path, bool gamma = false);
    void draw(std::shared_ptr<Shader>, GLuint skyboxTextureID = 0);

public:
    // model data
    std::vector<Texture> m_loadedTextures;
    std::vector<Mesh> m_meshes;
    std::string m_directory;
    bool m_gammaCorrection;

private:
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
                                              TextureType textureType);
    unsigned int TextureFromFile(const char* path, const std::string& directory,
                                 bool gamma = false);
};