#include "Sphere2.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * Constructs a sphere with a given radius and resolution.
 * @param r Radius of the sphere.
 * @param s Number of longitudinal sectors.
 * @param t Number of latitudinal stacks.
 */
Sphere2::Sphere2(float r, int s, int t) : radius(r), sectors(s), stacks(t) {
    buildVertices();
}

Sphere2::~Sphere2() = default;

/**
 * Generates vertex and index data for the sphere mesh.
 */
void Sphere2::buildVertices() {
    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / radius;
    float s, t;

    float sectorStep = 2 * M_PI / sectors;
    float stackStep = M_PI / stacks;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stacks; ++i) {
        stackAngle = M_PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (int j = 0; j <= sectors; ++j) {
            sectorAngle = j * sectorStep;

            // Vertex position
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // Placeholder color (will be overridden by material)
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);

            // Normalized vertex normal
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);

            // Vertex tex coord
            s = (float)j / sectors;
            t = (float)i / stacks;
            vertices.push_back(s);
            vertices.push_back(t);
        }
    }

    // Generate indices for triangle list
    int k1, k2;
    for (int i = 0; i < stacks; ++i) {
        k1 = i * (sectors + 1);
        k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }
}

const GLfloat* Sphere2::getVertices() const { return vertices.data(); }
const GLuint* Sphere2::getIndices() const { return indices.data(); }
int Sphere2::getVertexCount() const { return (int)(vertices.size() / 11); }
int Sphere2::getIndexCount() const { return (int)indices.size(); }
int Sphere2::getVertexSize() const { return (int)(vertices.size() * sizeof(GLfloat)); }
