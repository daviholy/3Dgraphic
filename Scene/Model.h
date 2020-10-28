//
// Created by davih on 19.09.2020.
//
#ifndef GLFWTEST_MODEL_H
#define GLFWTEST_MODEL_H


#include <assimp/scene.h>
#include <memory>
#include "../GL/Shader.h"
#include "Mesh.h"

constexpr char delimiter = '/';
/// @brief class representing of the loaded Model from file passed to constructor as string path
class Model {
public:
    Model()=default;
    Model(const std::string& path, const std::string &uniformMaterial_arg);
    void Draw(const Shader &shader){
        for (Mesh &mesh : meshes_)
            mesh.Draw(shader);
    }
private:
    std::vector<Texture>textures_loaded_;
    std::vector<Mesh> meshes_;
    /// @brief name of the object
    std::string directory_;

    /// @brief convert the Assimp mesh to Mesh
      Mesh convert(aiMesh *mesh_arg, const aiScene *scene, const std::string &uniformMaterial_arg);
      /// @brief stored loaded textures for the model
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureType type_arg);

    void processNode( aiNode *node, const aiScene *scene, const std::string &uniformMaterial_arg);
};


#endif //GLFWTEST_MODEL_H