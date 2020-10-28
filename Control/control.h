//
// Created by davih on 30.09.2020.
//

#ifndef GLFWTEST_CONTROL_H
#define GLFWTEST_CONTROL_H

#include "../Scene/Object.h"

class CameraCommand{
public:
    CameraCommand(const CameraMovement movement_arg, const int key_arg);
    void execute( GLFWwindow *window,const float deltaTime_arg, Camera &activeCamera_arg);
    int getKey() const;
private:
    CameraMovement movement_;
    int key_;
};

class Command{
public:
    Command(const int key_arg,void (*executiveFunction_arg ) (GLFWwindow *window));
    int getKey() const;
    void execute(GLFWwindow *window);
private:
    void (*executiveFunction_ ) (GLFWwindow *window);
    int key_;
    bool released_;
};

class Control{
public:
     Camera *activeCamera;
    std::vector<CameraCommand> cameraCommands;
    std::vector<Command> commands;
    explicit Control (Camera &activeCamera_arg);
    void update(GLFWwindow *window,float deltaTime_arg);
};
#endif //GLFWTEST_CONTROL_H
