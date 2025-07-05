#include "Box.h"
/**
 * C++ class for creating vertex and buffer data for drawing a box
 * using GLAD/OpenGL.
 * Intended to be used for an OpenGL scene renderer.
 * All methods are static.
 *
 * @author Merijam Gotzes
 * @version 12.04.2024, 19.04.2024
 */

    Box::Box() = default;
    Box::~Box() = default;

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
GLfloat* Box::makeBoxVertices(GLfloat width, GLfloat height, GLfloat depth, GLfloat* color) {

    GLfloat halfOfWidth = width / 2;
    GLfloat halfOfHeight = height / 2;
    GLfloat halfOfDepth = depth / 2;

    // Definition of positions of vertices for a cuboid
    GLfloat p0[3] = {-halfOfWidth, +halfOfHeight, +halfOfDepth}; // 0 front
    GLfloat p1[3] = {+halfOfWidth, +halfOfHeight, +halfOfDepth}; // 1 front
    GLfloat p2[3] = {+halfOfWidth, -halfOfHeight, +halfOfDepth}; // 2 front
    GLfloat p3[3] = {-halfOfWidth, -halfOfHeight, +halfOfDepth}; // 3 front
    GLfloat p4[3] = {-halfOfWidth, +halfOfHeight, -halfOfDepth}; // 4 back
    GLfloat p5[3] = {+halfOfWidth, +halfOfHeight, -halfOfDepth}; // 5 back
    GLfloat p6[3] = {+halfOfWidth, -halfOfHeight, -halfOfDepth}; // 6 back
    GLfloat p7[3]= {-halfOfWidth, -halfOfHeight, -halfOfDepth}; // 7 back

    // color vector
    GLfloat* c = color;

    // Definition of normal vectors for cuboid surfaces
    GLfloat nf[3] = { 0,  0,  1}; // 0 front
    GLfloat nb[3] = { 0,  0, -1}; // 0 back
    GLfloat nl[3] = {-1,  0,  0}; // 0 left
    GLfloat nr[3] = { 1,  0,  0}; // 0 right
    GLfloat nu[3] = { 0,  1,  1}; // 0 up (top)
    GLfloat nd[3] = { 0, -1,  1}; // 0 down (bottom)

    // Cuboid vertices to be drawn as triangle stripes
    // Interlaces with color information and normal vectors
    GLfloat vertices[216] = {
            // front surface
            // index: 0
            p0[0], p0[1], p0[2],   // position
            c[0],  c[1],  c[2],    // color
            nf[0], nf[1], nf[2],   // normal
            // index: 1
            p3[0], p3[1], p3[2],   // position
            c[0],  c[1],  c[2],   // color
            nf[0], nf[1], nf[2],   // normal
            // index: 2
            p1[0], p1[1], p1[2],   // position
            c[0],  c[1],  c[2],   // color
            nf[0], nf[1], nf[2],   // normal
            // index: 3
            p2[0], p2[1], p2[2],   // position
            c[0],  c[1],  c[2],   // color
            nf[0], nf[1], nf[2],   // normal

            // back surface
            // index: 4
            p5[0], p5[1], p5[2],   // position
            c[0],  c[1],  c[2],    // color
            nb[0], nb[1], nb[2],   // normal
            // index: 5
            p6[0], p6[1], p6[2],   // position
            c[0],  c[1],  c[2],   // color
            nb[0], nb[1], nb[2],   // normal
            // index: 6
            p4[0], p4[1], p4[2],   // position
            c[0],  c[1],  c[2],   // color
            nb[0], nb[1], nb[2],   // normal
            // index: 7
            p7[0], p7[1], p7[2],   // position
            c[0],  c[1],  c[2],   // color
            nb[0], nb[1], nb[2],   // normal

            // left surface
            // index: 8
            p4[0], p4[1], p4[2],   // position
            c[0],  c[1],  c[2],    // color
            nl[0], nl[1], nl[2],   // normal
            // index: 9
            p7[0], p7[1], p7[2],   // position
            c[0],  c[1],  c[2],   // color
            nl[0], nl[1], nl[2],   // normal
            // index: 10
            p0[0], p0[1], p0[2],   // position
            c[0],  c[1],  c[2],   // color
            nl[0], nl[1], nl[2],   // normal
            // index: 11
            p3[0], p3[1], p3[2],   // position
            c[0],  c[1],  c[2],   // color
            nl[0], nl[1], nl[2],   // normal

            // right surface
            // index: 12
            p1[0], p1[1], p1[2],   // position
            c[0],  c[1],  c[2],    // color
            nr[0], nr[1], nr[2],   // normal
            // index: 13
            p2[0], p2[1], p2[2],   // position
            c[0],  c[1],  c[2],   // color
            nr[0], nr[1], nr[2],   // normal
            // index: 14
            p5[0], p5[1], p5[2],   // position
            c[0],  c[1],  c[2],   // color
            nr[0], nr[1], nr[2],   // normal
            // index: 15
            p6[0], p6[1], p6[2],   // position
            c[0],  c[1],  c[2],   // color
            nr[0], nr[1], nr[2],   // normal

            // top surface
            // index: 16
            p4[0], p4[1], p4[2],   // position
            c[0],  c[1],  c[2],    // color
            nu[0], nu[1], nu[2],   // normal
            // index: 17
            p0[0], p0[1], p0[2],   // position
            c[0],  c[1],  c[2],   // color
            nu[0], nu[1], nu[2],   // normal
            // index: 18
            p5[0], p5[1], p5[2],   // position
            c[0],  c[1],  c[2],   // color
            nu[0], nu[1], nu[2],   // normal
            // index: 19
            p1[0], p1[1], p1[2],   // position
            c[0],  c[1],  c[2],   // color
            nu[0], nu[1], nu[2],   // normal

            // bottom surface
            // index: 20
            p3[0], p3[1], p3[2],   // position
            c[0],  c[1],  c[2],    // color
            nd[0], nd[1], nd[2],   // normal
            // index: 21
            p7[0], p7[1], p7[2],   // position
            c[0],  c[1],  c[2],   // color
            nd[0], nd[1], nd[2],   // normal
            // index: 22
            p2[0], p2[1], p2[2],   // position
            c[0],  c[1],  c[2],   // color
            nd[0], nd[1], nd[2],   // normal
            // index: 23
            p6[0], p6[1], p6[2],   // position
            c[0],  c[1],  c[2],   // color
            nd[0], nd[1], nd[2],   // normal
    };

    auto* vertex = new GLfloat[216];

    for(int i = 0; i < 216; i++)
        vertex[i] = vertices[i];

    return vertex;
}

/**
 * Creates 28 indices for drawing a cuboid (box).
 * To be used together with makeBoxVertices()
 * To be used with "glDrawElements" and "GL_TRIANGLE_STRIP".
 * @return indices into the vertex array of the cube (box)
 */
GLint* Box::makeBoxIndicesForTriangleStrip() {
    // Indices to reference the number of the box vertices
    // defined in makeBoxVertices()

    GLint indices[28] = {
            // Note: back faces are drawn,
            // but drawing is faster than using "GL_TRIANGLES"
            21, 23, 20, 22,         // down (bottom)
            1, 3, 0, 2, 2, 3,       // front
            12, 13, 14, 15,         // right
            4, 5, 6, 7,             // back
            8, 9, 10, 11, 10, 10,   // left
            16, 17, 18, 19          // up (top)
    };

    auto* index = new GLint[28];

    for(int i = 0; i < 28; i++)
        index[i] = indices[i];

    return index;
}

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
     GLfloat* Box::makeFastBoxVertices(GLfloat width, GLfloat height, GLfloat depth, GLfloat* color) {

        GLfloat halfOfWidth = width / 2;
        GLfloat halfOfHeight = height / 2;
        GLfloat halfOfDepth = depth / 2;

        // Definition of positions of vertices for a cuboid
        GLfloat p0[3] = {-halfOfWidth, +halfOfHeight, +halfOfDepth}; // 0 front
        GLfloat p1[3] = {+halfOfWidth, +halfOfHeight, +halfOfDepth}; // 1
        GLfloat p2[3] = {+halfOfWidth, -halfOfHeight, +halfOfDepth}; // 2
        GLfloat p3[3] = {-halfOfWidth, -halfOfHeight, +halfOfDepth}; // 3
        GLfloat p4[3] = {-halfOfWidth, +halfOfHeight, -halfOfDepth}; // 4 back
        GLfloat p5[3] = {+halfOfWidth, +halfOfHeight, -halfOfDepth}; // 5
        GLfloat p6[3] = {+halfOfWidth, -halfOfHeight, -halfOfDepth}; // 6
        GLfloat p7[3] = {-halfOfWidth, -halfOfHeight, -halfOfDepth}; // 7

        GLfloat* c = color;

        // Cuboid vertices to be drawn as triangle stripes
        // Interlaces with color information
        GLfloat vertices[48] = {
                // front surface
                p0[0], p0[1], p0[2],   // position
                c[0],  c[1],  c[2],   // color
                p1[0], p1[1], p1[2],   // position
                c[0],  c[1],  c[2],   // color
                p2[0], p2[1], p2[2],   // position
                c[0],  c[1],  c[2],   // color
                p3[0], p3[1], p3[2],   // position
                c[0],  c[1],  c[2],   // color
                p4[0], p4[1], p4[2],   // position
                c[0],  c[1],  c[2],   // color
                p5[0], p5[1], p5[2],   // position
                c[0],  c[1],  c[2],   // color
                p6[0], p6[1], p6[2],   // position
                c[0],  c[1],  c[2],   // color
                p7[0], p7[1], p7[2],   // position
                c[0],  c[1],  c[2],   // color
        };

        auto* vertex = new GLfloat[48];

        for(int i = 0; i < 48; i++)
            vertex[i] = vertices[i];
        return vertex;
    }

/**
* Creates fourteen indices for drawing a cuboid (box) with glDrawElements().
* To be used together with makeFastBoxVertices().
* To be used with "glDrawElements" and "GL_TRIANGLE_STRIP".
* @return indices into the vertex array of the cube
*/
GLint* Box::makeFastBoxIndicesForTriangleStrip() {

    // Indices to reference the number of the box vertices
    // defined in makeFastBoxVertices()
    int indices[14] = {2, 3, 6, 7,    // bottom side
                       4,             // back side, bottom left
                       3, 0,          // left side
                       2, 1,          // front side
                       6, 5,          // right side
                       4,             // back side, top right
                       1, 0};         // top side

    auto* index = new GLint[14];

    for(int i = 0; i < 14; i++)
        index[i] = indices[i];

    return index;
}


GLint Box::getNoOfIndicesForFastBox(){
         return noOfIndicesForFastBox();
     }

GLint Box::getNoOfIndicesForBox(){
    return noOfIndicesForBox();
}

GLint Box::getNoOfVerticesForFastBox(){
         return 48;
     }

GLint Box::getNoOfVerticesForBox(){
    return 216;
}

    /**
     * Returns the number of indices of the fast cuboid (box) for the draw call.
     * @return
     */
    GLint Box::noOfIndicesForFastBox() {
        return 14;
    }


    /**
     * Returns the number of indices of a cuboid (box) for the draw call.
     * To be used together with makeBoxIndicesForTriangleStrip
     * @return number of indices
     */
    GLint Box::noOfIndicesForBox() {
        return 28;
    }

    GLfloat* Box::makeBoxVerticesWithTex(GLfloat width, GLfloat height, GLfloat depth) {
    GLfloat halfOfWidth = width / 2;
    GLfloat halfOfHeight = height / 2;
    GLfloat halfOfDepth = depth / 2;

    GLfloat p0[3] = {-halfOfWidth, +halfOfHeight, +halfOfDepth}; GLfloat p1[3] = {+halfOfWidth, +halfOfHeight, +halfOfDepth}; GLfloat p2[3] = {+halfOfWidth, -halfOfHeight, +halfOfDepth}; GLfloat p3[3] = {-halfOfWidth, -halfOfHeight, +halfOfDepth};
    GLfloat p4[3] = {-halfOfWidth, +halfOfHeight, -halfOfDepth}; GLfloat p5[3] = {+halfOfWidth, +halfOfHeight, -halfOfDepth}; GLfloat p6[3] = {+halfOfWidth, -halfOfHeight, -halfOfDepth}; GLfloat p7[3]= {-halfOfWidth, -halfOfHeight, -halfOfDepth};

    GLfloat nf[3] = { 0,  0,  1}; GLfloat nb[3] = { 0,  0, -1}; GLfloat nl[3] = {-1,  0,  0};
    GLfloat nr[3] = { 1,  0,  0}; GLfloat nu[3] = { 0,  1,  0}; GLfloat nd[3] = { 0, -1,  0};

    GLfloat t0[2] = {0.0f, 1.0f}; GLfloat t1[2] = {0.0f, 0.0f}; GLfloat t2[2] = {1.0f, 1.0f}; GLfloat t3[2] = {1.0f, 0.0f};

    static GLfloat vertices[192] = {
        p0[0], p0[1], p0[2],   nf[0], nf[1], nf[2],   t0[0], t0[1],
        p3[0], p3[1], p3[2],   nf[0], nf[1], nf[2],   t1[0], t1[1],
        p1[0], p1[1], p1[2],   nf[0], nf[1], nf[2],   t2[0], t2[1],
        p2[0], p2[1], p2[2],   nf[0], nf[1], nf[2],   t3[0], t3[1],
        p5[0], p5[1], p5[2],   nb[0], nb[1], nb[2],   t0[0], t0[1],
        p6[0], p6[1], p6[2],   nb[0], nb[1], nb[2],   t1[0], t1[1],
        p4[0], p4[1], p4[2],   nb[0], nb[1], nb[2],   t2[0], t2[1],
        p7[0], p7[1], p7[2],   nb[0], nb[1], nb[2],   t3[0], t3[1],
        p4[0], p4[1], p4[2],   nl[0], nl[1], nl[2],   t0[0], t0[1],
        p7[0], p7[1], p7[2],   nl[0], nl[1], nl[2],   t1[0], t1[1],
        p0[0], p0[1], p0[2],   nl[0], nl[1], nl[2],   t2[0], t2[1],
        p3[0], p3[1], p3[2],   nl[0], nl[1], nl[2],   t3[0], t3[1],
        p1[0], p1[1], p1[2],   nr[0], nr[1], nr[2],   t0[0], t0[1],
        p2[0], p2[1], p2[2],   nr[0], nr[1], nr[2],   t1[0], t1[1],
        p5[0], p5[1], p5[2],   nr[0], nr[1], nr[2],   t2[0], t2[1],
        p6[0], p6[1], p6[2],   nr[0], nr[1], nr[2],   t3[0], t3[1],
        p4[0], p4[1], p4[2],   nu[0], nu[1], nu[2],   t0[0], t0[1],
        p0[0], p0[1], p0[2],   nu[0], nu[1], nu[2],   t1[0], t1[1],
        p5[0], p5[1], p5[2],   nu[0], nu[1], nu[2],   t2[0], t2[1],
        p1[0], p1[1], p1[2],   nu[0], nu[1], nu[2],   t3[0], t3[1],
        p3[0], p3[1], p3[2],   nd[0], nd[1], nd[2],   t0[0], t0[1],
        p7[0], p7[1], p7[2],   nd[0], nd[1], nd[2],   t1[0], t1[1],
        p2[0], p2[1], p2[2],   nd[0], nd[1], nd[2],   t2[0], t2[1],
        p6[0], p6[1], p6[2],   nd[0], nd[1], nd[2],   t3[0], t3[1],
    };
    return vertices;
}

