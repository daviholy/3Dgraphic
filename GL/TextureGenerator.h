//
// Created by davih on 22.04.2020.
//

#ifndef GLFWTEST_TEXTUREGENERATOR_H
#define GLFWTEST_TEXTUREGENERATOR_H
#include <string>
#include <glad/glad.h>

class TextureGenerator {
private:
    bool _Yflip=false;
    GLuint Repeat_ = GL_REPEAT;
    GLuint MinFiltering_ = GL_LINEAR;
    GLuint MaxFiltering_ = GL_NEAREST_MIPMAP_NEAREST;
    GLuint Target_ = GL_TEXTURE_2D;
    GLuint internalColorMode_ = GL_RGB;
    std::string Source_;
public:
  TextureGenerator (const std::string& source);
  void SetYflip(const bool value);
 void SetSource(const std::string& source);
 void SetRepeat(const int Repeat);
 void SetFiltering(const GLuint MinFiltering, const GLuint MaxFiltering);
 void SetColorMode(const GLuint ColorMode);
 void SetInternalColorMode(const GLuint ColorMode);
 void Reset();
 GLuint Build();
};


#endif //GLFWTEST_TEXTUREGENERATOR_H
