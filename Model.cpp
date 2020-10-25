//
// Created by davih on 19.09.2020.
//

#include <assimp/Importer.hpp>
#include <iostream>
#include <assimp/postprocess.h>
#include "Model.h"
#include "TextureBuilder.h"
Model::Model(const std::string& path, const std::string &uniformMaterial_arg) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);
    if (!scene || scene ->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() <<std::endl;
    }
    //set the name of the model
    directory_ = path.substr(0, path.find_last_of(delimiter));

#ifdef DEBUG
    std::cout << "number of meshes for model " << path <<':' << scene->mNumMeshes << std::endl;
    unsigned  int total =0;
    for (int i =0; i< scene->mNumMeshes;i++)
        total +=scene->mMeshes[i]->mNumVertices;
    std::cout << "total count of vertices: " << total << std::endl;
#endif

    processNode(scene->mRootNode, scene, uniformMaterial_arg);
}

void Model::processNode(aiNode *node,  const aiScene *scene, const std::string &uniformMaterial_arg) {
    //process all meshes of curent node

    for (unsigned int i=0 ; i <node->mNumMeshes;i++ ){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes_.push_back(convert(mesh, scene, uniformMaterial_arg));
    }

    //procces all other children nodes
    for (unsigned int i = 0; i < node->mNumChildren;i++)
        processNode(node->mChildren[i],scene, uniformMaterial_arg);
}
//todo: implement checking mesh atributes and store the information (texture coords, normals
Mesh Model::convert(aiMesh *mesh_arg,  const aiScene *scene, const std::string &uniformMaterial_arg) {
    //convert vertices-------------------
    bool texture = mesh_arg->HasTextureCoords(0);
    bool tangent = mesh_arg->HasTangentsAndBitangents();
    std::vector<Vertex> vertices;
    vertices.reserve(mesh_arg->mNumVertices);

    for (unsigned int i=0; i <mesh_arg->mNumVertices ; i++) {
        Vertex vertex =Vertex{glm::vec3(mesh_arg->mVertices[i].x, mesh_arg->mVertices[i].y, mesh_arg->mVertices[i].z),
                              glm::vec3(mesh_arg->mNormals[i].x, mesh_arg->mNormals[i].y, mesh_arg->mNormals[i].z),};
        //check if the mesh has texture coord
        //TODO; just loading first channel of UV
        if (texture)
            vertex.TexCoords = glm::vec2(mesh_arg->mTextureCoords[0][i].x, mesh_arg->mTextureCoords[0][i].y);
        if (tangent){
            vertex.tangent = glm::vec3(mesh_arg->mTangents[i].x,mesh_arg->mTangents[i].y,mesh_arg->mTangents[i].z);
            vertex.bitangent = glm::vec3(mesh_arg->mBitangents[i].x,mesh_arg->mBitangents[i].y,mesh_arg->mBitangents[i].z);
        }
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
    //TODO: just implemented diffuse,specular and normals textures
    std::vector<Texture> textures;
    std::vector<std::string> uniforms;
    if (mesh_arg->mMaterialIndex){
        aiMaterial *material = scene->mMaterials[mesh_arg->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::diffuse);
        for (unsigned int i =0 ; i < diffuseMaps.size();i++)
            uniforms.push_back((uniformMaterial_arg + "texture_diffuse").append(std::to_string(i)));
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::specular);
        for (unsigned int i =0 ; i < specularMaps.size();i++)
            uniforms.push_back((uniformMaterial_arg + "texture_specular").append(std::to_string(i)));
        textures = diffuseMaps;
        std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, TextureType::normal);
        for (unsigned int i =0 ; i < normalMaps.size();i++)
            uniforms.push_back(((uniformMaterial_arg + "texture_normal").append(std::to_string(i))));
        //TODO:copying vector to other vector which is O(n)!!!! (it dont have much big impact now, because the number of actual Textures are low)
        textures.insert(textures.end(),specularMaps.begin(),specularMaps.end());
    }
    //------------------------------------

    return Mesh(vertices,indices,textures,uniforms);
}
//TODO: checking loaded textures in model, possible duplicate in another model
std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const TextureType type_arg) {
    std::vector<Texture> textures;
    TextureBuilder texturebuilder("");
    texturebuilder.SetFiltering(GL_LINEAR,GL_NEAREST);
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        bool  skip =false;
        mat->GetTexture(type, i, &str);
        //checking if the texture isn't loaded------------------------
       for(int i =0 ; i < textures_loaded_.size(); i++){
            if (textures_loaded_[i].name == str.C_Str()){
                //found identical texture
                skip = true;
                textures.push_back(textures_loaded_[i]);
                break;
            }
        }
        //------------------------------------------------------------

        //loading the texture if it wasn't found----------------------
        if (!skip) {
            texturebuilder.SetSource(directory_ + '/' + str.C_Str());
            Texture texture;
            texturebuilder.SetYflip(true);
            texturebuilder.SetFiltering(GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_NEAREST);
            texture.id = texturebuilder.Build();
            texture.type = type_arg;
            //TODO: comparing whole given path, isn't comparing names sufficient?
            texture.name = str.C_Str();
            textures.push_back(texture);
            textures_loaded_.push_back(textures[textures.size() - 1]);
            #ifdef DEBUG
            std::cout << "loaded texture from " << directory_ + '/' + str.C_Str() << std::endl;
            #endif
        }
        //-----------------------------------------------------------------
    }
    return textures;
}
