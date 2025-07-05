#ifndef ROOF_H
#define ROOF_H

#include <glad/glad.h>

/**
 * C++ class for creating vertex and buffer data for drawing a
 * roof like shape, i.e. a cylinder with a triangular base surface
 * using GLAD/OpenGL.
 * Intended to be used for an OpenGL scene renderer.
 * All methods are static.
 *
 * @author Merijam Gotzes
 * @version 12.04.2024, 19.04.2024
 */
class Roof {

    public:

    Roof();
    ~Roof();
    /**
     * Creates vertices for a roof like shape with one single color and
     * normal vectors.
     * To be used together with makeIndicesForTriangleStrip().
     * The centre of gravity of the shape lies in the origin.
     * The base side of the top and bottom triangles is oriented
     * parallel to the z-axis (at z-coordinate: (-width/3)).
     * The width of the shape is the length of the geometric height
     * of the base triangles over their base side. The top of the
     * base triangle is located at the x-coordinate ((2/3) * width)
     * and the z-coordinate 0.
     *
     * @param width distance between base side and top (x-direction) of the base triangle
     * @param height distance between bottom and top triangular surfaces
     *               (length of the shape in y-direction)
     * @param depth length of the base side (z-direction) of the base triangles
     * @param color three dimensional color vector for each vertex
     */
    GLfloat* makeVertices(GLfloat width, GLfloat height, GLfloat depth, GLfloat* color);

    /**
     * Creates indices for drawing the shape with glDrawElements().
     * To be used together with makeVertices().
     * To be used with "glDrawElements" and "GL_TRIANGLE_STRIP".
     * @return indices into the vertex array of the shape
     */
    GLint* makeIndicesForTriangleStrip();
    /**
     * Return the number of indices for drawing the shape.
     * @return number of indices
     */
    GLint getNoOfIndices();
    GLint getNoOfVertices();
};


#endif //ROOF_H
