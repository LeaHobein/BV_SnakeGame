#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

#include <vector>
#include <iostream>
using namespace std;

/**
 *  C++ class holding model loading parameters for Standford bunny.
 *  @author Merijam Gotzes
 *  @version 12.04.2024, 19.04.2024
 */
class Model {

public:

    Model();
    ~Model();

    void loadModel(const string& filename);

    void parseNode(aiNode* vertex, const aiScene* Scene);
    Mesh parseMesh(aiMesh* PMesh, const aiScene* PScene);

    vector<texture> loadMaterialsTextures(aiMaterial *mat, aiTextureType type,string typname);

    vector<Mesh> getMeshes();
    vector<vertex> getVertices(Mesh mesh);
    vector<GLuint> getIndices(Mesh mesh);
    vector<texture> getTextures(Mesh mesh);

    GLuint getNoOfIndices(Mesh mesh);
    GLuint getNoOfIndices(Model model);

    GLuint getNoOfVertices(Mesh mesh);
    GLuint getNoOfVertices(Model model);

    GLuint getNoOfTextures(Mesh mesh);
    GLuint getNoOfMeshes();

private:
    vector<Mesh> meshes;
    vector<texture> tex_loaded;
    string directory;

    GLuint LoadTexFromFile(const string &directory, const char *path);

};

#endif //MODEL_H
