#ifndef PYRAMID_H
#define PYRAMID_H

#include <glad/glad.h>

/**
 * C++ class for creating vertex and buffer data for drawing a pyramid.
 * @version 2024-06-29
 */
class Pyramid {
public:
    Pyramid();
    ~Pyramid();

    // Creates vertices for a pyramid.
    GLfloat* makePyramidVertices(GLfloat width, GLfloat height, GLfloat depth, GLfloat* color);

    // Creates indices for the pyramid triangles.
    GLint* makePyramidIndices();

    // Returns the number of vertices.
    GLint getNoOfVerticesForPyramid();

    // Returns the number of indices.
    GLint getNoOfIndicesForPyramid();
};

#endif //PYRAMID_H
