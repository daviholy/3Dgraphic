//
// Created by davih on 18.09.2020.
//

#ifndef GLFWTEST_TEXTURE_H
#define GLFWTEST_TEXTURE_H

#include <string>

enum class TextureType{
    diffuse =0,specular =1,normal=2
};
struct Texture {
    unsigned int id;
    TextureType type;
    std::string name;
};
#endif //GLFWTEST_TEXTURE_H
