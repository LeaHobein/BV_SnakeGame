#ifndef SPHERE_H
#define SPHERE_H

#include <glad/glad.h>
#include <vector>

/**
 * C++ class for creating vertex and buffer data for drawing a sphere.
 * @version 2024-06-29
 */
class Sphere {
public:
    Sphere(float radius, int sectors, int stacks);
    ~Sphere();

    const GLfloat* getVertices() const;
    const GLuint* getIndices() const;
    int getVertexCount() const;
    int getIndexCount() const;
    int getVertexSize() const;

private:
    void buildVertices();

    float radius;
    int sectors;
    int stacks;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
};

#endif //SPHERE_H
