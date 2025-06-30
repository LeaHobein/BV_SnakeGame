#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>

#include <iostream>
using namespace std;

/**
 * C++ class holding material parameters for surfaces.
 * @author Merijam Gotzes
 * @version 12.04.2024, 19.04.2024
 */
class Material {

public:

    Material();

    Material(GLfloat* emi, GLfloat* amb, GLfloat* diff, GLfloat* spec, GLfloat shin);


    float* getEmission() const;

    void setEmission(GLfloat* emi);


    float* getAmbient() const;

    void setAmbient(GLfloat* amb);


    float* getDiffuse() const;

    void setDiffuse(GLfloat* diff);


    float* getSpecular() const;

    void setSpecular(GLfloat* spec);


    float getShininess() const;

    void setShininess(GLfloat shin);

private:

    GLfloat* emission;
    GLfloat* ambient;
    GLfloat* diffuse;
    GLfloat* specular;
    GLfloat shininess;

};

#endif //MATERIAL_H
