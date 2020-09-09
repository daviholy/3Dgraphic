//
// Created by davih on 22.04.2020.
//

#include <iostream>
#include <stb_image.h>
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>

TextureBuilder::TextureBuilder(const std::string& Source){
    _Source = Source;
}
void TextureBuilder::SetFiltering(const GLuint Filtering) {
    _Filtering = Filtering;
}
void TextureBuilder::SetSource(const std::string& source) {
    _Source = source;
}
void TextureBuilder::SetRepeat(const int Repeat) {
    _Repeat = Repeat;
}
void TextureBuilder::SetColorMode(const GLuint ColorMode) {
    _ColorMode = ColorMode;
}
void TextureBuilder::Reset() {
    _Source = nullptr;
    _Repeat = GL_REPEAT;
    _Filtering = GL_LINEAR;
    _Target = GL_TEXTURE_2D;
    _ColorMode= GL_RGB;
    _internalColorMode = GL_RGB;
}
void TextureBuilder::SetYflip(const bool value) {
    _Yflip = value;
}
GLuint TextureBuilder::Build() {
    if (_Source.empty())
        throw std::logic_error ("Didn't specified source");
    stbi_set_flip_vertically_on_load(_Yflip);
    GLuint ID;
    glGenTextures(1,&ID);
    glBindTexture(GL_TEXTURE_2D,ID);
    //use repeat wrapping
    glTexParameteri(_Target, GL_TEXTURE_WRAP_S, _Repeat);
    glTexParameteri(_Target, GL_TEXTURE_WRAP_T, _Repeat);
    //use linear filtering
    glTexParameteri(_Target, GL_TEXTURE_MIN_FILTER, _Filtering);
    glTexParameteri(_Target, GL_TEXTURE_MAG_FILTER, _Filtering);
    int textureWidth, textureHeight, textureNrChannels;
    unsigned char *textureData = stbi_load(_Source.c_str(),&textureWidth,&textureHeight,&textureNrChannels,0);
    if (textureData) {
        glTexImage2D(_Target, 0, _internalColorMode, textureWidth, textureHeight, 0, _ColorMode, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(_Target);
    }
    else
        throw std::ios_base::failure ("can't load texture : [" + _Source + "]");
    stbi_image_free(textureData);
    return ID;
}

void TextureBuilder::SetInternalColorMode(GLuint ColorMode) {
_internalColorMode = ColorMode;
}
