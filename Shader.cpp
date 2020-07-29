//
// Created by davih on 12.04.2020.
//
#include "Shader.h"
#include <fstream>
#include <string>
#include <iostream>
constexpr int infoSize = 520;
Shader::Shader() =default;
//read from file to string --------------------------------------------
Shader::Shader (const GLchar *vertexPath, const GLchar *fragmentPath){
    std::string vertexSource,fragmentSource;
    const char* cVertexSource;
    const char* cFragmentSource;
std::ifstream vertexFile (vertexPath, std::ios::in|std::ios::ate );
if (vertexFile) {
    vertexSource.resize(vertexFile.tellg());
    vertexFile.seekg(0);
    vertexFile.read(&vertexSource[0], vertexSource.capacity());
    vertexFile.close();
    cVertexSource = vertexSource.c_str();
}
else
    throw std::ifstream::failure("can't open source file for vertex");

std::ifstream fragmentFile(fragmentPath,std::ios::in|std::ios::ate);
if (fragmentFile) {
    fragmentSource.resize(fragmentFile.tellg());
    fragmentFile.seekg(0);
    fragmentFile.read(&fragmentSource[0], fragmentSource.capacity());
    fragmentFile.close();
    cFragmentSource = fragmentSource.c_str();
}
else
    throw std::ifstream::failure("can't open source file for fragment");
//--------------------------------------------
//compile fragment and vertex shaders --------------
GLuint vertex = glCreateShader(GL_VERTEX_SHADER),fragment = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(vertex,1,&cVertexSource, nullptr);
glShaderSource(fragment,1,&cFragmentSource,nullptr);
glCompileShader(vertex);
glCompileShader(fragment);
int succes;
GLchar infolog[infoSize];

glGetShaderiv(vertex,GL_COMPILE_STATUS,&succes);
//check vertex compiling
if (!succes){
    glGetShaderInfoLog(vertex, infoSize,nullptr,infolog);
    std::cout <<"ERROR::SHADER::VERTEX::COMPILATION\n" << infolog << std::endl;
}
glGetShaderiv(fragment,GL_COMPILE_STATUS,&succes);
//check fragment compiling
if (!succes){
    glGetShaderInfoLog(fragment, infoSize,nullptr,infolog);
    std::cout <<"ERROR::SHADER::FRAGMENT::COMPILATION\n" << infolog << std::endl;
}
//-------------------------
//link shaders-----------------
ID = glCreateProgram();
glAttachShader(ID,vertex);
glAttachShader(ID,fragment);

glLinkProgram(ID);

glGetProgramiv(ID,GL_LINK_STATUS,&succes);
//check linking
if (!succes){
    glGetShaderInfoLog(ID,infoSize, nullptr,infolog);
    std::cout <<"ERROR::SHADER::LINKING\n" << infolog << std::endl;
    }
//-------------------
//delete necessary shaders
glDeleteShader(vertex);
glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(ID);
}
void Shader::setBool(const std::string &name, bool value) const
{
    GLuint uniformLoc;
    uniformLoc =glGetUniformLocation(ID,name.c_str());
    if (uniformLoc == -1) {
        std::cout << "can't find uniform " << name << std::endl;
        return;
    }
    glUniform1i(uniformLoc,(int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    GLuint uniformLoc;
    uniformLoc =glGetUniformLocation(ID,name.c_str());
    if (uniformLoc == -1) {
        std::cout << "can't find uniform " << name << std::endl;
        return;
    }
    glUniform1i(uniformLoc,value);
}
void Shader::setFloat(const std::string &name, float value) const {
    GLuint uniformLoc;
    uniformLoc =glGetUniformLocation(ID,name.c_str());
    if (uniformLoc == -1) {
        std::cout << "can't find uniform " << name << std::endl;
        return;
    }
    glUniform1f(uniformLoc,value);
}

void Shader::setMatrix(const std::string &name, const GLfloat *value) const {
    GLuint uniformLoc;
    uniformLoc =glGetUniformLocation(ID,name.c_str());
    if (uniformLoc == -1) {
        std::cout << "can't find uniform " << name << std::endl;
        return;
    }
    glUniformMatrix4fv(uniformLoc,1,GL_FALSE,value);
}

void Shader::setVec3(const std::string &name, float value1, float value2, float value3) const {
    GLuint uniformLoc;
    uniformLoc =glGetUniformLocation(ID,name.c_str());
    if (uniformLoc == -1) {
        std::cout << "can't find uniform " << name << std::endl;
        return;
    }
    glUniform3f(uniformLoc,value1,value2,value3);
}

