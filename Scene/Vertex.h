//
// Created by davih on 18.09.2020.
//

#ifndef GLFWTEST_VERTEX_H
#define GLFWTEST_VERTEX_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <assimp/mesh.h>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};
#endif //GLFWTEST_VERTEX_H