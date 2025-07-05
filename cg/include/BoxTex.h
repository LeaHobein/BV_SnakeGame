#ifndef BOXTEX_H
#define BOXTEX_H
#include <glad/glad.h>

#include <iostream>
using namespace std;

/**
 * C++ class for creating vertex and buffer data for drawing a box
 * using GLAD/OpenGL.
 * Intended to be used for an OpenGL scene renderer.
 * All methods are static.
 *
 * @author Merijam Gotzes
 * @version 12.04.2024, 19.04.2024
 */
class BoxTex
{
    /**
     * Creates eight vertices for a cuboid (box) with one single color.
     * To be used together with makeFastBoxIndicesForTriangleStrip()
     * For using a fast drawing algorithm.
     * One color vector per vertex is placed.
     * No normal vectors are placed.
     * The center of gravity of this shape in the origin.
     * @param width width of the box (x direction)
     * @param height height of the box (y direction)
     * @param depth depth of the box (z direction)
     * @param color three dimensional color vector for each vertex
     * @return list of vertices
     */
public:

    BoxTex();
    ~BoxTex();


    /**
  * Creates 24 vertices for a cuboid (box) with one single color
  * and correctly placed normal vectors.
  * The center of gravity of this shape is placed in the origin.
  * To be used together with makeBoxIndicesForTriangleStrip()
  * @param width with of box (x direction)
  * @param height height of box (y direction)
  * @param depth depth of box (z direction)
  * @param color three dimensional color vector for each vertex
  * @return list of vertices
  */
    GLfloat* makeBoxVertices(GLfloat width, GLfloat height, GLfloat depth, GLfloat* color);

    /**
     * Creates 28 indices for drawing a cuboid (box).
     * To be used together with makeBoxVertices()
     * To be used with "glDrawElements" and "GL_TRIANGLE_STRIP".
     * @return indices into the vertex array of the cube (box)
     */
    GLint* makeBoxIndicesForTriangleStrip();
    /**
     * Returns the number of indices of a cuboid (box) for the draw call.
     * To be used together with makeBoxIndicesForTriangleStrip
     * @return number of indices
     */

    GLint getNoOfIndicesForBox();
    GLint getNoOfVerticesForBox();

private:
    /**
     * Returns the number of indices of the fast cuboid (box) for the draw call.
     * @return
     */
    GLint noOfIndicesForBox();
};

#endif //BOX_H
