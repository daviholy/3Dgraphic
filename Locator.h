//
// Created by davih on 28.10.2020.
//

#ifndef GLFWTEST_LOCATOR_H
#define GLFWTEST_LOCATOR_H


#include "menu/Menu.h"
#include "Scene/Scene.h"

class Locator {
public:
    static void setMenu(Menu menu__arg) {
        menu_ = menu__arg;
    }

    static Menu getMenu() {
        return menu_;
    }

    static void setScene(Scene scene_arg) {
        scene_ = scene_arg;
    }

    static Scene getScene(){
        return scene_;
    }

private:
    static Menu menu_;
    static Scene scene_;
};


#endif //GLFWTEST_LOCATOR_H
