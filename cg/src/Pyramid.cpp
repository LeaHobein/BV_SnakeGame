#include "Pyramid.h"
#include <glm/glm.hpp>
#include <vector>

Pyramid::Pyramid() = default;
Pyramid::~Pyramid() = default;

/**
 * Creates vertices for a pyramid with its base on the XY plane and apex along the Z axis.
 * Each face has unique vertices to allow for correct face normals for lighting.
 * @param width Base width (X-axis).
 * @param height Base height (Y-axis).
 * @param depth Pyramid height from base to apex (Z-axis).
 * @param color A 3-component color vector.
 * @return A pointer to a static array of vertex data.
 */
GLfloat* Pyramid::makePyramidVertices(GLfloat width, GLfloat height, GLfloat depth, GLfloat* color) {
    GLfloat halfOfWidth = width / 2.0f;
    GLfloat halfOfHeight = height / 2.0f;

    // Define the 5 unique points of the pyramid
    glm::vec3 p0(-halfOfWidth, -halfOfHeight, 0); // Base vertex 1
    glm::vec3 p1( halfOfWidth, -halfOfHeight, 0); // Base vertex 2
    glm::vec3 p2( halfOfWidth,  halfOfHeight, 0); // Base vertex 3
    glm::vec3 p3(-halfOfWidth,  halfOfHeight, 0); // Base vertex 4
    glm::vec3 p4(0.0f, 0.0f, depth);              // Apex

    // calculate normals for each of the 5 faces
    glm::vec3 n_base(0.0f, 0.0f, -1.0f);
    glm::vec3 n_front = glm::normalize(glm::cross(p1 - p0, p4 - p0));
    glm::vec3 n_right = glm::normalize(glm::cross(p2 - p1, p4 - p1));
    glm::vec3 n_back = glm::normalize(glm::cross(p3 - p2, p4 - p2));
    glm::vec3 n_left = glm::normalize(glm::cross(p0 - p3, p4 - p3));

    // define texture coordinates for the vertices
    glm::vec2 t00(0.0f, 0.0f);
    glm::vec2 t10(1.0f, 0.0f);
    glm::vec2 t11(1.0f, 1.0f);
    glm::vec2 t01(0.0f, 1.0f);
    glm::vec2 t_apex(0.5f, 1.0f);

    // static array to hold all vertex data. 16 vertices * 11 floats/vertex (pos, color, normal, tex)
    static GLfloat vertices[16 * 11] = {
        // base face (indices 0-3)
        p0.x, p0.y, p0.z,   color[0], color[1], color[2],   n_base.x, n_base.y, n_base.z,   t00.x, t00.y,
        p1.x, p1.y, p1.z,   color[0], color[1], color[2],   n_base.x, n_base.y, n_base.z,   t10.x, t10.y,
        p2.x, p2.y, p2.z,   color[0], color[1], color[2],   n_base.x, n_base.y, n_base.z,   t11.x, t11.y,
        p3.x, p3.y, p3.z,   color[0], color[1], color[2],   n_base.x, n_base.y, n_base.z,   t01.x, t01.y,

        // front face (indices 4-6)
        p0.x, p0.y, p0.z,   color[0], color[1], color[2],   n_front.x, n_front.y, n_front.z, t00.x, t00.y,
        p1.x, p1.y, p1.z,   color[0], color[1], color[2],   n_front.x, n_front.y, n_front.z, t10.x, t10.y,
        p4.x, p4.y, p4.z,   color[0], color[1], color[2],   n_front.x, n_front.y, n_front.z, t_apex.x, t_apex.y,

        // right face (indices 7-9)
        p1.x, p1.y, p1.z,   color[0], color[1], color[2],   n_right.x, n_right.y, n_right.z, t00.x, t00.y,
        p2.x, p2.y, p2.z,   color[0], color[1], color[2],   n_right.x, n_right.y, n_right.z, t10.x, t10.y,
        p4.x, p4.y, p4.z,   color[0], color[1], color[2],   n_right.x, n_right.y, n_right.z, t_apex.x, t_apex.y,

        // back face (indices 10-12)
        p2.x, p2.y, p2.z,   color[0], color[1], color[2],   n_back.x, n_back.y, n_back.z,   t00.x, t00.y,
        p3.x, p3.y, p3.z,   color[0], color[1], color[2],   n_back.x, n_back.y, n_back.z,   t10.x, t10.y,
        p4.x, p4.y, p4.z,   color[0], color[1], color[2],   n_back.x, n_back.y, n_back.z,   t_apex.x, t_apex.y,

        // left face (indices 13-15)
        p3.x, p3.y, p3.z,   color[0], color[1], color[2],   n_left.x, n_left.y, n_left.z,   t00.x, t00.y,
        p0.x, p0.y, p0.z,   color[0], color[1], color[2],   n_left.x, n_left.y, n_left.z,   t10.x, t10.y,
        p4.x, p4.y, p4.z,   color[0], color[1], color[2],   n_left.x, n_left.y, n_left.z,   t_apex.x, t_apex.y
    };
    return vertices;
}

/**
 * creates indices for drawing the pyramid using GL_TRIANGLES.
 * @return A pointer to a static array of indices.
 */
GLint* Pyramid::makePyramidIndices() {
    static GLint indices[] = {
        // Base
        0, 1, 2,    0, 2, 3,
        // Sides
        4, 5, 6,
        7, 8, 9,
        10, 11, 12,
        13, 14, 15
    };
    return indices;
}

GLint Pyramid::getNoOfVerticesForPyramid() {
    return 16;
}

GLint Pyramid::getNoOfIndicesForPyramid() {
    // 6 triangles * 3 vertices/triangle
    return 18;
}
