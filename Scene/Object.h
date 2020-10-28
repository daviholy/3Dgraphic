//
// Created by davih on 28.09.2020.
//

#ifndef GLFWTEST_OBJECT_H
#define GLFWTEST_OBJECT_H
#include <memory>
#include <string>
#include "Model.h"
/// @brief class defining game object (model with additional information like position and size)
 class Object {
public:
    /// @brief default empty game object
    Object()=default;
    Object(std::shared_ptr<Model> model_arg, const Shader &shader_arg, glm::vec3 position_arg = glm::vec3 (0.0f,0.0f,0.0f),
           const glm::vec3 size_arg = glm::vec3(1.0f));

     Object(const std::string &path_arg, const std::string &uniformmaterial_arg, Shader &shader_arg, const glm::vec3 position_arg = glm::vec3 (0.0f,0.0f,0.0f),
            const glm::vec3 size_arg = glm::vec3(1.0f)) :
             Object(std::make_shared<Model>(Model(path_arg, uniformmaterial_arg)),shader_arg,position_arg, size_arg){};

    void draw(const std::string &uniformMaterial, const glm::mat4 & viewMatrix_arg, const glm::mat4 & projectionMatrix_arg );

     const glm::vec3 &getSize() const;

     const glm::vec3 &getPosition() const;

     void setSize(const glm::vec3 &size);

     void setPosition(const glm::vec3 &position);

     /// @brief shader binded to the object
     Shader shader;
     std::shared_ptr<Model> model;
private:
    inline void setModelMatrix_();
     /// @brief size multiplier of original object
     glm::vec3 size_{};
     glm::vec3 position_{};
     glm::mat4 modelMatrix_{};
};

#endif //GLFWTEST_OBJECT_H
