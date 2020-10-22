//
// Created by davih on 19.09.2020.
//
#ifndef GLFWTEST_MODEL_H
#define GLFWTEST_MODEL_H


#include <assimp/scene.h>
#include <memory>
#include "Shader.h"
#include "Mesh.h"

constexpr char delimiter = '/';
/// @brief class representing of the loaded Model from file passed to constructor as string path
class Model {
public:
    Model()=default;
    explicit Model(const std::string& path);
    void Draw(const Shader &shader, const std::string &UniformMaterial){
        for (Mesh &mesh : meshes_)
            mesh.Draw(shader, UniformMaterial);
    }
private:
    std::vector<Texture>textures_loaded_;
    std::vector<Mesh> meshes_;
    /// @brief name of the object
    std::string directory_;

    /// @brief convert the Assimp mesh to Mesh
      Mesh convert(aiMesh *mesh_arg, const aiScene *scene);
      /// @brief stored loaded textures for the model
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName, TextureType type_arg);

    void processNode( aiNode *node, const aiScene *scene);
};


#endif //GLFWTEST_MODEL_H