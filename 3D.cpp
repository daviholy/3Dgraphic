//
// Created by davih on 27.04.2020.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <math.h>
#include <list>
#include "Shader.h"
#include "Constants.h"
#include "Camera.h"
#include <iostream>
#include "Texture.h"
#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <random>
#include <fstream>

std::minstd_rand engine(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_real_distribution<float> dist (-0.5f,0.5f);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);
//           position              normal vector     tex coord.
GLfloat cube[] = {
        -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,    0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,    0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,      1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,      1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,      1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,      1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,      1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,      1.0f,  0.0f,  0.0f,    1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,    0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,    0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f, 0.0f, 0.0f),
        glm::vec3( 2.0f, 5.0f,-15.0f),
        glm::vec3(-1.5f,-2.2f,-2.5f),
        glm::vec3(-3.8f,-2.0f,-12.3f),
        glm::vec3( 2.4f,-0.4f,-3.5f),
        glm::vec3(-1.7f, 3.0f,-7.5f),
        glm::vec3( 1.3f,-2.0f,-2.5f),
        glm::vec3( 1.5f, 2.0f,-2.5f),
        glm::vec3( 1.5f, 0.2f,-1.5f),
        glm::vec3(-1.3f, 1.0f,-1.5f)
};

Shader textureShader,lightningShader,LampShader;

float deltaTime =0.0;
float lastFrame = 0.0F;
GLuint VBO, VAO,LightVAO, textures[2];
float deqree =0;
float FOV= 45 ;
Camera camera = Camera(-40,-40);
bool RawInput = false;
glm::vec3 lightPos = glm::vec3 (1.2,0,2.0);

void drawCubeLights(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(LightVAO);
    glm::mat4 model, projection;
    lightningShader.use();
    lightningShader.setVec3("light.position",lightPos.x,lightPos.y,lightPos.z);
    lightningShader.setVec3("viewPos",camera.Position.x,camera.Position.y,camera.Position.z);
    projection = glm::perspective(glm::radians(FOV), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f,100.0f);
    lightningShader.setMatrix("view",glm::value_ptr(camera.GetViewMatrix()));
    lightningShader.setMatrix("projection",glm::value_ptr(projection));

    model = glm::translate(glm::mat4(1.0),cubePositions[0]);
    lightningShader.setMatrix("model",glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES,0,36);
    // render lamp box
    LampShader.use();
    LampShader.setMatrix("view",glm::value_ptr(camera.GetViewMatrix()));
    LampShader.setMatrix("projection",glm::value_ptr(projection));
    model = glm::translate(glm::mat4(1.0),lightPos);
    model = glm::scale(model,glm::vec3(0.2f));
    LampShader.setMatrix("model",glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES,0,36);
}

void drawCube() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    textureShader.use();
    glm::mat4 model, projection;

    projection = glm::perspective(glm::radians(FOV), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f,100.0f);
    textureShader.setMatrix("view",glm::value_ptr(camera.GetViewMatrix()));
    textureShader.setMatrix("projection",glm::value_ptr(projection));
    glBindVertexArray(VAO);
    for (int i =0; i <10;i++){
        model = glm::translate(glm::mat4(1.0),cubePositions[i]);
        float angle = 20.0f * (float)i;
        if (i % 3 == 0) {
            angle += deqree;
            model = glm::scale(model,glm::vec3(1.0f,1.0f,1.0f));
        }
        else
            model = glm::scale(model,glm::vec3(1.0f,1.0f,1.0f));
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f,0.3f,0.5f));
        textureShader.setMatrix("model",glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES,0,36);
    }
}
void (*draw)() = drawCube;
int main() {
    Shader shader;
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

    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window,mouse_callback);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }
    // create and bind vertex buffer objects(VBO), vertex array Objects(VAO)
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    //bind VAO with EBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, nullptr);
    glEnableVertexAttribArray(0);
    //texture coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8,(void *) (6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    //set the light VAO
    glGenVertexArrays(1,&LightVAO);
    glBindVertexArray(LightVAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void *) ( 3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void *) ( 6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    //compile shaders -----------------------------
    try{
        textureShader = Shader("shaders/textureVertex3D.shader", "shaders/textureFragment3D.shader");
        lightningShader = Shader("shaders/lightingVertex.shader","shaders/lightingFragment.shader");
        LampShader = Shader("shaders/textureVertex3D.shader","shaders/lightingLamp.shader");
    }
catch (std::ifstream::failure& fail) {
    std::cout << fail.what() << std::endl;
    glfwTerminate();
    return -1;
}

    //---------------------------------------------
    //load textures
    //---------
    TextureBuilder builder("textures/container.jpg");
    try
    {textures[0] = builder.Build();}
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
    try{
    textures[1] = builder.Build();}
    catch (std::ios_base::failure &fail) {
        std::cout << fail.what() << std::endl;
        glfwTerminate();
        return -1;
    }
    //---------
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    //set uniforms
    textureShader.use();
    textureShader.setInt("Texture0", 0);
    textureShader.setInt("Texture1", 1);
    textureShader.setFloat("Transparency", 0.3);
    lightningShader.use();
    lightningShader.setVec3("material.ambient",0.78431f,0.549,0.2745f);
    lightningShader.setVec3("material.diffuse",0.78431f,0.549f,0.2745f);
    lightningShader.setVec3("material.specular",0.78431f,0.6666f,0.2352f);
    lightningShader.setFloat("material.shininess", 1.0f);
    lightningShader.setVec3("light.position",lightPos.x,lightPos.y,lightPos.z);
    lightningShader.setVec3("light.color",1.0f,1.0f,1.0f);
    lightningShader.setVec3("light.ambient",0.4f,0.4f,0.4f);
    lightningShader.setVec3("light.diffuse",0.5f,0.5f,0.5f);
    lightningShader.setVec3("light.specular",1.0f,1.0f,1.0f);
    lightningShader.setInt("Texture0", 0);
    //--------
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    // render loop
    // ---------------------------------------------------------------------------------------
    while (!glfwWindowShouldClose(window)) {
        // calculate deltatime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        lightPos.x = cos(glfwGetTime()) * 4.0f;
        lightPos.z = sin(glfwGetTime()) * 4.0f;
        //
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //draw a triangle

        draw();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
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
    if (glfwGetKey(window,GLFW_KEY_W))
       camera.ProccesCameraMovement(Forward, deltaTime);
     if (glfwGetKey(window,GLFW_KEY_S))
         camera.ProccesCameraMovement(Backward, deltaTime);
     if (glfwGetKey(window,GLFW_KEY_A))
         camera.ProccesCameraMovement(Left, deltaTime);
    if (glfwGetKey(window,GLFW_KEY_D))
        camera.ProccesCameraMovement(RightMovement, deltaTime);
    if (glfwGetKey(window,GLFW_KEY_1))
        draw = drawCube;
    if (glfwGetKey(window,GLFW_KEY_2))
        draw = drawCubeLights;
    //-------------------------------------------------------------------
    if (glfwGetKey(window,GLFW_KEY_Q)) {
        deqree += 1;
        std::cout <<"Degree: " << deqree << std::endl;
    }
    else if (glfwGetKey(window,GLFW_KEY_E)) {
        deqree -= 1;
        std::cout <<"Degree: " << deqree << std::endl;
    }
    else if (glfwGetKey(window,GLFW_KEY_KP_7)) {
        FOV -=1;
        std::cout << "FOV: " << FOV << std::endl;
    }
    else if (glfwGetKey(window,GLFW_KEY_KP_8)) {
        FOV +=1;
        std::cout << "FOV: " << FOV << std::endl;
    }
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos){
    camera.ProccesMouseMovement(xPos,yPos);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}