#include "Model.h"

#include <algorithm>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Model::Model(const std::string& path, bool gamma)
    : m_gammaCorrection(gamma) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    m_directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::draw(Shader& shader) {
    for (unsigned int i = 0; i < m_meshes.size(); i++) {
        m_meshes[i].draw(shader);
    }
}

void Model::processNode(aiNode* node, const aiScene* scene) {
    // process all the node’s meshes (if any)
    for (auto i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (auto i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (auto i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        vertex.position =
            glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

        if (mesh->HasNormals()) {
            vertex.normal =
                glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        }

        // a vertex can contain up to 8 different texture coordinates. We thus make the assumption
        // that we won't use models where a vertex can have multiple texture coordinates so we
        // always take the first set (0).
        if (mesh->mTextureCoords[0]) {
            vertex.texCoords =
                glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            vertex.tangent =
                glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
            vertex.bitangent =
                glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
            ;
        } else {
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    for (auto i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (auto j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    aiColor3D diff, amb, spec;
    float shiney;
    material->Get(AI_MATKEY_COLOR_DIFFUSE, diff);
    material->Get(AI_MATKEY_COLOR_AMBIENT, amb);
    material->Get(AI_MATKEY_COLOR_SPECULAR, spec);
    material->Get(AI_MATKEY_SHININESS, shiney);

    glm::vec3 diffuse(diff.r, diff.g, diff.b);
    glm::vec3 ambient(amb.r, amb.g, amb.b);
    glm::vec3 specular(spec.r, spec.g, spec.b);
    Material mat({diffuse, ambient, specular, shiney});

    std::vector<Texture> diffuseMaps =
        loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps =
        loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::SPECULAR);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<Texture> normalMaps =
        loadMaterialTextures(material, aiTextureType_HEIGHT, TextureType::NORMAL);
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<Texture> heightMaps =
        loadMaterialTextures(material, aiTextureType_AMBIENT, TextureType::HEIGHT);
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return Mesh(vertices, indices, textures, mat);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type,
                                                 TextureType textureType) {
    std::vector<Texture> textures;
    for (auto i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a
        // new texture
        bool skip = false;

        for (auto j = 0; j < m_loadedTextures.size(); j++) {
            if (m_loadedTextures[j].path == str.C_Str()) {
                textures.push_back(m_loadedTextures[j]);
                skip = true;  // a texture with the same filepath has already been loaded, continue
                              // to next one. (optimization)
                break;
            }
        }
        if (!skip) {  // if texture hasn't been loaded already, load it
            Texture texture{TextureFromFile(str.C_Str(), m_directory), textureType, str.C_Str()};
            textures.push_back(texture);
            m_loadedTextures.push_back(
                texture);  // store it as texture loaded for entire model, to ensure we won't
                           // unnecesery load duplicate textures.
        }
    }
    return textures;
}

unsigned int Model::TextureFromFile(const char* path, const std::string& directory, bool gamma) {
    std::string filename(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1) {
            format = GL_RED;
        } else if (nrComponents == 3) {
            format = GL_RGB;
        } else if (nrComponents == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}