// Loading objects using Assimp
// See https://learnopengl.com/Model-Loading/Assimp for a tutorial
// Basierend auf LoadBunnyLightTexRenderer.h von Merijam Gotzes
// 14.03.2024, 02.05.2024, 29.06.2025

#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

#include "ShaderProgram.h"
#include "LightSource.h"
#include "Material.h"
#include "Model.h"
#include "Grid.h"
#include "Sphere.h"
#include "Box.h"
#include "Cone.h"
#include "Roof.h"



#include <iostream>
using namespace std;

class GameRenderer {
public:

    GameRenderer();
    ~GameRenderer();

    void init();
    void display(GLFWwindow* window);
    void reshape(GLFWwindow* window);
    void dispose();
    void setGrid(Grid* g) { grid = g; }


private:
    inline static const char *SHADER_PATH = "../resources/";

    inline static const char *VERTEX_SHADER_FILE_NAME0 = "BlinnPhongPointTex.vert";
    inline static const char *FRAGMENT_SHADER_FILE_NAME0 = "BlinnPhongPointTex.frag";

    // inline static const char *VERTEX_SHADER_FILE_NAME0 = "BlinnPhongPointTex.vert";
    // inline static const char *FRAGMENT_SHADER_FILE_NAME0 = "BlinnPhongPointTex.frag";

    /*inline static const char *TEXTURE_PATH = "../resources/";
    inline static const char *TEXTURE_FILE_NAME0 = "HSHLLogo1.jpg";*/
    inline static const char *TEXTURE_PATH = "../resources/apple/";
    inline static const char *TEXTURE_FILE_NAME0 = "apple_tex.jpg";
    inline static const char *BANANA_TEXTURE_PATH = "../resources/banana/";
    inline static const char *BANANA_TEXTURE_FILE_NAME0 = "banana_tex.jpg";
    // inline static const char *TEXTURE_FILE_NAME0 = "HSHLLogo2.jpg";

    //.vert & .frag für Shapes
    inline static const char *VERTEX_SHADER_FILE_NAMEa = "O0_Basic.vert";
    inline static const char *FRAGMENT_SHADER_FILE_NAMEa = "O0_Basic.frag";

    inline static const char *VERTEX_SHADER_FILE_NAMEb = "O1_Basic.vert";
    inline static const char *FRAGMENT_SHADER_FILE_NAMEb = "O1_Basic.frag";

    inline static const char *VERTEX_SHADER_FILE_NAME2 = "O2_Basic.vert";
    inline static const char *FRAGMENT_SHADER_FILE_NAME2 = "O2_Basic.frag";

    inline static const char *VERTEX_SHADER_FILE_NAME3 = "O3_Basic.vert";
    inline static const char *FRAGMENT_SHADER_FILE_NAME3 = "O3_Basic.frag";

    inline static GLuint *vertex_buffer;
    inline static GLuint *vertex_array_object;
    inline static GLuint *index_buffer_object;

    // Define Materials
    inline static Material material0;

    // Define light sources
    inline static LightSource light0;

    ShaderProgram shaderProgram0;
    ShaderProgram shaderProgram1;

    //shader für Shapes
    ShaderProgram shaderProgramA;
    ShaderProgram shaderProgramB;
    ShaderProgram shaderProgram2;
    ShaderProgram shaderProgram3;

    void initObject0();
    void initObject1();
    //init für Shapes
    void initObjectA();
    void initObjectB();
    void initObject2();
    void initObject3();
    void initObject4();
    void initObject5();
    void initCony();
    void initIce();
    void initCube();
    void initRoof();
    void initField();
    void initBall();

    void displayObject0(float* LightPosition);
    void displayObject1(float* LightPosition);
    //display für Shapes
    void displayObjectA();
    void displayObjectB();
    void displayObject2();
    void displayObject3();
    void displayObject4();
    void displayObject5();
    void displayCony();
    void displayIce();
    void displayHouse(float z);
    void displayCube(glm::mat4x4 m);
    void displayRoof(glm::mat4x4 m);
    void serialHouse(float z, int a);
    void displayField();
    void displayBall(float time);

    // Create box for the scene
    //inline static BoxTex box0;
    inline static Model bunny;
    inline static Model banana;
    //objects für Shapes
    inline static Sphere sphere0;
    inline static Box box0;
    inline static Cone cone0;
    inline static Roof roof0;
    inline static Cone treelog;
    inline static Cone treecrown;
    inline static Cone baumstamm;
    inline static Sphere baumkrone;
    inline static Cone cony;
    inline static Sphere ice;
    inline static Box cube;
    inline static Roof roof;
    inline static Box field;
    inline static Sphere ball;

    glm::mat4x4 modelviewMat;
    glm::mat4x4 projMat;

    Grid* grid = nullptr;
};


#endif // GAMERENDERER_H