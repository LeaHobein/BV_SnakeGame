#include "Mesh.h"

/**
 *  C++ class holding mesh loading parameters models (e.g. Standford bunny).
 *  See https://learnopengl.com/Model-Loading/Assimp for a tutorial
 *  @author Merijam Gotzes
 *  @version 12.04.2024, 19.04.2024, 02.05.2024
 */


    Mesh::Mesh() = default;

    Mesh::~Mesh() = default;

    Mesh::Mesh(vector<vertex> vert, vector<GLuint> ind,vector<texture> tex){
        vertices = vert;
        indices = ind;
        textures = tex;
    }
