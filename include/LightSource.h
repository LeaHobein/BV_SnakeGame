#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include<glad/glad.h>

/**
 * C++ class holding parameters for a light source.
 * @author Merijam Gotzes
 * @version 12.04.2024, 19.04.2024, 02.05.2024
 */
class LightSource {
public:

    LightSource();

    LightSource(GLfloat* pos, GLfloat* amb, GLfloat* diff, GLfloat* spec);

    // KORRIGIERT: Getter als 'const' markiert
    GLfloat* getPosition() const;

    void setPosition(GLfloat* pos);

    // KORRIGIERT: Getter als 'const' markiert
    GLfloat* getAmbient() const;

    void setAmbient(GLfloat* amb);

    // KORRIGIERT: Getter als 'const' markiert
    GLfloat* getDiffuse() const;

    void setDiffuse(GLfloat* diff);

    // KORRIGIERT: Getter als 'const' markiert
    GLfloat* getSpecular() const;

    void setSpecular(GLfloat* spec);

private:

    GLfloat* position;
    GLfloat* ambient;
    GLfloat* diffuse;
    GLfloat* specular;
};

#endif //LIGHTSOURCE_H
