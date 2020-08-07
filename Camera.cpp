//
// Created by david on 22.07.20.
//

#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"
#include "glm/glm.hpp"
#include "Constants.h"
#include <GLFW/glfw3.h>
Camera::Camera(const float yaw, const float pitch, const glm::vec3 position, const glm::vec3 up) {
    Yaw = yaw;
    Pitch = pitch;
    Position = position;
    WorldUp = up;
    UpdateCameraVectors();
}
void Camera::UpdateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos (glm::radians(Pitch));
    front.y = sin (glm::radians(Pitch));
    front.z = sin (glm::radians(Yaw)) * cos (glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
 glm::mat4 Camera::GetViewMatrix() const{
   return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProccesMouseMovement (const float xPos, const float yPos) {
    if (firstMouseMove){
        lastX =xPos;
        lastY = yPos;
        firstMouseMove = false;
    }
    float xOffset = xPos - lastX;
    float yOffset = yPos - lastY;
    lastX = xPos;
    lastY = yPos;
    Yaw += xOffset * MOUSE_SENSITIVITY;
    Pitch -= yOffset * MOUSE_SENSITIVITY;

    if (Pitch < PITCH_MIN)
        Pitch = PITCH_MIN;
    else if (Pitch > PITCH_MAX)
        Pitch = PITCH_MAX;
    UpdateCameraVectors();
}

void Camera::ProccesCameraMovement(const CameraMovement movement, const float deltatime) {
    float velocity = CAMERA_SPEED * deltatime;
    switch (movement) {
        case Forward:
            Position += Front * velocity;
            break;
        case Backward:
            Position -= Front * velocity;
            break;
        case Left:
            Position -= Right * velocity;
            break;
        case RightMovement:
            Position += Right * velocity;
    }
}
