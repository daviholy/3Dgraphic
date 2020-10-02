//
// Created by davih on 28.09.2020.
//

#ifndef GLFWTEST_SCENE_H
#define GLFWTEST_SCENE_H


#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Camera.h"
#include "settings.h"
#include "control.h"
/// @brief class representing scene (representing the final drawing scene with defined cameras and objects)
class Scene {
public:
    Scene(const std::shared_ptr<Camera>& camera_arg, Control &control_arg);
    Scene(const std::vector<std::shared_ptr<Camera>>& cameras_arg, Control &control_arg, unsigned int activeCamera_arg);
    /// @brief draw all the objects in the scene
    void draw(const std::string& uniformMaterial_arg = "material.");
    void addObject(const std::shared_ptr<Object> &object_arg);
    void addCamera(std::shared_ptr<Camera>& camera);
    //todo: implement as coroutines?
    void nextCamera();
    //todo: make better system then setting the uniforms manually?
    /// @brief
    /// @param Uniform
  /*  void setShaderUniformFloat(const std::string Uniform_arg,float value_arg, Shader &shader_arg){
        std::shared_ptr<std::vector<Shader>> foundShaders;
        for (std::shared_ptr<Object> object : objects_){
            if (foundShaders.use_count())
        }
    }*/
    std::shared_ptr<Camera> activeCamera;
private:
std::vector<std::shared_ptr<Object>> objects_;
/// @brief integer, which sets the actual position in cameras_
unsigned int activeCamera_;
std::vector<std::shared_ptr<Camera>> cameras_;
glm::mat4 projection;
//TODO; decouple with control
Control control_;
};

#endif //GLFWTEST_SCENE_H
