//
// Created by david on 22.07.20.
//

#ifndef GLFWTEST_CAMERA_H
#define GLFWTEST_CAMERA_H
#include <glm/glm.hpp>
enum CameraMovement{
    Forward,
    Backward,
    Left,
    RightMovement
};

class Camera {
public:
    glm::vec3 Position;
private:
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Pitch,Yaw,lastX,lastY;
public:
    Camera(float yaw,float pitch,glm::vec3 position = glm::vec3 (0.0f,0.0f,0.0f), glm::vec3 up = glm::vec3 (0.0f,1.0f,0.0f));
    glm::mat4 GetViewMatrix();
    void ProccesCameraMovement(CameraMovement movement, float deltatime);
    void ProccesMouseMovement(float xOffset, float yOffset);
private:
    void UpdateCameraVectors();
};


#endif //GLFWTEST_CAMERA_H
