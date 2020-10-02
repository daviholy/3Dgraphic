#include "Camera.h"
#include <memory>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "control.h"
//
// Created by davih on 28.09.2020.
//

CameraCommand::CameraCommand(const CameraMovement movement_arg, const int key_arg) {
    movement_ = movement_arg;
    key_ = key_arg;
}

void CameraCommand::execute( GLFWwindow *window, const float deltaTime_arg, const std::shared_ptr<Camera> &activeCamera_arg) {
    if (glfwGetKey(window,key_) == GLFW_PRESS)
        activeCamera_arg->ProccesCameraMovement(movement_,deltaTime_arg);
}

 int const CameraCommand::getKey() {
    return key_;
}

Command::Command(const int key_arg, void (*executiveFunction_arg)(GLFWwindow *)) {
    key_ =key_arg;
    executiveFunction_ = executiveFunction_arg;
    released_ = true;
}

const int Command::getKey() {
    return key_;
}

void Command::execute(GLFWwindow *window) {
    if (glfwGetKey(window,key_))
            executiveFunction_(window);
}

void Control::update(GLFWwindow *window, float deltaTime_arg) {
    for (CameraCommand camera : cameraCommands)
        camera.execute(window,deltaTime_arg,activeCamera);
    for (Command command : commands)
        command.execute(window);
}

Control::Control(std::shared_ptr<Camera> activeCamera_arg) {
    activeCamera = activeCamera_arg;
}
