#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include "Cone.h"

    Cone::Cone() {
        horizontalResolution = 0;
        noOfIndices = 0;
}
    Cone::~Cone() = default;

/**
 * C++ class for creating vertex and buffer data for drawing a frustum
 * with circular base surfaces using Glad/OpenGL.
 * For avoiding confusion with the "frustum for clipping"
 * the name "cone" it used.
 * Intended to be used for an OpenGL scene renderer.
 * The resolution of the shape is held as instance variables.
 * @author Merijam Gotzes
 * @version 12.04.2024, 19.04.2024
 */

    Cone::Cone(GLint horizRes) {
        horizontalResolution = horizRes;
        noOfIndices = noOfIndicesForCone();
    }

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
    GLfloat* Cone::makeVertices(GLfloat radiusTop, GLfloat radiusBottom, GLfloat length, GLfloat* color) {

        // vertices for the top and bottom circles are duplicated
        // for correct normal vector orientation
        GLint noOfComponents = 3 + 3 + 3; // 3 position coordinates, 3 color coordinates, 3 normal coordinates
        auto* vertices = new GLfloat[(1 + (4 * horizontalResolution) + 1) * noOfComponents];
        GLint vertexNumberInc = 3 + 3 + 3; // three position coordinates, three color values, three normal coordinates
        GLint vertexNumber = 0; // initialize vertex count

        // y Coordinate of top circle
        GLfloat yTop = length / 2;
        // y Coordinate of bottom circle
        GLfloat yBottom = -length / 2;

        // normal vector for top circle
        GLfloat topNormal[3] = {0, 1, 0};
        // top center of circle
        vertices[vertexNumber] = 0;
        vertices[vertexNumber+1] = yTop;
        vertices[vertexNumber+2] = 0;
        // color coordinates (for all vertices the same)
        vertices[vertexNumber+3] = color[0];
        vertices[vertexNumber+4] = color[1];
        vertices[vertexNumber+5] = color[2];
        // normal vector coordinates
        vertices[vertexNumber+6] = topNormal[0];
        vertices[vertexNumber+7] = topNormal[1];
        vertices[vertexNumber+8] = topNormal[2];
        vertexNumber += vertexNumberInc;

        // vertices for the top circle
        GLfloat angleTop = 0;
        auto angleTopInc = (GLfloat) (2 * glm::pi<float>() / (GLfloat) horizontalResolution);
        for (int angleIndex = 0; angleIndex < horizontalResolution; angleIndex++) {
            // position coordinates
            vertices[vertexNumber] = radiusTop * (GLfloat) (glm::cos(angleTop));
            vertices[vertexNumber + 1] = yTop;
            vertices[vertexNumber + 2] = radiusTop * (GLfloat) glm::sin(angleTop);
            // color coordinates (for all vertices the same)
            vertices[vertexNumber + 3] = color[0];
            vertices[vertexNumber + 4] = color[1];
            vertices[vertexNumber + 5] = color[2];
            // normal vector coordinates
            vertices[vertexNumber+6] = topNormal[0];
            vertices[vertexNumber+7] = topNormal[1];
            vertices[vertexNumber+8] = topNormal[2];
            vertexNumber += vertexNumberInc;
            angleTop += angleTopInc;
        }

        // vertices for the top edge of the surface
        angleTop = 0;
        angleTopInc = (GLfloat) (2 * glm::pi<float>() / (GLfloat) horizontalResolution);
        // y component of normal vector coordinates for top edge of surface
        GLfloat yNormalTop = radiusTop * (radiusBottom - radiusTop) / length;
        for (int angleIndex = 0; angleIndex < horizontalResolution; angleIndex++) {
            // position coordinates
            GLfloat xPos = radiusTop * (GLfloat) (glm::cos(angleTop));
            GLfloat yPos = yTop;
            GLfloat zPos = radiusTop * (GLfloat) glm::sin(angleTop);
            vertices[vertexNumber] = xPos;
            vertices[vertexNumber + 1] = yPos;
            vertices[vertexNumber + 2] = zPos;
            // color coordinates (for all vertices the same)
            vertices[vertexNumber + 3] = color[0];
            vertices[vertexNumber + 4] = color[1];
            vertices[vertexNumber + 5] = color[2];
            // normalize normal vector
            GLfloat normalizationFactor =
                    1 / (GLfloat) glm::sqrt((xPos * xPos) + (yNormalTop * yNormalTop) + (zPos * zPos));
            vertices[vertexNumber+6] = xPos * normalizationFactor;
            vertices[vertexNumber+7] = 0;
            vertices[vertexNumber+8] = zPos * normalizationFactor;
            vertexNumber += vertexNumberInc;
            angleTop += angleTopInc;
        }

        // vertices for the bottom edge of the surface
        GLfloat angleBottom = 0;
        auto angleBottomInc = (GLfloat) (2 * glm::pi<float>() / (GLfloat) horizontalResolution);
        // y component of normal vector coordinates for bottom edge of surface
        GLfloat yNormalBottom = radiusBottom * (radiusBottom - radiusTop) / length;
        for (int angleIndex = 0; angleIndex < horizontalResolution; angleIndex++) {
            // position coordinates
            GLfloat xPos = radiusBottom * (GLfloat) (glm::cos(angleBottom));
            GLfloat yPos = yBottom;
            GLfloat zPos = radiusBottom * (GLfloat) glm::sin(angleBottom);
            vertices[vertexNumber] = xPos;
            vertices[vertexNumber + 1] = yPos;
            vertices[vertexNumber + 2] = zPos;
            // color coordinates (for all vertices the same)
            vertices[vertexNumber + 3] = color[0];
            vertices[vertexNumber + 4] = color[1];
            vertices[vertexNumber + 5] = color[2];
            // normalize normal vector
            GLfloat normalizationFactor =
                    1 / (GLfloat) glm::sqrt((xPos * xPos) + (yNormalBottom * yNormalBottom) + (zPos * zPos));
            vertices[vertexNumber+6] = xPos * normalizationFactor;
            vertices[vertexNumber+7] = 0;
            vertices[vertexNumber+8] = zPos * normalizationFactor;
            vertexNumber += vertexNumberInc;
            angleBottom += angleBottomInc;
        }

        // vertices for the bottom circle
        // normal vector for bottom circle
        GLfloat bottomNormal[3] = {0, -1, 0};
        angleBottom = 0;
        angleBottomInc = (GLfloat) (2 * glm::pi<float>() / (GLfloat) horizontalResolution);
        for (int angleIndex = 0; angleIndex < horizontalResolution; angleIndex++) {
            // position coordinates
            vertices[vertexNumber] = radiusBottom * (GLfloat) (glm::cos(angleBottom));
            vertices[vertexNumber + 1] = yBottom;
            vertices[vertexNumber + 2] = radiusBottom * (GLfloat) glm::sin(angleBottom);
            // color coordinates (for all vertices the same)
            vertices[vertexNumber + 3] = color[0];
            vertices[vertexNumber + 4] = color[1];
            vertices[vertexNumber + 5] = color[2];
            vertexNumber += vertexNumberInc;
            angleBottom += angleBottomInc;
            // normal vector coordinates
            vertices[vertexNumber+6] = bottomNormal[0];
            vertices[vertexNumber+7] = bottomNormal[1];
            vertices[vertexNumber+8] = bottomNormal[2];
        }

        // bottom center of circle
        vertices[vertexNumber] = 0;
        vertices[vertexNumber+1] = yBottom;
        vertices[vertexNumber+2] = 0;
        // color coordinates (for all vertices the same)
        vertices[vertexNumber+3] = color[0];
        vertices[vertexNumber+4] = color[1];
        vertices[vertexNumber+5] = color[2];
        // normal vector coordinates
        vertices[vertexNumber+6] = bottomNormal[0];
        vertices[vertexNumber+7] = bottomNormal[1];
        vertices[vertexNumber+8] = bottomNormal[2];

        return vertices;
    }

    /**
     * Creates indices for drawing the shape with glDrawElements().
     * To be used together with makeVertices().
     * To be used with "glDrawElements" and "GL_TRIANGLE_STRIP".
     * @return indices into the vertex array of the shape
     */
    GLint* Cone::makeIndicesForTriangleStrip() {

        // Indices to refer to the number of the cone (frustum) vertices
        // defined in makeVertices()
        auto* indices = new GLint[noOfIndices];

        // BEGIN: Indices for top circle
        GLint topCenterIndex = 0;
        GLint firstTopCircleEdgeIndex = 1;
        GLint lastTopCircleEdgeIndex = horizontalResolution;

        int index = 0;
        // first index, center of top circle
        // draw twice to get the front face orientation right
        indices[index] = topCenterIndex;
        index++;
        indices[index] = topCenterIndex;
        index++;

        for (int hIndex = 1; hIndex <= horizontalResolution; hIndex++) {
            indices[index] = hIndex;
            index++;
            indices[index] = topCenterIndex;
            index++;
        }
        // close the top circle with a final triangle
        indices[index] = firstTopCircleEdgeIndex;
        index++;
        // END: Indices for top circle

        // BEGIN: Indices for surface
        GLint firstSurfaceTopIndex = horizontalResolution + 1;
        GLint firstSurfaceBottomIndex = (2 * horizontalResolution) + 1;
        for (int hIndex = 0; hIndex < horizontalResolution; hIndex++) {
            indices[index] = firstSurfaceTopIndex + hIndex;
            index++;
            indices[index] = firstSurfaceBottomIndex + hIndex;
            index++;
        }
        // Close the surface
        indices[index] = firstSurfaceTopIndex;
        index++;
        indices[index] = firstSurfaceBottomIndex;
        index++;
        // END: Indices for surface

        // BEGIN: Indices for bottom circle
        GLint bottomCenterIndex = (4 * horizontalResolution) + 1;
        GLint firstBottomCircleEdgeIndex = (3 * horizontalResolution) + 1;

        // picking up from surface
        indices[index] = firstBottomCircleEdgeIndex;
        index++;
        // first index, center of top circle
        indices[index] = bottomCenterIndex;
        index++;

        for (int hIndex = 0; hIndex < horizontalResolution; hIndex++) {
            indices[index] = firstBottomCircleEdgeIndex + hIndex;
            index++;
            indices[index] = bottomCenterIndex;
            index++;
        }
        // close the top circle with a final triangle
        indices[index] = firstBottomCircleEdgeIndex;

        return indices;
    }

    /**
     * Computes the number of indices of a shape for the draw call.
     * @return
     */
    GLint Cone::noOfIndicesForCone() {
        GLint noOfIndicesForCircle =
                1 + // center of the circle
                        // additional vertices for drawing with TRIANGLE_STRIP instead of TRIANGLE_FAN
                        (2 * horizontalResolution) +
                        1; // closing the circle

        return  1+ // reverse back/front faces
                noOfIndicesForCircle + // top circle
                (2 * horizontalResolution) +  // surface
                2 + // close the surface
                1 + // picking up the bottom circle
                noOfIndicesForCircle;// bottom circle
    }

    GLint Cone::getNoOfIndices() {
        return noOfIndices;
    }

    GLint Cone::getNoOfVertices(){
        GLint noOfComponents = 3 + 3 + 3;
        return (1 + (4 * horizontalResolution) + 1) * noOfComponents;
    }
