//
// Created by davih on 27.04.2020.
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <list>
#include <vector>
#include "Shader.h"
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

void processInput(GLFWwindow *window);
GLfloat cube[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f + dist(engine),  0.0f + dist(engine),  0.0f),
        glm::vec3( 2.0f + dist(engine),  5.0f + dist(engine), -15.0f),
        glm::vec3(-1.5f + dist(engine), -2.2f + dist(engine), -2.5f),
        glm::vec3(-3.8f + dist(engine), -2.0f + dist(engine), -12.3f),
        glm::vec3( 2.4f + dist(engine), -0.4f + dist(engine), -3.5f),
        glm::vec3(-1.7f + dist(engine),  3.0f + dist(engine), -7.5f),
        glm::vec3( 1.3f + dist(engine), -2.0f + dist(engine), -2.5f),
        glm::vec3( 1.5f + dist(engine),  2.0f + dist(engine), -2.5f),
        glm::vec3( 1.5f + dist(engine),  0.2f + dist(engine), -1.5f),
        glm::vec3(-1.3f + dist(engine),  1.0f + dist(engine), -1.5f)
};
Shader textureShader;
constexpr unsigned int SCR_WIDTH = 1920;
constexpr unsigned int SCR_HEIGHT = 1080;
GLuint VBO, VAO, textures[2];
float deqree =0;
float FOV= 45 ;
void drawCube() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    textureShader.use();
    glm::mat4 model, view(1.0), projection(1.0);
    // view model matrix-----
    float radius = 20.0f;
    float camX = sin(glfwGetTime()/2) * radius;
    float camZ = cos(glfwGetTime()/2) * radius;
    view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //------
    projection = glm::perspective(glm::radians(FOV), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f,100.0f);
    textureShader.setMatrix("view",glm::value_ptr(view));
    textureShader.setMatrix("projection",glm::value_ptr(projection));

    for (int i =0; i <10;i++){
        model = glm::translate(glm::mat4(1.0),cubePositions[i]);
        float angle = 20.0f * (float)i;
        if (i % 3 == 0) {
            angle += deqree;
            model = glm::scale(model,glm::vec3(1.5f,1.5f,1.5f));
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
    //square VAO with EBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, nullptr);
    glEnableVertexAttribArray(0);
    //texture coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5,(void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
try
{textureShader = Shader("shaders/textureVertex3D.shader", "shaders/textureFragment3D.shader");}
catch (std::ifstream::failure& fail) {
    std::cout << fail.what() << std::endl;
    glfwTerminate();
    return -1;
}
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

    //set uniforms for textureShader
    textureShader.use();
    textureShader.setInt("Texture0", 0);
    textureShader.setInt("Texture1", 1);
    textureShader.setFloat("Transparency", 0.3);
    //--------
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
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

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}