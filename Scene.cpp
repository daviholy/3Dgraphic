//
// Created by davih on 28.09.2020.
//

#include "Scene.h"

void Scene::draw(const std::string &uniformMaterial_arg) {
    for(std::shared_ptr<Object> &object: objects_)
        object->draw(uniformMaterial_arg,activeCamera->GetViewMatrix(),projection );
}

Scene::Scene(const std::shared_ptr<Camera> &camera_arg, Control &control_arg):control_(control_arg) {
    cameras_.push_back(camera_arg);
    activeCamera = camera_arg;
    activeCamera_=0;
    projection =  glm::perspective(glm::radians(settings::FOV), (float) settings::scrWidth / settings::scrHeight, 0.1f, 100.0f);
}

Scene::Scene(const std::vector<std::shared_ptr<Camera>> &cameras_arg,Control &control_arg, const unsigned int activeCamera_arg =0):
control_(control_arg) {
cameras_ = cameras_arg;
activeCamera_ = activeCamera_arg;
activeCamera = cameras_[activeCamera_];
projection =  glm::perspective(glm::radians(settings::FOV), (float) settings::scrWidth / settings::scrHeight, 0.1f, 100.0f);
}

void Scene::addCamera(std::shared_ptr<Camera>& camera) {
cameras_.push_back(camera);
activeCamera_ =0;
}
void Scene::nextCamera() {
    if (activeCamera_++ >= cameras_.size())
        activeCamera_ =0;
    activeCamera = cameras_[activeCamera_];
    control_.activeCamera= activeCamera;
}

void Scene::addObject(const std::shared_ptr<Object> &object_arg) {
    objects_.push_back(object_arg);
}
