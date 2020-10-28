//
// Created by davih on 18.09.2020.
//

#ifndef GLFWTEST_MESH_H
#define GLFWTEST_MESH_H


#include <utility>
#include <vector>
#include "Vertex.h"
#include "../GL/Texture.h"
#include "../GL/Shader.h"
#include <memory>
class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    /// @brief convert from aiMesh (Assimp structure) to our mesh Structure
    /// @param shader shader to use
    /// @param UniformMaterial basic name of texture uniforms (used convention UniformMaterial + name + number)
    void Draw(const Shader &shader);
    Mesh(std::vector<Vertex> vertices_arg, std::vector<unsigned  int> indices_arg, std::vector<Texture>& textures_arg, std::vector<std::string> &uniforms):
    uniforms(std::move(uniforms)){
        vertices = std::move(vertices_arg);
        indices = std::move(indices_arg);
        textures = textures_arg;
        setupMesh();
    }
private:
     std::vector<std::string> uniforms;

    /// @brief render data in GPU
    unsigned int VAO, VBO, EBO;
    /// @brief help function to
    void setupMesh();
};


#endif //GLFWTEST_MESH_H
