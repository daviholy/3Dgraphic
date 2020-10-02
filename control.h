//
// Created by davih on 30.09.2020.
//

#ifndef GLFWTEST_CONTROL_H
#define GLFWTEST_CONTROL_H

class CameraCommand{
public:
    CameraCommand(const CameraMovement movement_arg, const int key_arg);
    void execute( GLFWwindow *window,const float deltaTime_arg, const std::shared_ptr<Camera> &activeCamera_arg);
    const int getKey();
private:
    CameraMovement movement_;
    int key_;
};

class Command{
public:
    Command(const int key_arg,void (*executiveFunction_arg ) (GLFWwindow *window));
    const int getKey();
    void execute(GLFWwindow *window);
private:
    void (*executiveFunction_ ) (GLFWwindow *window);
    int key_;
};

class Control{
public:
     std::shared_ptr<Camera> activeCamera;
    std::vector<CameraCommand> cameraCommands;
    std::vector<Command> commands;
    Control (std::shared_ptr<Camera> activeCamera_arg);
    void update(GLFWwindow *window,float deltaTime_arg);
private:
    Control()= default;
};
#endif //GLFWTEST_CONTROL_H
