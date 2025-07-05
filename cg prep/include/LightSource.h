#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include<glad/glad.h>

/**
 *  C++ class holding parameters for a light source.
 *  @author Merijam Gotzes
 *  @version 12.04.2024, 19.04.2024, 02.05.2024
 */
class LightSource {
public:


    LightSource();

    LightSource(GLfloat* pos, GLfloat* amb, GLfloat* diff, GLfloat* spec);
	
	~LightSource();

    GLfloat* getPosition();

    void setPosition(GLfloat* pos);

    GLfloat* getAmbient();

    void setAmbient(GLfloat* amb);

    GLfloat* getDiffuse();

    void setDiffuse(GLfloat* diff);

    GLfloat* getSpecular();

    void setSpecular(GLfloat* spec);

    private:

    GLfloat* position;
    GLfloat* ambient;
    GLfloat* diffuse;
    GLfloat* specular;
};

#endif //LIGHTSOURCE_H
