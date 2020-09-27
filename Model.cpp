//
// Created by davih on 19.09.2020.
//

#include <assimp/Importer.hpp>
#include <iostream>
#include <assimp/postprocess.h>
#include "Model.h"
#include "TextureBuilder.h"
Model::Model(std::string path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate );
    if (!scene || scene ->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() <<std::endl;
    }
    //set the name of the model
    directory = path.substr(0,path.find_last_of(delimiter));
#ifdef DEBUG
    std::cout << "number of meshes for model " << path <<':' << scene->mNumMeshes << std::endl;
    unsigned  int total =0;
    for (int i =0; i< scene->mNumMeshes;i++)
        total +=scene->mMeshes[i]->mNumVertices;
    std::cout << "total count of vertices: " << total << std::endl;
#endif
    processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode *node,  const aiScene *scene) {
    //process all meshes of curent node

    for (unsigned int i=0 ; i <node->mNumMeshes;i++ ){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(convert(mesh,  scene));
    }

    //procces all other children nodes
    for (unsigned int i = 0; i < node->mNumChildren;i++)
        processNode(node->mChildren[i],scene);
}

Mesh Model::convert(aiMesh *mesh_arg,  const aiScene *scene) {
    //convert vertices-------------------
    bool texture = mesh_arg->mTextureCoords[0];
    std::vector<Vertex> vertices;
    vertices.reserve(mesh_arg->mNumVertices);

    for (unsigned int i=0; i <mesh_arg->mNumVertices ; i++) {
        Vertex vertex =Vertex{glm::vec3(mesh_arg->mVertices[i].x, mesh_arg->mVertices[i].y, mesh_arg->mVertices[i].z),
                              glm::vec3(mesh_arg->mNormals[i].x, mesh_arg->mNormals[i].y, mesh_arg->mNormals[i].z),};
        //check if the mesh has texture coord
        if (texture)
            vertex.TexCoords = glm::vec2(mesh_arg->mTextureCoords[0][i].x, mesh_arg->mTextureCoords[0][i].y);
        vertices.push_back(vertex);
    }
    //-----------------------------------

    //convert indices-------------------
    std::vector<unsigned int> indices;
    //TODO: just true for triangulated objects
    indices.reserve(mesh_arg->mNumFaces *3);
    for (unsigned int i=0; i <mesh_arg->mNumFaces;i++) {
        for (unsigned int j = 0; j < mesh_arg->mFaces[i].mNumIndices; j++)
            indices.push_back(mesh_arg->mFaces[i].mIndices[j]);
    }
    //----------------------------------

    //convert textures-------------------
    //TODO: just implemented diffuse and specular textures
    std::vector<std::shared_ptr<Texture>> textures;
    if (mesh_arg->mMaterialIndex){
        aiMaterial *material = scene->mMaterials[mesh_arg->mMaterialIndex];
        std::vector<std::shared_ptr<Texture>> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        std::vector<std::shared_ptr<Texture>> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures = diffuseMaps;
        //TODO:copying vector to other vector which is O(n)!!!! (it dont have much big impact now, because the number of actual Textures are low)
        textures.insert(textures.end(),specularMaps.begin(),specularMaps.end());
    }
    //------------------------------------
    return Mesh(vertices,indices,textures);
}

std::vector<std::shared_ptr<Texture>> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName) {
    std::vector<std::shared_ptr<Texture>> textures;
    TextureBuilder texturebuilder("");
    texturebuilder.SetFiltering(GL_LINEAR,GL_NEAREST);
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        bool  skip =false;
        mat->GetTexture(type, i, &str);
        //checking if the texture isn't loaded------------------------
       for(int i =0 ; i < textures_loaded.size();i++){
            if (textures_loaded[i]->name == str.C_Str()){
                //found identical texture
                skip = true;
                textures.push_back(textures_loaded[i]);
                break;
            }
        }
        //------------------------------------------------------------

        //loading the texture if it wasn't found----------------------
        if (!skip) {
            texturebuilder.SetSource(directory + '/' + str.C_Str());
            Texture texture;
            texture.id = texturebuilder.Build();
            texture.type = typeName;
            //TODO: comparing whole given path, isn't comparing names sufficient?
            texture.name = str.C_Str();
            textures.push_back(std::make_shared<Texture>(texture));
            textures_loaded.push_back(textures[textures.size() - 1]);
            #ifdef DEBUG
            std::cout << "loaded texture from " << directory + '/' + str.C_Str() << std::endl;
            #endif
        }
        //-----------------------------------------------------------------
    }
    return textures;
}
