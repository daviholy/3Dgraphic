//
// Created by davih on 22.04.2020.
//

#ifndef GLFWTEST_TEXTURE_H
#define GLFWTEST_TEXTURE_H
#include <string>
#include <glad/glad.h>

class TextureBuilder {
private:
    bool _Yflip=false;
    GLuint _Repeat = GL_REPEAT;
    GLuint _Filtering = GL_LINEAR;
    GLuint _Target = GL_TEXTURE_2D;
    GLuint _internalColorMode = GL_RGB;
    GLuint _ColorMode = GL_RGB;
    std::string _Source;
public:
  TextureBuilder (const std::string& source);
  void SetYflip(const bool value);
 void SetSource(const std::string& source);
 void SetRepeat(const int Repeat);
 void SetFiltering(const GLuint Filtering);
 void SetColorMode(const GLuint ColorMode);
 void SetInternalColorMode(const GLuint ColorMode);
 void Reset();
 GLuint Build();
};


#endif //GLFWTEST_TEXTURE_H
