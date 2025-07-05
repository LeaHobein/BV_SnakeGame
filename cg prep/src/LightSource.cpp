#include "LightSource.h"

/**
 *  C++ class holding parameters for a light source.
 *  @author Merijam Gotzes
 *  @version 12.04.2024, 19.04.2024, 02.05.2024
 */


    LightSource::LightSource() {
    position = new GLfloat[4];
    ambient = new GLfloat[4];
    diffuse = new GLfloat[4];
    specular = new GLfloat[4];
    }

    LightSource::LightSource(GLfloat* pos, GLfloat* amb, GLfloat* diff, GLfloat* spec) {
        position = new GLfloat[4];
        ambient = new GLfloat[4];
        diffuse = new GLfloat[4];
        specular = new GLfloat[4];

        for(int i = 0; i < 4; i++){
            position[i] = pos[i];
            ambient[i] = amb[i];
            diffuse[i] = diff[i];
            specular[i] = spec[i];
        }
    }
	
	LightSource::~LightSource() = default;

    GLfloat* LightSource::getPosition() {
        return position;
    }

    void LightSource::setPosition(GLfloat* pos) {
        position = pos;
    }

    GLfloat* LightSource::getAmbient() {
        return ambient;
    }

    void LightSource::setAmbient(GLfloat* amb) {
        ambient = amb;
    }

    GLfloat* LightSource::getDiffuse() {
        return diffuse;
    }

    void LightSource::setDiffuse(GLfloat* diff) {
        diffuse = diff;
    }

    GLfloat* LightSource::getSpecular() {
        return specular;
    }

    void LightSource::setSpecular(GLfloat* spec) {
        specular = spec;
    }


