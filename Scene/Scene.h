//
// Created by davih on 28.09.2020.
//

#ifndef GLFWTEST_SCENE_H
#define GLFWTEST_SCENE_H


#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "../Control/Camera.h"
#include "../menu/settings.h"
#include "../Control/control.h"
/// @brief class representing scene (representing the final drawing scene with defined cameras and objects)
class Scene {
public:
    explicit Scene(const Camera& camera_arg);
    Scene(const std::vector<Camera>& cameras_arg, unsigned int activeCamera_arg);
    /// @brief draw all the objects in the scene
    void draw(const std::string& uniformMaterial_arg = "material.");
    void addObject(const Object &object_arg);
    void addCamera(const Camera& camera);
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
  Camera& getActiveCamera(){
      return cameras_[activeCamera_];
  }
private:
std::vector<Object> objects_;
/// @brief integer, which sets the actual position in cameras_
unsigned int activeCamera_;
std::vector<Camera> cameras_;
glm::mat4 projection;
};

#endif //GLFWTEST_SCENE_H
