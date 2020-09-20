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
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene ->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() <<std::endl;
    }
    directory = path.substr(0,path.find_last_of(delimiter));
#ifdef DEBUG
    std::cout << scene->mNumMeshes << std::endl;
#endif
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node,  const aiScene *scene) {
    //process all meshes of node

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
    std::vector<Vertex> vertices = std::vector<Vertex>();
    for (unsigned int i=0; i <mesh_arg->mNumVertices ; i++) {
        Vertex vertex =Vertex{glm::vec3(mesh_arg->mVertices[i].x, mesh_arg->mVertices[i].y, mesh_arg->mVertices[i].z),
                              glm::vec3(mesh_arg->mNormals[i].x, mesh_arg->mNormals[i].y, mesh_arg->mNormals[i].z),};
        //check if the mesh has texture coord
        if (mesh_arg->mTextureCoords[0])
            vertex.TexCoords = glm::vec2(mesh_arg->mTextureCoords[0][i].x, mesh_arg->mTextureCoords[0][i].y);
        vertices.push_back(vertex);
    }
    //-----------------------------------

    //convert indices-------------------
    std::vector<unsigned int> indices;
    for (unsigned int i=0; i <mesh_arg->mNumFaces;i++) {
        for (unsigned int j = 0; j < mesh_arg->mFaces[i].mNumIndices; j++)
            indices.push_back(mesh_arg->mFaces[i].mIndices[j]);
    }
    //----------------------------------
    //TODO: just implemented diffuse and specular textures
    std::vector<Texture> textures;
    if (mesh_arg->mMaterialIndex){
        aiMaterial *material = scene->mMaterials[mesh_arg->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures = diffuseMaps;
        //TODO:copying vector to other vector which is O(n)!!!!
        textures.insert(textures.end(),specularMaps.begin(),specularMaps.end());
    }
    return Mesh(vertices,indices,textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName) {
    std::vector<Texture> textures;
    TextureBuilder texturebuilder("");
    texturebuilder.SetYflip(true);
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
#ifdef DEBUG
        std::cout << "loaded texture from " << directory + '/' +str.C_Str() << std::endl;
#endif
        texturebuilder.SetSource(directory + '/' +str.C_Str());
        Texture texture;
        texture.id = texturebuilder.Build();
        texture.type = typeName;
        textures.push_back(texture);
    }
    return textures;
}
