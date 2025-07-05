
#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include "Sphere.h"

/**
 * C++ class for creating vertex and buffer data for drawing a sphere
 * using Glad/OpenGL.
 * Intended to be used for an OpenGL scene renderer.
 * The resolution of the sphere is held as instance variables.
 * @author Merijam Gotzes
 * @version 12.04.2024, 19.04.2024
 */

    Sphere::Sphere(){
    verticalResolution = 0;
    horizontalResolution = 0;
    noOfIndices = 0;
    noOfVertices = 0;
    }

    Sphere::~Sphere() = default;

    Sphere::Sphere(GLint vertRes, GLint horizRes) {
        verticalResolution = vertRes;
        horizontalResolution = horizRes;
        noOfIndices = noOfIndicesForSphere();
        noOfVertices = noOfVerticesForSphere();
    }

    /**
     * Creates vertices for a (UV)-sphere with one single color and normal vectors.
     * To be used together with makeIndicesForTriangleStrip().
     * @param radius radius of the sphere
     * @param color three dimensional color vector for each vertex
     * @return list of vertices
     */
     GLfloat* Sphere::makeVertices(GLfloat radius, GLfloat* color)
    {
        // Using spherical coordinates to create the vertices
        GLuint noOfComponents = 3 + 3 + 3; // 3 position coordinates, 3 color coordinates, 3 normal coordinates
        auto* vertices = new GLfloat[(verticalResolution + 1) * horizontalResolution * noOfComponents];
        GLuint vertexNumberInc = 3 + 3 + 3; // three position coordinates, three color values, three normal coordinates
        GLuint vertexNumber = 0;

        GLfloat elevation = 0;
        auto elevationInc = (GLfloat) (glm::pi<GLfloat>() / (GLfloat) verticalResolution);
        GLfloat azimuth = 0;
        auto azimuthInc = (GLfloat) (2*glm::pi<GLfloat>() / (GLfloat) horizontalResolution);
        for(int elevationIndex = 0; elevationIndex <= verticalResolution; elevationIndex++) {
            azimuth = 0;
            for(int azimuthIndex = 0; azimuthIndex < horizontalResolution; azimuthIndex++) {
                // position coordinates in spherical coordinates
                GLfloat xPos = radius * (GLfloat) (glm::sin(elevation) * glm::cos(azimuth));
                GLfloat yPos = radius * (GLfloat) (glm::sin(elevation) * glm::sin(azimuth));
                GLfloat zPos = radius * (GLfloat) glm::cos(elevation);
                vertices[vertexNumber] = xPos;
                //cout << "xPosmadevertex[" << vertexNumber << "]=" << vertices[vertexNumber] << endl;
                vertices[vertexNumber+1] = yPos;
                //cout << "yPosmadevertex[" << vertexNumber+1 << "]=" << vertices[vertexNumber+1] << endl;
                vertices[vertexNumber+2] = zPos;
                //cout << "zPosmadevertex[" << vertexNumber+2 << "]=" << vertices[vertexNumber+2] << endl;
                // color coordinates (for all vertices the same)
                vertices[vertexNumber+3] = color[0];
                //cout << "col1madevertex[" << vertexNumber+3 << "]=" << vertices[vertexNumber+3] << endl;
                vertices[vertexNumber+4] = color[1];
                //cout << "col2madevertex[" << vertexNumber+4 << "]=" << vertices[vertexNumber+4] << endl;
                vertices[vertexNumber+5] = color[2];
                //cout << "col3madevertex[" << vertexNumber+5 << "]=" << vertices[vertexNumber+5] << endl;
                // coordinates of normal vector
                // for a sphere this vector is identical to the normalizes position vector
                GLfloat normalizationFactor = 1 / (float) glm::sqrt((xPos * xPos) + (yPos * yPos) + (zPos * zPos));
                vertices[vertexNumber+6] = xPos * normalizationFactor;
                //cout << "normxmadevertex[" << vertexNumber+6 << "]=" << vertices[vertexNumber+6] << endl;
                vertices[vertexNumber+7] = yPos * normalizationFactor;
                //cout << "normymadevertex[" << vertexNumber+7 << "]=" << vertices[vertexNumber+7] << endl;
                vertices[vertexNumber+8] = zPos * normalizationFactor;
                //cout << "normzmadevertex[" << vertexNumber+8 << "]=" << vertices[vertexNumber+8] << endl;

                vertexNumber += vertexNumberInc;
                azimuth += azimuthInc;
            }
            elevation += elevationInc;
        }
        return vertices;
    }

    /**
     * Creates indices for drawing a sphere with glDrawElements().
     * To be used together with makeVertices().
     * To be used with "glDrawElements" and "GL_TRIANGLE_STRIP".
     * @return indices into the vertex array of the sphere
     */
    GLint* Sphere::makeIndicesForTriangleStrip() {

        // Indices to refer to the number of the sphere vertices
        // defined in makeVertices()
        auto* indices = new GLint[getNoOfIndices()];
        GLuint index = 0;
        for (int vIndex = 1; vIndex <= verticalResolution; vIndex++)
            for (int hIndex = 0; hIndex < horizontalResolution; hIndex++) {
                indices[index] = (GLint) ((vIndex-1) * horizontalResolution) + hIndex;
                //cout << "1madeindex[" << index << "]=" << indices[index] << endl;
                index++;
                indices[index] = (GLint) ((vIndex) * horizontalResolution) + hIndex;
                //cout << "2madeindex[" << index << "]=" << indices[index] << endl;
                index++;
            }

        return indices;
    }

    /**
     * Computes the number of indices of a sphere for the draw call.
     * @return number of indices the index buffer
     */
   GLuint Sphere::noOfIndicesForSphere(){
        return 2 * verticalResolution * horizontalResolution;
    }

    GLuint Sphere::noOfVerticesForSphere(){
        GLsizei noOfComponents = 3 + 3 + 3;
        return ( verticalResolution + 1) * horizontalResolution * noOfComponents;
    }

    /**
     * Returns the number of indices of a sphere for the draw call.
     * @return number of indices the index buffer
     */
  GLsizei Sphere::getNoOfIndices(){
        return noOfIndices;
    }

/**
 * Returns the number of vertex attributes of a sphere for the draw call.
 * @return number of vertex attributes of the buffer object
 */
    GLsizei Sphere::getNoOfVertices(){
        return noOfVertices;
    }

