//
// Created by davih on 23.08.2020.
//


#ifndef GLFWTEST_SETTINGS_H
#define GLFWTEST_SETTINGS_H
#include <imgui/imgui.h>
#include <glm/vec3.hpp>
#include <string>
#include <thread>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "../common.h"

class settings {
private:
/*
 * ==========================
 * ligthing setting variables
 * ==========================
 */
//definition of structures
//---------------------------
    struct Material {
        float  shininess;
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
public:
//---------------------------------
//variables of lights
//----------------------------------
  inline  static  Light pointLight = {{1.0f, 1.0f,  1.0f},
                                      {0.8f, 0.1f,  0.6f, 0.36f},
                                      {1.0f, 0.09f, 0.032f}};

  inline  static  Light dirLight = {{1.0f, 1.0f, 1.0f},
                                    {0.2f, 0.1f, 0.2f, 0.3f}};

  inline static  SpotLight spotLight = {1.0f, 0.953f, 0.667f,
                                        0.6f, 0.1f, 1.0f, 0.5f,
                                        1.0f, 0.09f, 0.032f,
                                        15.0f, 6.0f};
//--------------------------------------
//material variable
//-------------------------
  inline  static  Material material = {32};
//--------------------------
   inline static float backgroundColor[3] = {0.2f, 0.3f, 0.3};

    inline static  unsigned int scrWidth = 400;
    inline static  unsigned int scrHeight = 400;
    inline static  float FOV =45;
    inline static  float mouseSensitivity = 0.2f;
    inline static  float pitchMax = 89.0f;
    inline static  float pitchMin = -89.0f;
    inline static  float cameraSpeed = 4.0f ;
   inline static  bool movingLamp = true;
   inline static  bool setDirectionLight = true;
   inline static  bool setSpotLight = true;
   inline static  bool setPointLight = true;
   inline static  bool changedUniform = true;
   inline static bool hideGui = true;

    inline static float radius = 2.0f;
    inline static float speed = 1.0f;
    inline static float lightCenter[3] = {0, 0, 0};

    inline static int IDnum = 0;

//=======================================================================================
private:
    inline static void HelpMarker(const char *desc) {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }

    inline static void drawLightProperties(Light &light, bool attentuation = true) {
        const char *name[] = {"light intensity", "ambient intensity", "diffuse intensity", "specular intensity"};
        //color property
        ImGui::PushID(IDnum++);
        std::string num = std::to_string(IDnum);
        if (ImGui::ColorEdit3("light color ", light.lightColor))
            changedUniform = true;
        ImGui::PopID();
        //draw intensity properties
        for (int i = 0; i < 4; i++) {
            ImGui::PushID(IDnum++);
            if (ImGui::SliderFloat(name[i], &light.intensities[i], 0, 10))
                changedUniform = true;
            ImGui::PopID();
        }
        if (attentuation) {
            //draw attenuation properties
            //----------------------------
            ImGui::Text("Attentuation");
            ImGui::SameLine();
            HelpMarker("describe reducing intensity over distance ");

            ImGui::PushID(IDnum++);
            if (ImGui::SliderFloat("linear term", &light.attenuation.linear, 0.0014f, 0.7f))
                changedUniform = true;
            ImGui::PopID();

            ImGui::PushID(IDnum++);
            if (ImGui::SliderFloat("quadratic term", &light.attenuation.quadratic, 0.000007f, 1.8f))
                changedUniform = true;
            ImGui::PopID();
        }
        //---------------------------
    }

    inline static void drawLightProperties(SpotLight &light) {
        const char *name[] = {"light intensity", "ambient intensity", "diffuse intensity", "specular intensity"};
        //color property
        ImGui::PushID(IDnum++);
        if (ImGui::ColorEdit3("light color ", light.light.lightColor))
            changedUniform = true;
        ImGui::PopID();

        //draw the intensity properties
        for (int i = 0; i < 4; i++) {
            ImGui::PushID(IDnum++);
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

        ImGui::PushID(IDnum++);
        if (ImGui::SliderFloat("linear term", &light.light.attenuation.linear, 0.0014f, 0.7f))
            changedUniform = true;
        ImGui::PopID();

        ImGui::PushID(IDnum++);
        if (ImGui::SliderFloat("quadratic term", &light.light.attenuation.quadratic, 0.000007f, 1.8f))
            changedUniform = true;
        ImGui::PopID();
        //---------------------------

    }

   static inline void drawMaterialProperties(Material &material) {
        if (ImGui::SliderFloat("shininess", &material.shininess, 0.001, 128))
            changedUniform = true;

    }

public:
/*================================================
 * ==== static function for drawing the menu======
 * ===============================================
 */
    static inline void drawMenu() {
        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
        ImGui::ShowDemoWindow();
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
                drawLightProperties(pointLight, true);
                ImGui::TreePop();
            }
            //position setting of the lamp
            if (ImGui::TreeNode("position")) {
                ImGui::SliderFloat("radius", &radius, 0, 10);
                ImGui::SliderFloat("speed", &speed, 0, 1);
                ImGui::SliderFloat3("position", lightCenter, -10, 10);
                ImGui::Checkbox("moving", &movingLamp);
                ImGui::TreePop();
            }

        }

        if (ImGui::CollapsingHeader("global lighting"))
            drawLightProperties(dirLight, false);

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
        IDnum = 0;
    }
};
#endif //GLFWTEST_SETTINGS_H