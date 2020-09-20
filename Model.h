//
// Created by davih on 19.09.2020.
//
#ifndef GLFWTEST_MODEL_H
#define GLFWTEST_MODEL_H


#include <assimp/scene.h>
#include "Shader.h"
#include "Mesh.h"

constexpr char delimiter = '/';
class Model {
public:
    Model()=default;
    Model(std::string path);
    void Draw(Shader &shader){
        for (Mesh mesh : meshes)
            mesh.Draw(shader);
    }
private:
      Mesh convert(aiMesh *mesh_arg, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
    std::vector<Mesh> meshes;
    std::string directory;

    void processNode( aiNode *node, const aiScene *scene);
};


#endif //GLFWTEST_MODEL_H