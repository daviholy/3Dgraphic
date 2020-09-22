//
// Created by davih on 22.04.2020.
//

#ifndef GLFWTEST_TEXTUREBUILDER_H
#define GLFWTEST_TEXTUREBUILDER_H
#include <string>
#include <glad/glad.h>

class TextureBuilder {
private:
    bool _Yflip=false;
    GLuint _Repeat = GL_REPEAT;
    GLuint _MinFiltering = GL_LINEAR;
    GLuint _MaxFiltering = GL_NEAREST_MIPMAP_NEAREST;
    GLuint _Target = GL_TEXTURE_2D;
    GLuint _internalColorMode = GL_RGB;
    GLuint _ColorMode = GL_RGB;
    std::string _Source;
public:
  TextureBuilder (const std::string& source);
  void SetYflip(const bool value);
 void SetSource(const std::string& source);
 void SetRepeat(const int Repeat);
 void SetFiltering(const GLuint MinFiltering, const GLuint MaxFiltering);
 void SetColorMode(const GLuint ColorMode);
 void SetInternalColorMode(const GLuint ColorMode);
 void Reset();
 GLuint Build();
};


#endif //GLFWTEST_TEXTUREBUILDER_H
