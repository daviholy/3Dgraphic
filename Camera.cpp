//
// Created by david on 22.07.20.
//

#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"
#include "glm/glm.hpp"
#include "Constants.h"
Camera::Camera(float yaw, float pitch, glm::vec3 position, glm::vec3 up) {
    lastX = SCR_WIDTH/2.0;
    lastY = SCR_HEIGHT/2.0;
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

    Right = glm::normalize(glm::cross(Front,WorldUp));
    Up = glm::normalize(glm::cross(Right,Front));
}
 glm::mat4 Camera::GetViewMatrix() {
   return glm::lookAt(Position,Position + Front, Up);
}

void Camera::ProccesMouseMovement (float xPos, float yPos){

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

void Camera::ProccesCameraMovement(CameraMovement movement, float deltatime) {
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
