// Create an OS Window using Windowing API GLFW  for OpenGL
// (alternative Windowing APIs for OpenGL: GLUT/FreeGLUT, Qt aso.)
// Inspired by https://www.glfw.org/docs/3.3/quick.html and
// https://www.glfw.org/docs/3.3/input_guide.html
// Merijam Gotzes
// 14.03.2024, 02.05.2024


#ifndef BOXLIGHTTEXRENDERER_H
#define BOXLIGHTTEXRENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

#include "ShaderProgram.h"
#include "BoxTex.h"
#include "LightSource.h"
#include "Material.h"
#include "Pyramid.h"
#include "Sphere.h"


#include <iostream>
using namespace std;

class BoxLightTexRenderer {
public:

    BoxLightTexRenderer();
    ~BoxLightTexRenderer();

    void init();
    void display(GLFWwindow* window);
    void reshape(GLFWwindow* window);
    void dispose();


private:
    // Variable zur Steuerung der Anzahl der Körpersegmente
    // Kann hier geändert werden, Gesamtlänge ist dieser Wert + 1 für Kopf
    // max 9, da Gesamtlänge 10 nicht überschreiten soll
    inline static int numberOfBodySegments = 4;

    inline static const char *SHADER_PATH = "../resources/";

    inline static const char *VERTEX_SHADER_FILE_NAME0 = "BlinnPhongPointTex.vert";
    inline static const char *FRAGMENT_SHADER_FILE_NAME0 = "BlinnPhongPointTex.frag";

    inline static const char *TEXTURE_PATH = "../resources/";
    inline static const char *TEXTURE_FILE_NAME0 = "SchlangeTextur.jpeg";

    inline static const int NUMB_OF_OBJECTS = 3;
    inline static GLuint vertex_buffer[NUMB_OF_OBJECTS];
    inline static GLuint vertex_array_object[NUMB_OF_OBJECTS];
    inline static GLuint index_buffer_object[NUMB_OF_OBJECTS];
    inline static GLuint textureID0;

    // Define Materials
    inline static Material material0;
    inline static Material materialEyes;

    // Define light sources
    inline static LightSource light0;

    ShaderProgram shaderProgram0;

    // Init functions for each object type
    void initObject0(); // Box
    void initObject1(); // Pyramid
    void initObject2(); // Sphere

    // Generic draw function
    void drawObject(int objectIndex, int indexCount, GLenum drawMode, const glm::mat4& modelMatrix, const Material& material, bool useTexture);


    // Create objects for the scene
    inline static BoxTex box0;
    inline static Pyramid pyramid0;
    inline static Sphere *sphere0;

    // Matrices
    glm::mat4x4 projMat;
    glm::mat4x4 viewMat;
};


#endif // BOXLIGHTTEXRENDERER_H
