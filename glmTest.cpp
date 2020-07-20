//
// Created by davih on 27.04.2020.
//
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
int main() {
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans(1.0);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x << vec.y << vec.z  << std::endl;
    for (int y =0 ; y <4;y++){
        for (int x=0 ; x <4;x++)
            std::cout <<trans[x][y] << "  ";
        std::cout << std::endl;
    }
}