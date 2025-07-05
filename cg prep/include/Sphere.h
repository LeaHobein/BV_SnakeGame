#ifndef SPHERE_H
#define SPHERE_H

#include "glad/glad.h"

#include <iostream>
using namespace std;

/**
 * C++ class for creating vertex and buffer data for drawing a sphere
 * using GLAD/OpenGL.
 * Intended to be used for an OpenGL scene renderer.
 * The resolution of the sphere is held as instance variables.
 * @author Merijam Gotzes
 * @version 12.04.2024, 19.04.2024
 */
class Sphere {
public:


    Sphere();
    ~Sphere();

    Sphere(GLint vertRes, GLint horizRes);

    GLint getNoOfIndices();
    GLint getNoOfVertices();


    /**
     * Creates vertices for a (UV)-sphere with one single color and normal vectors.
     * To be used together with makeIndicesForTriangleStrip().
     * @param radius radius of the sphere
     * @param color three dimensional color vector for each vertex
     * @return list of vertices
     */
    GLfloat* makeVertices(GLfloat radius, GLfloat* color);

    /**
     * Creates indices for drawing a sphere with glDrawElements().
     * To be used together with makeVertices().
     * To be used with "glDrawElements" and "GL_TRIANGLE_STRIP".
     * @return indices into the vertex array of the sphere
     */
    GLint* makeIndicesForTriangleStrip();

private:

    GLuint verticalResolution;
    GLuint horizontalResolution;
    GLuint noOfIndices;
    GLuint noOfVertices;

    /**
     * Computes the number of indices of a sphere for the draw call.
     * @return number of indices the index buffer
     */
    GLuint noOfIndicesForSphere();
    GLuint noOfVerticesForSphere();
    /**
     * Returns the number of indices of a sphere for the draw call.
     * @return number of indices the index buffer
     */

};

#endif //SPHERE_H
