//
// Created by davih on 28.09.2020.
//

#include "Scene.h"

void Scene::draw(const std::string &uniformMaterial_arg) {
    for (Object &object: objects_)
        object.draw(uniformMaterial_arg, cameras_[activeCamera_].GetViewMatrix(), projection);
}

Scene::Scene(const Camera &camera_arg) : projection(
        glm::perspective(glm::radians(settings::FOV), (float) settings::scrWidth / settings::scrHeight, 0.1f, 100.0f)) {
    cameras_.push_back(camera_arg);
    activeCamera_ = 0;
}

Scene::Scene(const std::vector<Camera> &cameras_arg, const unsigned int activeCamera_arg = 0) : projection(
        glm::perspective(glm::radians(settings::FOV), (float) settings::scrWidth / settings::scrHeight, 0.1f,
                         100.0f)) {
    cameras_ = cameras_arg;
    activeCamera_ = activeCamera_arg;
}

void Scene::addCamera(const Camera &camera) {
    cameras_.push_back(camera);
}

void Scene::nextCamera() {
    if (activeCamera_++ >= cameras_.size())
        activeCamera_ = 0;
}

void Scene::addObject(const Object &object_arg) {
    objects_.push_back(object_arg);
}
