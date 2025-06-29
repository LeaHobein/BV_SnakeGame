#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>

#include <iostream>
using namespace std;

/**
 *  C++ class holding material parameters for surfaces.
 *  @author Merijam Gotzes
 *  @version 12.04.2024, 19.04.2024
 */
class Material {

public:

    Material();

    Material(GLfloat* emi, GLfloat* amb, GLfloat* diff, GLfloat* spec, GLfloat shin);
	
	~Material();

    float* getEmission();

    void setEmission(GLfloat* emi);

    float* getAmbient();

    void setAmbient(GLfloat* amb);

    float* getDiffuse();

    void setDiffuse(GLfloat* diff);

    float* getSpecular();

    void setSpecular(GLfloat* spec);

    float getShininess();

    void setShininess(GLfloat shin);

private:

    GLfloat* emission;
    GLfloat* ambient;
    GLfloat* diffuse;
    GLfloat* specular;
    GLfloat shininess;

};

#endif //MATERIAL_H
