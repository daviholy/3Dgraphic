//
// Created by davih on 18.09.2020.
//

#include <iostream>
#include <assimp/scene.h>
#include "Mesh.h"
#include<charconv>

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
glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*) nullptr);
//normal
glEnableVertexAttribArray(1);
glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)offsetof(Vertex, Normal));
//texture coordinate
glEnableVertexAttribArray(2);
glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)offsetof(Vertex, TexCoords));
//tangent vector
glEnableVertexAttribArray(3);
glVertexAttribPointer(3,3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)offsetof(Vertex, tangent));
//bitangent vector
glEnableVertexAttribArray(4);
glVertexAttribPointer(4,2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)offsetof(Vertex, bitangent));
//-------------------------------------

glBindVertexArray(0);
}
void Mesh::Draw(const Shader &shader) {
//using uniform naming conventions UniformMaterial.{type}{nr} nr= 0, 1, 2......
//setting texture units---------------
for (int i=0; i <textures.size();i++){
    //activate texture unit
    glActiveTexture(GL_TEXTURE0 + i);
    shader.setFloat  (uniforms[i], i);
    glBindTexture(GL_TEXTURE_2D, textures[i].id);
}
//--------------------------------------

glActiveTexture(GL_TEXTURE0);

//draw the mesh
glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr) ;
glBindVertexArray(0);
}




