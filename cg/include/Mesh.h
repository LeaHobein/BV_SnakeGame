#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <iostream>
using namespace std;

/**
 *  C++ class holding model loading parameters for Standford bunny.
 *  @author Merijam Gotzes
 *  @version 12.04.2024, 19.04.2024
 */

struct vertex{
    glm::vec3 position;
    glm::vec2 texcoords;
    glm::vec3 normal;
};

struct texture{
    GLuint id;
    string type;
    string path;
};

class Mesh {

public:
    //mesh data
    vector<vertex> vertices;
    vector<GLuint> indices;
    vector<texture> textures;

    Mesh();
    ~Mesh();

    Mesh(vector<vertex> vert, vector<GLuint> ind,vector<texture> tex);

};

#endif //MESH_H
