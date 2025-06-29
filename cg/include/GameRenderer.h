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

    inline static GLuint *vertex_buffer;
    inline static GLuint *vertex_array_object;
    inline static GLuint *index_buffer_object;

    // Define Materials
    inline static Material material0;

    // Define light sources
    inline static LightSource light0;

    ShaderProgram shaderProgram0;
    ShaderProgram shaderProgram1;

    void initObject0();
    void initObject1();

    void displayObject0(float* LightPosition);
    void displayObject1(float* LightPosition);

    // Create box for the scene
    //inline static BoxTex box0;
    inline static Model bunny;
    inline static Model banana;

    glm::mat4x4 modelviewMat;
    glm::mat4x4 projMat;

    Grid* grid = nullptr;
};


#endif // GAMERENDERER_H