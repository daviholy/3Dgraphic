//
// Created by davih on 27.04.2020.
//
/*todo: things to add:
 *semi transparent objects
 * animation system
 * multiple lamps
 * static camera
 * culling
 * perlin noise
 */
/*FIXME: bugs:
 * can't move lamp when it's stopped
 */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <cmath>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include "settings.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Object.h"
#include "Scene.h"

//headers of functions used in the file
//------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void processInput(GLFWwindow *window, Scene &scene);

void drawCubeLights(Scene &scene, Shader &shader);

#ifdef DEBUG
//debug message function for opengl
void APIENTRY glDebugOutput(GLenum source,GLenum type,unsigned int id,GLenum severity,GLsizei length,const char*message,const void*userParam) {
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;
    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;
    switch (source) {
        case GL_DEBUG_SOURCE_API:
            std::cout << "Source: API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            std::cout << "Source: Window System";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            std::cout << "Source: Shader Compiler";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            std::cout << "Source: Third Party";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            std::cout << "Source: Application";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            std::cout << "Source: Other";
            break;
    }
    std::cout << std::endl;
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            std::cout << "Type: Error";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            std::cout << "Type: Deprecated Behaviour";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cout << "Type: Undefined Behaviour";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            std::cout << "Type: Portability";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cout << "Type: Performance";
            break;
        case GL_DEBUG_TYPE_MARKER:
            std::cout << "Type: Marker";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            std::cout << "Type: Push Group";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            std::cout << "Type: Pop Group";
            break;
        case GL_DEBUG_TYPE_OTHER:
            std::cout << "Type: Other";
            break;
    }
    std::cout << std::endl;
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            std::cout << "Severity: high";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << "Severity: medium";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            std::cout << "Severity: low";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            std::cout << "Severity: notification";
            break;
    }
    std::cout << std::endl;
    std::cout << "Message: " << message << std::endl;
    std::cout << std::endl;
}
#endif

//global variables used across functions
//--------------------------------------
float deltaTime = 0.0;
float deqree = 0;
bool RawInput = false;
glm::vec3 lightPos = glm::vec3(1.2, 0, 2.0);
std::shared_ptr<Camera> activeCamera ;
//for saving cursor position
double xPos,yPos;
void (*draw) (Scene&, Shader &shader) = drawCubeLights;

void drawCubeLights(Scene &scene_arg, Shader &shader) {
    glm::mat4 model(1.0f), projection = glm::perspective(glm::radians(settings::FOV), (float) settings::scrWidth / settings::scrHeight, 0.1f, 100.0f);
    //setting the current positions to the uniforms
    //---------------------------------------------
    shader.use();
   // shader.setVec3("pointLight.position", lightPos.x, lightPos.y, lightPos.z);
    shader.setVec3("spotLight.direction", scene_arg.activeCamera->Front.x, scene_arg.activeCamera->Front.y, scene_arg.activeCamera->Front.z);
    shader.setVec3("spotLight.position", scene_arg.activeCamera->Position.x, scene_arg.activeCamera->Position.y, scene_arg.activeCamera->Position.z);
    shader.setVec3("viewPos", scene_arg.activeCamera->Position.x, scene_arg.activeCamera->Position.y, scene_arg.activeCamera->Position.z);
    model = glm::scale(model,glm::vec3(1.0,1.0,1.0));
    scene_arg.draw();
    // render lamp
    //-----------------
   /* LampShader.use();
    LampShader.setMatrix("view", glm::value_ptr(scene_arg.activeCamera->GetViewMatrix()));
    LampShader.setMatrix("projection", glm::value_ptr(projection));
    model = glm::scale(model, glm::vec3(0.2f));
    model = glm::translate(glm::mat4(1.0), lightPos);
    LampShader.setMatrix("model", glm::value_ptr(model));
    LampShader.setVec3("lightColor", settings::pointLight.lightColor[0],settings::pointLight.lightColor[1],
                       settings::pointLight.lightColor[2]);
    lamp.Draw(LampShader,"");*/
}

inline void setUniforms(Shader &shader){
    //TODO: implement better uniform class then this hardcoded crap?
    shader.use();
    shader.setFloat("material.shininess", settings::material.shininess);
    shader.setInt("dirLightSet", settings::setDirectionLight);
    shader.setVec3("dirLight.light.color", settings::dirLight.lightColor[0], settings::dirLight.lightColor[1],
                    settings::dirLight.lightColor[2]);
    shader.setFloat("dirLight.light.ambient", settings::dirLight.intensities[0] * settings::dirLight.intensities[1]);
    shader.setFloat("dirLight.light.diffuse", settings::dirLight.intensities[0] * settings::dirLight.intensities[2]);
    shader.setFloat("dirLight.light.specular", settings::dirLight.intensities[0] * settings::dirLight.intensities[3]);
    shader.setVec3("dirLight.dir", 0.0f, -5.0f, -6.0f);

    shader.setInt("pointLightSet", settings::setPointLight);
    shader.setVec3("pointLight.light.color", settings::pointLight.lightColor[0], settings::pointLight.lightColor[1],
         settings::pointLight.lightColor[2]);
    shader.setFloat("pointLight.light.ambient", settings::pointLight.intensities[0] * settings::pointLight.intensities[1]);
    shader.setFloat("pointLight.light.diffuse", settings::pointLight.intensities[0] * settings::pointLight.intensities[2]);
    shader.setFloat("pointLight.light.specular", settings::pointLight.intensities[0] * settings::pointLight.intensities[3]);
    shader.setFloat("pointLight.constant", settings::pointLight.attenuation.constant);
    shader.setFloat("pointLight.linear", settings::pointLight.attenuation.linear);
    shader.setFloat("pointLight.quadratic", settings::pointLight.attenuation.quadratic);

    shader.setInt("spotLightSet", settings::setSpotLight);
    shader.setVec3("spotLight.light.color", settings::spotLight.light.lightColor[0],
                           settings::spotLight.light.lightColor[1], settings::spotLight.light.lightColor[2]);
    shader.setFloat("spotLight.light.ambient",
                            settings::spotLight.light.intensities[0] * settings::spotLight.light.intensities[1]);
    shader.setFloat("spotLight.light.diffuse",
                            settings::spotLight.light.intensities[0] * settings::spotLight.light.intensities[2]);
    shader.setFloat("spotLight.light.specular",
                            settings::spotLight.light.intensities[0] * settings::spotLight.light.intensities[3]);
    shader.setFloat("spotLight.constant", settings::spotLight.light.attenuation.constant);
    shader.setFloat("spotLight.linear", settings::spotLight.light.attenuation.linear);
    shader.setFloat("spotLight.quadratic", settings::spotLight.light.attenuation.quadratic);
    shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(settings::spotLight.innerCone)));
    shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(settings::spotLight.outerCone)));
}

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfw window creation
    // --------------------
    //getting the actual primary monitor resolution
    const GLFWvidmode* monitor = glfwGetVideoMode(glfwGetPrimaryMonitor());
    settings::scrWidth = monitor->width;
    settings::scrHeight = monitor->height;

    GLFWwindow *window = glfwCreateWindow(settings::scrWidth, settings::scrHeight, "testProject", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //check and set raw input if its available
    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        RawInput = true;
    }
    //disable the cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_callback);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    //enable debug output log in opengl---------
#ifdef DEBUG
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT){
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0,nullptr, GL_TRUE);
    }
    //-----------------------------------------
#endif
    // Setup Dear ImGui context
    //----------------------------------------
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    std::shared_ptr<Shader> modelShader;
    //compile shaders -----------------------------
    try {
       // LampShader = Shader("shaders/textureVertex3D.shader", "shaders/lightingLamp.shader");
        modelShader = std::make_shared<Shader>("shaders/modelVertex.shader","shaders/modelFragment.shader" );
    }
    catch (std::ifstream::failure &fail) {
        std::cout << fail.what() << std::endl;
        glfwTerminate();
        return -1;
    }
    //-----------------------------------------------------------------------------------
    //setting camera
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(-90, -36, glm::vec3(0.0, 4.0, 3.5));
    activeCamera = camera;
    //loading objects
   std::shared_ptr<Object> object = std::make_shared<Object>("models/survival Backpack/backpack.obj", modelShader);
    //lamp = Model ("models/sphere.obj");
    //loading scene with single object
    Scene scene (camera);
    scene.addObject(object);
    for (float i = 1 ; i < 1 ; i++)
    scene.addObject(std::make_shared<Object>(object->model,modelShader,glm::vec3 (4 * i,0.0f,0.0f)));
    //glfw: set the limiter of FPS to the refresh rate of monitor ( v-sinc)
    glfwSwapInterval(1);
    //enable Z Buffer
    glEnable(GL_DEPTH_TEST);
    float lastFrame = 0.0F;
    // render loop
    // ---------------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window)) {
        // calculate time logic
        //--------------------
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //calculate position of the lamp
        //------------------------------
        if (settings::movingLamp) {
            lightPos.x = settings::lightCenter[0] + cos(glfwGetTime() * settings::speed) * settings::radius;
            lightPos.y = settings::lightCenter[1];
            lightPos.z = settings::lightCenter[2] + sin(glfwGetTime() * settings::speed) * settings::radius;
        }
        // input
        // -----
        processInput(window,scene);

        // set the background color and clear the buffer with it
        // -----------------------------------------------------
        glClearColor(settings::backgroundColor[0], settings::backgroundColor[1], settings::backgroundColor[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //change uniforms if it's not changed
        //-----------------------------------------
        if (settings::changedUniform) {
            settings::changedUniform = false;
            setUniforms(*modelShader);
        }

        //draw the scene
        //--------------
        draw(scene, *modelShader);

        //draw the GUI
        //------------------
        if (!settings::hideGui) {
            settings::drawMenu();
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved ...)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        //FIXME:rendering work but giving GL_INVALID_OPERATION, why?
       /* if (glGetError() == GL_INVALID_OPERATION) {
            std::cout << "some error in drawing mesh" << std::endl;
        }*/
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

void processInput(GLFWwindow *window, Scene &scene) {
    //TODO: implement better input system then naively putting thread to sleep

    // camera control----------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_W))
        scene.activeCamera->ProccesCameraMovement(Forward, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S))
        scene.activeCamera->ProccesCameraMovement(Backward, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A))
        scene.activeCamera->ProccesCameraMovement(Left, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D))
        scene.activeCamera->ProccesCameraMovement(RightMovement, deltaTime);
    //-------------------------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        //closing window
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    //for debug purpose
    if (glfwGetKey(window, GLFW_KEY_P)) {
        std::cout << scene.activeCamera->Yaw << " " << scene.activeCamera->Pitch << std::endl << scene.activeCamera->Position.x << " " << scene.activeCamera->Position.y
                  << " " << scene.activeCamera->Position.z << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_M)) {
        if (settings::hideGui) {
            settings::hideGui = false;
            glfwGetCursorPos(window, &xPos, &yPos);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            //disable camera movement
            glfwSetCursorPosCallback(window, nullptr);
        } else {
            settings::hideGui = true;
            glfwSetCursorPos(window,xPos,yPos);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            //enable camera movement
            glfwSetCursorPosCallback(window, mouse_callback);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }
}

// callback function called  when the mouse position change
//---------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xPos, double yPos) {
    activeCamera->ProccesMouseMovement(xPos, yPos);
}

// callback function called  when size of the window change
//---------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}