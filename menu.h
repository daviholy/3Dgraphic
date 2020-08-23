//
// Created by davih on 23.08.2020.
//


#ifndef GLFWTEST_MENU_H
#define GLFWTEST_MENU_H
#include <imgui/imgui.h>
#include <glm/vec3.hpp>
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

/*
 * ==========================
 * ligthing setting variables
 * ==========================
 */
//definition of structures
//---------------------------
struct Material {
    //{R, G, B}
    float ambientColors[3], diffuseColors[3], specularColors[3], shininess;
};
struct Attenuation {
    float constant, linear, quadratic;
};
struct Light {
    float lightColor[3];
    float intensities[4];
    Attenuation attenuation;
};
struct SpotLight {
    Light light;
    float outerCone;
    float innerCone;
};
//---------------------------------
//variables of lights
//----------------------------------
Light pointLight = {{1.0f, 1.0f,  1.0f},
                    {0.8f, 0.1f,  0.6f, 0.36f},
                    {1.0f, 0.09f, 0.032f}};

Light dirLight = {{1.0f, 1.0f, 1.0f},
                  {0.2f, 0.1f, 0.2f, 0.3f}};

SpotLight spotLight = {1.0f, 0.953f, 0.667f,
                       0.6f, 0.1f, 1.0f, 0.5f,
                       1.0f, 0.09f, 0.032f,
                       15.0f, 6.0f};
//--------------------------------------
//material variables
//-------------------------
Material material = {0.931f, 0.848f, 0.749f,
                      0.799f, 0.727f, 0.045,
                     0.871f, 0.742f, 0.068f,
                     32};
//--------------------------
float backgroundColor[3] = {0.2f, 0.3f, 0.3};

bool movingLamp = true;
bool setDirectionLight = true;
bool setSpotLight = true;
bool setPointLight = true;
bool changedUniform = true;

float radius = 2.0f;
float speed = 1.0f;
float lightCenter[3] = {0, 0, 0};

int IDnum = 0;
//=======================================================================================

inline void HelpMarker(const char *desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

inline int UniqueID() {
    return IDnum++;
}

inline void ResetID() {
    IDnum = 0;
}
inline void drawLightProperties(Light &light){
    const char *name[] = {"light intensity", "ambient intensity", "diffuse intensity", "specular intensity"};
    //color property
    ImGui::PushID(UniqueID());
    if (ImGui::ColorEdit3("light color ", pointLight.lightColor))
        changedUniform = true;
    ImGui::PopID();
    //draw intensity properties
    for (int i = 0; i < 4; i++) {
        ImGui::PushID(UniqueID());
        if (ImGui::SliderFloat(name[i], &light.intensities[i], 0, 1))
            changedUniform = true;
        ImGui::PopID();
    }
    //draw attenuation properties
    //----------------------------
    ImGui::Text("Attentuation");
    ImGui::SameLine();
    HelpMarker("describe reducing intensity over distance ");

    ImGui::PushID(UniqueID());
    if(ImGui::SliderFloat("linear term", &light.attenuation.linear, 0.0014f, 0.7f))
        changedUniform = true;
    ImGui::PopID();

    ImGui::PushID(UniqueID());
    if(ImGui::SliderFloat("quadratic term", &light.attenuation.quadratic, 0.000007f, 1.8f))
        changedUniform = true;
    ImGui::PopID();
    //---------------------------
}

inline void drawLightProperties(SpotLight &light){
    const char *name[] = {"light intensity", "ambient intensity", "diffuse intensity", "specular intensity"};
    //color property
    ImGui::PushID(UniqueID());
    if (ImGui::ColorEdit3("light color ", light.light.lightColor))
        changedUniform = true;
    ImGui::PopID();

    //draw the intensity properties
    for (int i = 0; i < 4; i++) {
        ImGui::PushID(UniqueID());
        if (ImGui::SliderFloat(name[i], &light.light.intensities[i], 0, 1))
            changedUniform = true;
        ImGui::PopID();
    }

    //cone setting
    //---------------------------
    if (ImGui::SliderFloat("inner Cone", &spotLight.innerCone, 0.f, spotLight.outerCone))
        changedUniform = true;
    if (ImGui::SliderFloat("outer Cone", &spotLight.outerCone, 0, 90.f)) {
        changedUniform = true;

        if (spotLight.innerCone > spotLight.outerCone)
            spotLight.innerCone = spotLight.outerCone;
    }
    //---------------------------
    //draw attenuation properties
    //----------------------------
    ImGui::Text("Attentuation");
    ImGui::SameLine();
    HelpMarker("describe reducing intensity over distance ");

    ImGui::PushID(UniqueID());
    if(ImGui::SliderFloat("linear term", &light.light.attenuation.linear, 0.0014f, 0.7f))
        changedUniform = true;
    ImGui::PopID();

    ImGui::PushID(UniqueID());
    if(ImGui::SliderFloat("quadratic term", &light.light.attenuation.quadratic, 0.000007f, 1.8f))
        changedUniform = true;
    ImGui::PopID();
    //---------------------------

}

inline void drawMaterialProperties(Material &material){
    if (ImGui::SliderFloat("shininess", &material.shininess, 0, 128))
        changedUniform = true;
    //ambient color
    ImGui::PushID(UniqueID());
    if (ImGui::ColorEdit3("Ambient", material.ambientColors))
        changedUniform = true;
    ImGui::PopID();

    // diffuse color
    ImGui::PushID(UniqueID());
    if (ImGui::ColorEdit3("Diffuse", material.diffuseColors))
        changedUniform = true;
    ImGui::PopID();

    //specular color
    ImGui::PushID(UniqueID());
    if (ImGui::ColorEdit3("Specular", material.specularColors))
        changedUniform = true;
    ImGui::PopID();

}

//static function for drawing the menu
inline void drawMenu(){
    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    //====================
    // render GUI
    //====================
    //checkboxes
    //--------------------
    ImGui::Begin("settings");
    if (ImGui::Checkbox("lamp light", &setPointLight))
        changedUniform = true;
    ImGui::SameLine();
    if (ImGui::Checkbox("flashlight", &setSpotLight))
        changedUniform = true;
    ImGui::SameLine();
    if (ImGui::Checkbox("global light", &setDirectionLight))
        changedUniform = true;
    ImGui::ColorEdit3("background color", backgroundColor);
    //--------------------

    if (ImGui::CollapsingHeader("lamp ")) {

        if (ImGui::TreeNode("lighting")) {
            drawLightProperties(pointLight);
            ImGui::TreePop();
        }
        //position setting of the lamp
        if (ImGui::TreeNode("position")) {
            ImGui::SliderFloat("radius", &radius, 0, 10);
            ImGui::SliderFloat("speed", &speed, 0, 1);
            ImGui::SliderFloat3("position",lightCenter,-10,10);
            ImGui::Checkbox("moving", &movingLamp);
            ImGui::TreePop();
        }

    }

    if (ImGui::CollapsingHeader("global lighting"))
        drawLightProperties(dirLight);

    if (ImGui::CollapsingHeader("flashlight light")) {
        drawLightProperties(spotLight);
    }

    if (ImGui::CollapsingHeader("material"))
        drawMaterialProperties(material);
//========================================
    ImGui::End();
    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ResetID();
}
#endif GLFWTEST_MENU_H