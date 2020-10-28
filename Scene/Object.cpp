#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Object.h"

//
// Created by davih on 28.09.2020.
//
void Object::setSize(const glm::vec3 &size) {
    size_ = size;
    setModelMatrix_();
}

void Object::setPosition(const glm::vec3 &position) {
    position_ = position;
    setModelMatrix_();
}

const glm::vec3 &Object::getSize() const {
    return size_;
}

const glm::vec3 &Object::getPosition() const {
    return position_;
}
void Object::setModelMatrix_() {
    //scale and rotating is did around origin point, thus we have to scale first and then translate
    modelMatrix_ = glm::scale(modelMatrix_,size_);
    modelMatrix_ = glm::translate(modelMatrix_,position_);
}

Object::Object(const std::shared_ptr<Model> model_arg, const Shader &shader_arg, const glm::vec3 position_arg, const glm::vec3 size_arg) {
    model = model_arg;
    shader = shader_arg;
    modelMatrix_ = glm::mat4 (1.0f);
    position_ = position_arg;
    size_ = size_arg;
    setModelMatrix_();
}

void Object::draw(const std::string &uniformMaterial, const glm::mat4 & viewMatrix_arg, const glm::mat4& projectionMatrix_arg) {
    shader.use();
    shader.setMatrix("model",glm::value_ptr(modelMatrix_));
    shader.setMatrix("view",glm::value_ptr(viewMatrix_arg));
    shader.setMatrix("projection",glm::value_ptr(projectionMatrix_arg));
    model->Draw(shader);
}
