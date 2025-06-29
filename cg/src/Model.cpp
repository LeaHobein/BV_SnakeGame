#include <stb_image/stb_image.h>

#include "Model.h"

/**
 *  C++ class holding model loading parameters models (e.g. Standford bunny).
 *  See https://learnopengl.com/Model-Loading/Assimp for a tutorial
 *  @author Merijam Gotzes
 *  @version 12.04.2024, 19.04.2024, 02.05.2024
 */


    Model::Model() = default;

    Model::~Model() = default;

    void Model::loadModel(const string& filename){

        Assimp::Importer Importer;
        const aiScene* scene = Importer.ReadFile(filename.c_str(),  aiProcess_Triangulate | aiProcess_GenSmoothNormals| aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

        if (!scene)
            cout << "Error loading the model file." << endl;

        // retrieve the directory path of the filepath
        directory = filename.substr(0, filename.find_last_of('/'));
        parseNode(scene->mRootNode, scene);

    }

    void Model::parseNode(aiNode* node, const aiScene* PScene){

        for(size_t i = 0; i < node->mNumMeshes; i++)
            meshes.push_back(parseMesh(PScene->mMeshes[node->mMeshes[i]], PScene));

        for(size_t i = 0; i < node->mNumChildren; i++)
            parseNode(node->mChildren[i], PScene);

    }

    Mesh Model::parseMesh(aiMesh* PMesh, const aiScene* PScene) {
        vector<vertex> vertices;
        vector<GLuint> indices;
        vector<texture> textures;

        //process vertex attributes position, normals and texture coordinates
        for (size_t i = 0; i < PMesh->mNumVertices; i++)
        {
            vertex vert{};

            glm::vec3 pos;
            pos.x = PMesh->mVertices[i].x;
            pos.y = PMesh->mVertices[i].y;
            pos.z = PMesh->mVertices[i].z;
            vert.position = pos;

            glm::vec3 norm;
            norm.x = PMesh->mNormals[i].x;
            norm.y = PMesh->mNormals[i].y;
            norm.z = PMesh->mNormals[i].z;
            vert.normal = norm;

            if(PMesh->mTextureCoords[0]){
                glm::vec2 tex;
                tex.x = PMesh->mTextureCoords[0][i].x;
                tex.y = PMesh->mTextureCoords[0][i].y;
                vert.texcoords = tex;
            }
            else vert.texcoords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vert);
        }

        // process indices
        for (size_t i = 0; i < PMesh->mNumFaces; i++)
        {
            aiFace PFace = PMesh->mFaces[i];
            for (size_t j = 0; j < PFace.mNumIndices; j++)
                indices.push_back((GLuint) PFace.mIndices[j]);
        }

       // process material / textures
       if(PMesh->mMaterialIndex>=0){
           aiMaterial *mat = PScene -> mMaterials[PMesh->mMaterialIndex];
           vector<texture> diffuse = loadMaterialsTextures(mat, aiTextureType_DIFFUSE, "diffuse_texture");
           textures.insert(textures.end(), diffuse.begin(), diffuse.end());
           vector<texture> specular = loadMaterialsTextures(mat, aiTextureType_SPECULAR, "specular_texture");
           textures.insert(textures.end(), specular.begin(), specular.end());
       }

        return {vertices, indices, textures};
    }

    vector<texture> Model::loadMaterialsTextures(aiMaterial *mat, aiTextureType type, string typname)
    {
        vector<texture> textures;

        for(unsigned int i = 0; i < mat->GetTextureCount(type); i++){

            aiString strng;
            mat->GetTexture(type, i, &strng);
            texture tex;
            tex.id = LoadTexFromFile(this->directory, strng.C_Str());
            tex.type = typname;
            tex.path = strng.C_Str();
            textures.push_back(tex);
        }

        return textures;
    }

    GLuint Model::LoadTexFromFile(const string &directory, const char *path)
{
    string filename = string(path);
    filename = directory + '/' + filename;

    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, numberComps;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &numberComps, 0);
    if (data)
    {
        GLenum format;
        if (numberComps == 1)
            format = GL_RED;
        else if (numberComps == 3)
            format = GL_RGB;
        else if (numberComps == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Error loading texture! " << endl;
        stbi_image_free(data);
    }

    return textureID;
}

    vector<Mesh> Model::getMeshes(){
        return meshes;
    }

    vector<vertex> Model::getVertices(Mesh mesh){
        return mesh.vertices;
    }

    vector<GLuint> Model::getIndices(Mesh mesh){
        return mesh.indices;
    }

    vector<texture> Model::getTextures(Mesh mesh){
    return mesh.textures;
    }

    GLuint Model::getNoOfIndices(Mesh mesh){
        return mesh.indices.size();
    }

    GLuint Model::getNoOfVertices(Mesh mesh){
        return mesh.vertices.size();
    }

    GLuint Model::getNoOfVertices(Model model){
    vector<Mesh> modelMeshes = model.getMeshes();
    GLuint numberVertices = 0;

    for (int i = 0; i < model.getNoOfMeshes(); i++)
        numberVertices += model.getVertices(modelMeshes[i]).size();

    return numberVertices;
    }

    GLuint Model::getNoOfIndices(Model model){
    vector<Mesh> modelMeshes = model.getMeshes();
    GLuint numberIndices = 0;

    for (int i = 0; i < model.getNoOfMeshes(); i++)
        numberIndices += model.getIndices(modelMeshes[i]).size();

    return numberIndices;
}

    GLuint Model::getNoOfTextures(Mesh mesh){
       return mesh.textures.size();
    }

    GLuint Model::getNoOfMeshes(){
        return meshes.size();
    }
