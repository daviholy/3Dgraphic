//
// Created by david on 22.07.20.
//

#ifndef GLFWTEST_CAMERA_H
#define GLFWTEST_CAMERA_H

#include <glm/glm.hpp>
#include "Object.h"

enum CameraMovement {
    Forward,
    Backward,
    Left,
    RightMovement
};

class Camera {
public:
    glm::vec3 Position{};
    glm::vec3 Front{};
    float Pitch, Yaw, lastX{}, lastY{};
private:
    glm::vec3 Up{};
    glm::vec3 Right{};
    glm::vec3 WorldUp{};
    bool firstMouseMove = true;
    Object *bindObject;

public:
    Camera(float yaw, float pitch, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), Object *object_arg = nullptr);

    glm::mat4 GetViewMatrix() const;

    void ProccesCameraMovement(CameraMovement movement, float deltatime);

    void ProccesMouseMovement(float xOffset, float yOffset);

private:
    void UpdateCameraVectors();
};


#endif //GLFWTEST_CAMERA_H
