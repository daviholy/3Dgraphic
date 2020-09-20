//
// Created by davih on 18.09.2020.
//

#ifndef GLFWTEST_MESH_H
#define GLFWTEST_MESH_H


#include <vector>
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    //convert from aiMesh (Assimp structure) to our mesh Structure
    void Draw(Shader &shader);
    Mesh(std::vector<Vertex> vertices_arg, std::vector<unsigned  int> indices_arg, std::vector<Texture> textures_arg){
        vertices = vertices_arg;
        indices = indices_arg;
        textures = textures_arg;
        setupMesh();
    }
private:
    //render data in GPU
    unsigned int VAO, VBO, EBO;
    //help function to
    void setupMesh();
};


#endif //GLFWTEST_MESH_H
