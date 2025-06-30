#include "Material.h"

/**
 * C++ class holding material parameters for surfaces.
 * @author Merijam Gotzes
 * @version 12.04.2024, 19.04.2024, 02.05.2024
 */


    Material::Material() {
        emission = new GLfloat[4];
        ambient = new GLfloat[4];
        diffuse = new GLfloat[4];
        specular = new GLfloat[4];
        shininess = 0;
    }

Material::Material(GLfloat* emi, GLfloat* amb, GLfloat* diff, GLfloat* spec, GLfloat shin) {
        emission = new GLfloat[4];
        ambient = new GLfloat[4];
        diffuse = new GLfloat[4];
        specular = new GLfloat[4];

        for(int i = 0; i < 4; i++){
            emission[i] = emi[i];
            ambient[i] = amb[i];
            diffuse[i] = diff[i];
            specular[i] = spec[i];
        }
        shininess = shin;
    }


float* Material::getEmission() const {
        return emission;
    }

void Material::setEmission(GLfloat* emi) {
        emission = emi;
    }


float* Material::getAmbient() const {
        return ambient;
    }

void Material::setAmbient(GLfloat* amb) {
        ambient = amb;
    }


float* Material::getDiffuse() const {
        return diffuse;
    }

void Material::setDiffuse(GLfloat* diff) {
        diffuse = diff;
    }


float* Material::getSpecular() const {
        return specular;
    }

void Material::setSpecular(GLfloat* spec) {
        specular = spec;
    }


float Material::getShininess() const {
        return shininess;
    }

void Material::setShininess(GLfloat shin) {
        shininess = shin;
    }
