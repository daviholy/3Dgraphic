//
// Created by davih on 27.04.2020.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <cmath>
#include <list>
#include "menu.h"
#include "Shader.h"
#include "Constants.h"
#include "Camera.h"
#include <iostream>
#include "Texture.h"
#include"glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>

#define UNIQ_ID

//headers of functions used in the file
//------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void processInput(GLFWwindow *window);

void drawCubeLights();

//global variables used across functions
//--------------------------------------
Shader lightingshader, LampShader;
float deltaTime = 0.0;
GLuint VBO, LightVAO, textures[2];
float deqree = 0;
float FOV = 45;
Camera camera = Camera(-90, -36, glm::vec3(0.0, 4.0, 3.5));
bool RawInput = false;
glm::vec3 lightPos = glm::vec3(1.2, 0, 2.0);


void (*draw)() = drawCubeLights;

bool hideGui = true;

//TODO: implement the object loader system, for loading more complex objects
/*========================
  polygon data of the cube
  ========================
           position (3) normal vector(3) tex coord.(3)*/
GLfloat cube[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

/*==================================
  positions of centers for the cubes
  ==================================
  */
glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
};

void drawCubeLights() {
    glBindVertexArray(LightVAO);
    glm::mat4 model, projection;
    //setting the current positions to the uniforms
    //---------------------------------------------
    lightingshader.use();
    lightingshader.setVec3("pointLight.position", lightPos.x, lightPos.y, lightPos.z);
    lightingshader.setVec3("spotLight.direction", camera.Front.x, camera.Front.y, camera.Front.z);
    lightingshader.setVec3("spotLight.position", camera.Position.x, camera.Position.y, camera.Position.z);
    lightingshader.setVec3("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);
    projection = glm::perspective(glm::radians(FOV), (float) SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
    lightingshader.setMatrix("view", glm::value_ptr(camera.GetViewMatrix()));
    lightingshader.setMatrix("projection", glm::value_ptr(projection));

    //render the boxes
    //----------------
    for (unsigned int i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        lightingshader.setMatrix("model", glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    // render lamp box
    //-----------------
    LampShader.use();
    LampShader.setMatrix("view", glm::value_ptr(camera.GetViewMatrix()));
    LampShader.setMatrix("projection", glm::value_ptr(projection));
    model = glm::translate(glm::mat4(1.0), lightPos);
    model = glm::scale(model, glm::vec3(0.2f));
    LampShader.setMatrix("model", glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
//old code which is not useful now
// -----------------------------------------------------
/*
void drawCube() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    textureShader.use();
    glm::mat4 model, projection;

    projection = glm::perspective(glm::radians(FOV), (float) SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
    textureShader.setMatrix("view", glm::value_ptr(camera.GetViewMatrix()));
    textureShader.setMatrix("projection", glm::value_ptr(projection));
    glBindVertexArray(VAO);
    for (int i = 0; i < 10; i++) {
        model = glm::translate(glm::mat4(1.0), cubePositions[i]);
        float angle = 20.0f * (float) i;
        if (i % 3 == 0) {
            angle += deqree;
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        } else
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        textureShader.setMatrix("model", glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}*/
inline void setUniforms(){
    lightingshader.use();
    lightingshader.setVec3("material.ambient", material.ambientColors[0], material.ambientColors[1],
                           material.ambientColors[2]);
    lightingshader.setVec3("material.diffuse", material.diffuseColors[0], material.diffuseColors[1],
                           material.ambientColors[2]);
    lightingshader.setVec3("material.specular", material.specularColors[0], material.specularColors[1],
                           material.specularColors[2]);
    lightingshader.setFloat("material.shininess", material.shininess);

    lightingshader.setInt("dirLightSet", setDirectionLight);
    lightingshader.setVec3("dirLight.light.color", dirLight.lightColor[0], dirLight.lightColor[1],
                           dirLight.lightColor[2]);
    lightingshader.setFloat("dirLight.light.ambient", dirLight.intensities[0] * dirLight.intensities[1]);
    lightingshader.setFloat("dirLight.light.diffuse", dirLight.intensities[0] * dirLight.intensities[2]);
    lightingshader.setFloat("dirLight.light.specular", dirLight.intensities[0] * dirLight.intensities[3]);
    lightingshader.setVec3("dirLight.dir", 0.0f, -5.0f, -6.0f);

    lightingshader.setInt("pointLightSet", setPointLight);
    lightingshader.setVec3("pointLight.light.color", pointLight.lightColor[0], pointLight.lightColor[1],
                           pointLight.lightColor[2]);
    lightingshader.setFloat("pointLight.light.ambient", pointLight.intensities[0] * pointLight.intensities[1]);
    lightingshader.setFloat("pointLight.light.diffuse", pointLight.intensities[0] * pointLight.intensities[2]);
    lightingshader.setFloat("pointLight.light.specular", pointLight.intensities[0] * pointLight.intensities[3]);
    lightingshader.setFloat("pointLight.constant", pointLight.attenuation.constant);
    lightingshader.setFloat("pointLight.linear", pointLight.attenuation.linear);
    lightingshader.setFloat("pointLight.quadratic", pointLight.attenuation.quadratic);

    lightingshader.setInt("spotLightSet", setSpotLight);
    lightingshader.setVec3("spotLight.light.color", spotLight.light.lightColor[0],
                           spotLight.light.lightColor[1], spotLight.light.lightColor[2]);
    lightingshader.setFloat("spotLight.light.ambient",
                            spotLight.light.intensities[0] * spotLight.light.intensities[1]);
    lightingshader.setFloat("spotLight.light.diffuse",
                            spotLight.light.intensities[0] * spotLight.light.intensities[2]);
    lightingshader.setFloat("spotLight.light.specular",
                            spotLight.light.intensities[0] * spotLight.light.intensities[3]);
    lightingshader.setFloat("spotLight.constant", spotLight.light.attenuation.constant);
    lightingshader.setFloat("spotLight.linear", spotLight.light.attenuation.linear);
    lightingshader.setFloat("spotLight.quadratic", spotLight.light.attenuation.quadratic);
    lightingshader.setFloat("spotLight.cutOff", glm::cos(glm::radians(spotLight.innerCone)));
    lightingshader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(spotLight.outerCone)));
    lightingshader.setInt("Texture0", 0);
}

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "testProject", nullptr, nullptr);
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
    // Setup Dear ImGui context
    //----------------------------------------
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // create and bind vertex buffer objects(VBO), vertex array Objects(VAO)
    //------------------------------------------
    //generate buffers
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &LightVAO);
    // glGenVertexArrays(1, &VAO);

    // buffer the cube data to VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

    // old unused VAO
    /* glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, nullptr);
    glEnableVertexAttribArray(0);
    //texture coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void *) (6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);*/

    //set the VAO with lighting (normal vectors)
    glBindVertexArray(LightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //1 attribute - vertex positions
    //------------------------------
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, nullptr);
    glEnableVertexAttribArray(0);
    //2 attribute - normal vectors
    //----------------------------
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    //3 attribute - texture coordinates
    //---------------------------------
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void *) (6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    //---------------------------------------------------

    //compile shaders -----------------------------
    try {
        //textureShader = Shader("shaders/textureVertex3D.shader", "shaders/textureFragment3D.shader");
        lightingshader = Shader("shaders/lightingVertex.shader", "shaders/lightingFragment.shader");
        LampShader = Shader("shaders/textureVertex3D.shader", "shaders/lightingLamp.shader");
    }
    catch (std::ifstream::failure &fail) {
        std::cout << fail.what() << std::endl;
        glfwTerminate();
        return -1;
    }

    //---------------------------------------------
    //load textures
    //---------
    TextureBuilder builder("textures/container.jpg");
    try { textures[0] = builder.Build(); }
    catch (std::ios_base::failure &fail) {
        std::cout << fail.what() << std::endl;
        glfwTerminate();
        return -1;
    }
    builder.SetSource("textures/awesomeface.png");
    builder.SetYflip(true);
    builder.SetColorMode(GL_RGBA);
    builder.SetInternalColorMode(GL_RGBA);
    builder.SetRepeat(GL_REPEAT);
    try {
        textures[1] = builder.Build();
    }
    catch (std::ios_base::failure &fail) {
        std::cout << fail.what() << std::endl;
        glfwTerminate();
        return -1;
    }
    //---------
    //activate and bind texture units
    //------------------------------
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    //set the default uniforms for shader
    //----------------------
    //old unused shader
    /*textureShader.use();
    textureShader.setInt("Texture0", 0);
    textureShader.setInt("Texture1", 1);
    textureShader.setFloat("Transparency", 0.3);*/

    //-----------------------------------------------------------------------------------
    //glfw: set the limiter of FPS to the refresh rate of monitor
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
        if (movingLamp) {
            lightPos.x = lightCenter[0] + cos(glfwGetTime() * speed) * radius;
            lightPos.y = lightCenter[1];
            lightPos.z = lightCenter[2] + sin(glfwGetTime() * speed) * radius;
        }
        // input
        // -----
        processInput(window);

        // set the background color and clear the buffer with it
        // -----------------------------------------------------
        glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //change uniforms if it's changed
        //-----------------------------------------
        if (changedUniform) {
            changedUniform = false;
            setUniforms();
        }

        //draw the scene
        //--------------
        draw();
        //draw the GUI
        //------------------
        if (!hideGui) {
            drawMenu();
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved ...)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

void processInput(GLFWwindow *window) {
    // camera control----------------------------------------------------
    if (glfwGetKey(window, GLFW_KEY_W))
        camera.ProccesCameraMovement(Forward, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S))
        camera.ProccesCameraMovement(Backward, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A))
        camera.ProccesCameraMovement(Left, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D))
        camera.ProccesCameraMovement(RightMovement, deltaTime);
    //-------------------------------------------------------------------
    //old already unused actions
    /*
    if (glfwGetKey(window, GLFW_KEY_Q)) {
        deqree += 1;
        std::cout << "Degree: " << deqree << std::endl;
    } else if (glfwGetKey(window, GLFW_KEY_E)) {
        deqree -= 1;
        std::cout << "Degree: " << deqree << std::endl;
    }*/
    if (glfwGetKey(window, GLFW_KEY_KP_7)) {
        FOV -= 1;
        std::cout << "FOV: " << FOV << std::endl;
    } else if (glfwGetKey(window, GLFW_KEY_KP_8)) {
        FOV += 1;
        std::cout << "FOV: " << FOV << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        //closing window
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    //for debug purpose
    if (glfwGetKey(window, GLFW_KEY_P)) {
        std::cout << camera.Yaw << " " << camera.Pitch << std::endl << camera.Position.x << " " << camera.Position.y
                  << " " << camera.Position.z << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_M)) {
        if (hideGui) {
            hideGui = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            //disable camera movement
            glfwSetCursorPosCallback(window, nullptr);
        } else {
            hideGui = true;
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
    camera.ProccesMouseMovement(xPos, yPos);
}

// callback function called  when size of the window change
//---------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}