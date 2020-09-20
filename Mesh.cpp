//
// Created by davih on 18.09.2020.
//

#include <assimp/material.h>
#include <iostream>
#include <assimp/scene.h>
#include "Mesh.h"

 void Mesh::setupMesh() {
//make the VAO, EBO buffers----------
glGenVertexArrays(1,&VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);
//-----------------------------------

//buffer data into  the buffers------
glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);

glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
//-----------------------------------

//set attribute pointers in VAO------
//vertex positions
glEnableVertexAttribArray(0);
glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)0);
//normal
glEnableVertexAttribArray(1);
glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)offsetof(Vertex, Normal));
//texture coordinate
glEnableVertexAttribArray(2);
glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)offsetof(Vertex, TexCoords));
//-------------------------------------

glBindVertexArray(0);
}
void Mesh::Draw(Shader &shader) {
//using uniform naming conventions {type}{nr} nr= 0, 1, 2......
unsigned int diffuseNr = 0;
unsigned int specularNr =0;
//setting texture units---------------
/*for (int i=0; i <textures.size();i++){
    //activate texture unit
    glActiveTexture(GL_TEXTURE0 + i);
    std::string name = textures[i].type;
    std::string number;
    if (name == "texture_diffuse")
        number = std::to_string(diffuseNr++);
    else
        number = std::to_string(specularNr++);
    shader.setFloat("material." + name + number, i);
    glBindTexture(GL_TEXTURE0, textures[i].id);
}*/
//--------------------------------------

glActiveTexture(GL_TEXTURE0);

//draw the mesh
glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
glBindVertexArray(0);
}




