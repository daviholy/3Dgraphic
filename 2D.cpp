#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>
#include <list>
#include <vector>
#include "shader.h"
#include <iostream>
#include<math.h>
#include "Texture.h"
#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
constexpr unsigned int SCR_WIDTH = 1920;
constexpr unsigned int SCR_HEIGHT = 1080;
GLfloat triangle_colors[] = {0.0,1.0,0.0,
                             0.0,0.0,1.0,
                             1.0,0.0,0.0};
GLfloat triangle[] = {-0.5,-0.5,0.0,
                       0.0, 0.5,0.0,
                       0.5,-0.5,0.0};
GLfloat square[] = { 0.5,  0.5,0.0,
                     0.5, -0.5,0.0,
         		    -0.5, -0.5,0.0,
         	    	-0.5,  0.5,0.0
                  };
GLfloat square_colors[] = {1.0,1.0,1.0,
                           1.0,0.0,0.0,
                           0.0,1.0,0.0,
                           0.0,0.0,1.0};
GLuint indices[] = {
        0,1,3, //first triangle
        1,2,3//second triangle
};
GLfloat texCoords[] = {1.0, 1.0,
                       1.0,0.0,
                       0.0,0.0,
                       0.0,1.0};
GLfloat smileTexCoords[] = {2.0, 2.0,
                            2.0,0.0,
                            0.0,0.0,
                            0.0,2.0
};
GLfloat twoTryangles1[] = {-0.5, -0.5, 0.0,
                         -0.25, 0.5, 0.0,
                         0.0, -0.5, 0.0,};
GLfloat twoTryangles2[] ={0.0,-0.5,0.0,
                    0.25,0.5,0.0,
                    0.5,-0.5,0.0
                    };
float scale = 1;
float degree=0;
float transparency =0.2;
glm::vec3 position(0,0,1);

std::list<Shader> shads;
GLuint textures[2];
unsigned int vertexDraws = 6;
int textureWidth,textureHeight,textureNrChannels;
unsigned char *textureData;
Shader redShader ,blueShader,colorfulShader,animatedColorShader,textureShader;
GLuint VBO[4],VAO[4],VBO_colors[2],EBO,textureCoordsBO[2];
unsigned int polygonMode =1;
void drawTriangle(){
    shads.begin()->use();
    glDrawArrays(GL_TRIANGLES, 0, vertexDraws);
}
void drawSquare(){
    shads.begin()->use();
    glm::mat4 trans(1.0);
    trans = glm::translate(trans,position );
    trans = glm::rotate(trans, glm::radians(degree), glm::vec3(0,0,1));
    trans = glm::scale(trans, glm::vec3(scale, scale, scale));
    textureShader.setMatrix("transform",glm::value_ptr(trans));
    textureShader.setFloat("Transparency",transparency);
    glDrawElements(GL_TRIANGLES,vertexDraws,GL_UNSIGNED_INT,nullptr);
}
void drawTwoTriangles (){
    auto shad = shads.begin();
    shad->use();
    glDrawArrays(GL_TRIANGLES, 0, vertexDraws);
    shad++;
    shad->use();
    glBindVertexArray(VAO[3]);
    glDrawArrays(GL_TRIANGLES,0, vertexDraws);
    glBindVertexArray(VAO[2]);
};
void animatedTriangle(){
    shads.begin()->use();
    GLfloat time = glfwGetTime();
    GLfloat greenValue= sin(time)/2.0 +0.5;
    GLfloat redValue = cos(time)/2.0 +0.5;
    GLfloat blueValue= sin(time +1.57)/2.0 +0.5;
    int unifomrLoc = glGetUniformLocation(shads.begin()->ID,"u_RColor");
    if (unifomrLoc == -1)
        std::cout << "cant find uniform location";
    glUniform4f(unifomrLoc,redValue,greenValue,blueValue,1.0);
    glDrawArrays(GL_TRIANGLES,0,vertexDraws);
}
void (*draw)() = drawTriangle;
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "testProject", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // create and bind vertex buffer objects(VBO), vertex array Objects(VAO)
    glGenBuffers(4, VBO);
    glGenBuffers(2,textureCoordsBO);
    glGenVertexArrays(4,VAO);
    glGenBuffers(2,VBO_colors);
    glGenBuffers(1,&EBO);
    //triangle
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle),triangle,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(0);
    //bind color buffer
    glBindBuffer(GL_ARRAY_BUFFER,VBO_colors[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_colors),triangle_colors,GL_STATIC_DRAW);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(1);

    //square VAO with EBO
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square),square,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(0);
    // color buffer
    glBindBuffer(GL_ARRAY_BUFFER,VBO_colors[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(square_colors),square_colors,GL_STATIC_DRAW);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(1);
    //texture coords
    glBindBuffer(GL_ARRAY_BUFFER,textureCoordsBO[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(texCoords),texCoords,GL_STATIC_DRAW);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER,textureCoordsBO[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(smileTexCoords),smileTexCoords,GL_STATIC_DRAW);
    glVertexAttribPointer(3,2,GL_FLOAT,GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(3);
    //element buffer object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW);

    //2 triangles
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(twoTryangles1),twoTryangles1,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(VAO[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(twoTryangles2),twoTryangles2,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0, nullptr);
    glEnableVertexAttribArray(0);


    blueShader = Shader("shaders\\basicVertex.shader","Shaders\\blueFragment.shader");
    colorfulShader = Shader("shaders\\colorfulVertex.shader","Shaders\\colorfulFragment.shader");
    redShader = Shader("shaders\\basicVertex.shader","Shaders\\redFragment.shader");
    animatedColorShader = Shader("shaders\\basicVertex.shader","shaders\\uniformFragment.shader");
    textureShader = Shader("shaders\\textureVertex.shader","shaders\\textureFragment.shader");
     shads ={colorfulShader};
    //load textures
    //---------
    TextureBuilder builder ("..\\textures\\container.jpg");
    textures[0] = builder.Build();
    builder.SetSource("..\\textures\\awesomeface.png");
    builder.SetYflip(true);
    builder.SetColorMode(GL_RGBA);
    builder.SetRepeat(GL_MIRRORED_REPEAT);
    textures[1] = builder.Build();
    //---------

    //set uniforms for textureShader
    textureShader.use();
    textureShader.setInt("Texture0",0);
    textureShader.setInt("Texture1",1);
    //--------
    glfwSwapInterval(1);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
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
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    //draw a square
    else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        vertexDraws = 6;
        glBindVertexArray(VAO[1]);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        draw =drawSquare;
        shads = {textureShader};
    }
    //draw a triangle
    else if (glfwGetKey(window, GLFW_KEY_2)) {
        vertexDraws = 3;
        glBindVertexArray(VAO[0]);
        draw = drawTriangle;
        shads = {colorfulShader};
    }
    //draw 2 triangles
    else if (glfwGetKey(window, GLFW_KEY_3)){
        vertexDraws = 3;
        glBindVertexArray(VAO[2]);
        shads = {redShader, blueShader};
        draw = drawTwoTriangles;
    }
    else if (glfwGetKey(window, GLFW_KEY_4)) {
        if (polygonMode == 1) {
            polygonMode = 0;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            std::this_thread::sleep_for(std::chrono::milliseconds(120));
        }
        else{
            polygonMode =1;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            std::this_thread::sleep_for(std::chrono::milliseconds(120));
        }
    }
    else if (glfwGetKey(window, GLFW_KEY_5)){
        vertexDraws= 3;
        glBindVertexArray(VAO[0]);
        shads = {animatedColorShader};
        draw = animatedTriangle;
    }

     if (glfwGetKey(window, GLFW_KEY_UP) && transparency < 1.0)
        transparency += 0.01;

     if (glfwGetKey(window, GLFW_KEY_DOWN) && transparency > 0.0){
        transparency -= 0.01;
    }
     if (glfwGetKey(window,GLFW_KEY_A) && position.x > -1.0)
        position.x -= 0.01;
     if (glfwGetKey(window,GLFW_KEY_D) && position.x < 1.0)
        position.x += 0.01;
     if (glfwGetKey(window,GLFW_KEY_W) && position.y < 1.0)
         position.y +=0.01;
    if (glfwGetKey(window,GLFW_KEY_S) && position.y > -1.0)
        position.y -= 0.01;
    if (glfwGetKey(window,GLFW_KEY_Q))
        degree -= 1;
    if (glfwGetKey(window,GLFW_KEY_E))
        degree +=1;
    if (glfwGetKey(window,GLFW_KEY_LEFT))
        scale -= 0.01;
    if (glfwGetKey(window,GLFW_KEY_RIGHT))
        scale += 0.01;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}