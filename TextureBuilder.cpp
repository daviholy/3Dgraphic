//
// Created by davih on 22.04.2020.
//

#include <iostream>
#include "TextureBuilder.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
TextureBuilder::TextureBuilder(const std::string& Source){
    Source_ = Source;
}
void TextureBuilder::SetFiltering(const GLuint MaxFiltering, const GLuint MinFiltering) {
    MaxFiltering_ = MaxFiltering;
    MinFiltering_ = MinFiltering;
}
void TextureBuilder::SetSource(const std::string& source) {
    Source_ = source;
}
void TextureBuilder::SetRepeat(const int Repeat) {
    Repeat_ = Repeat;
}
void TextureBuilder::SetInternalColorMode(GLuint ColorMode) {
    internalColorMode_ = ColorMode;
}
void TextureBuilder::Reset() {
    Source_ = nullptr;
    Repeat_ = GL_REPEAT;
    MinFiltering_ = GL_LINEAR;
    MaxFiltering_ = GL_NEAREST_MIPMAP_NEAREST;
    Target_ = GL_TEXTURE_2D;
    internalColorMode_ = GL_RGB;
}
void TextureBuilder::SetYflip(const bool value) {
    _Yflip = value;
}
//TODO:: delete the image from memory after sending it to GPU, implement some memory buffer
GLuint TextureBuilder::Build() {
    int StbiToGl[]{0,0,0,GL_RGB,GL_RGBA};
    if (Source_.empty())
        throw std::logic_error ("Didn't specified source");
    stbi_set_flip_vertically_on_load(_Yflip);
    GLuint ID;
    glGenTextures(1,&ID);
    glBindTexture(GL_TEXTURE_2D,ID);
    //use repeat wrapping
    glTexParameteri(Target_, GL_TEXTURE_WRAP_S, Repeat_);
    glTexParameteri(Target_, GL_TEXTURE_WRAP_T, Repeat_);
    //use linear filtering
    glTexParameteri(Target_, GL_TEXTURE_MIN_FILTER, MinFiltering_);
    glTexParameteri(Target_, GL_TEXTURE_MAG_FILTER, MaxFiltering_);
    int textureWidth, textureHeight, textureNrChannels;
    unsigned char *textureData = stbi_load(Source_.c_str(), &textureWidth, &textureHeight, &textureNrChannels, 0);

#if DEBUG
    if (textureNrChannels < 3)
        throw std::runtime_error("unsupported image format");
#endif

    if (textureData) {
        glTexImage2D(Target_, 0, internalColorMode_, textureWidth, textureHeight, 0, StbiToGl[textureNrChannels], GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(Target_);
    }
    else
        throw std::ios_base::failure ("can't load texture : [" + Source_ + "]");
    stbi_image_free(textureData);
    return ID;
}

