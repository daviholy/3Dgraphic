//
// Created by davih on 12.04.2020.
//

#ifndef GLFWTEST_SHADER_H
#define GLFWTEST_SHADER_H

#include <glad/glad.h>
#include <string>

class Shader {
public:
    //program id
GLuint ID{};
    Shader();
//reads sources and build shader
Shader (const GLchar *vertexPath, const GLchar *fragmentPath);
void use();
void setFloat(const std::string &name,float value)const;
void setInt(const std::string &name, int value)const;
void setBool(const std::string &name, bool value)const;
void setMatrix(const std::string &name, const GLfloat* value) const;
void setVec3(const std::string &name, float value1, float value2, float value3) const;
void setVec4(const std::string &name, float value1, float value2, float value3, float value4) const;
};


#endif //GLFWTEST_SHADER_H
