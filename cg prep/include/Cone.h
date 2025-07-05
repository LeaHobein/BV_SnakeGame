#ifndef CONE_H
#define CONE_H
#include <glad/glad.h>

#include <iostream>
using namespace std;


/**
 * C++ class for creating vertex and buffer data for drawing a frustum
 * with circular base surfaces using GLAD/OpenGL.
 * For avoiding confusion with the "frustum for clipping"
 * the name "cone" it used.
 * Intended to be used for an OpenGL scene renderer.
 * The resolution of the shape is held as instance variables.
 * @author Merijam Gotzes
 * @version 12.04.2024, 19.04.2024
 */
 class Cone {
 public:

     Cone();
     ~Cone();

     Cone(GLint horizRes);

     /**
      * Creates vertices for a cone (frustum) with one single color and normal vectors.
      * To be used together with makeIndicesForTriangleStrip().
      * If the top and base circles have the same radius, then the center of gravity
      * lies in the origin. The surface is parallel to the y-axis.
      * @param radiusTop radius of the top circle
      * @param radiusBottom radius of the bottom circle
      * @param length length of the cone (frustum) (distance between the two circles)
      * @param color three dimensional color vector for each vertex
      * @return list of vertices
      */
     GLfloat *makeVertices(GLfloat radiusTop, GLfloat radiusBottom, GLfloat length, GLfloat *color);

     /**
      * Creates indices for drawing the shape with glDrawElements().
      * To be used together with makeVertices().
      * To be used with "glDrawElements" and "GL_TRIANGLE_STRIP".
      * @return indices into the vertex array of the shape
      */
     GLint *makeIndicesForTriangleStrip();

     GLint getNoOfIndices();

     GLint getNoOfVertices();


 private:
     GLint horizontalResolution;
     GLint noOfIndices;

     /**
      * Computes the number of indices of a shape for the draw call.
      * @return
      */
     GLint noOfIndicesForCone();
 };

#endif // CONE_H
