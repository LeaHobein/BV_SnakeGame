#ifndef NEWPYRAMID_H
#define NEWPYRAMID_H
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
class NewPyramid
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

    NewPyramid();
    ~NewPyramid();

    GLfloat* makeFastNewPyramidVertices(GLfloat width, GLfloat height, GLfloat depth, GLfloat* color);

    /**
     * Creates fourteen indices for drawing a cuboid (box) with glDrawElements().
     * To be used together with makeFastBoxVertices().
     * To be used with "glDrawElements" and "GL_TRIANGLE_STRIP".
     * @return indices into the vertex array of the cube
     */
    GLint* makeFastNewPyramidIndicesForTriangleStrip();

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
    GLfloat* makeNewPyramidVertices(GLfloat width, GLfloat height, GLfloat depth, GLfloat* color);

    /**
     * Creates 28 indices for drawing a cuboid (box).
     * To be used together with makeBoxVertices()
     * To be used with "glDrawElements" and "GL_TRIANGLE_STRIP".
     * @return indices into the vertex array of the cube (box)
     */
    GLint* makeNewPyramidIndicesForTriangleStrip();
    /**
     * Returns the number of indices of a cuboid (box) for the draw call.
     * To be used together with makeBoxIndicesForTriangleStrip
     * @return number of indices
     */

    GLint getNoOfIndicesForFastNewPyramid();
    GLint getNoOfIndicesForNewPyramid();
    GLint getNoOfVerticesForFastNewPyramid();
    GLint getNoOfVerticesForNewPyramid();

private:
    /**
     * Returns the number of indices of the fast cuboid (box) for the draw call.
     * @return
     */
    GLint noOfIndicesForFastNewPyramid();


    GLint noOfIndicesForNewPyramid();
};

#endif //NEWPYRAMID_H
