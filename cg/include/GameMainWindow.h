/**
 *  Start class of the graphics application.
 *  Creates a Window (GLFW) where the OpenGL output is displayed in.
 *  Starts an animation loop, which triggers the OpenGL renderer.
 **/

/** Create an OS Window using Windowing API GLFW  for OpenGL
 * (alternative Windowing APIs for OpenGL: GLUT/FreeGLUT, Qt aso.)
* Inspired by https://www.glfw.org/docs/3.3/quick.html and
 * https://www.glfw.org/docs/3.3/input_guide.html
 * @author: Merijam Gotzes
* @version: 14.03.2024
**/

#ifndef GAMEMAINWINDOW_H
#define GAMEMAINWINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GameRenderer.h"

#include <iostream>

using namespace std;

class GameMainWindow {
public:
    explicit GameMainWindow();

    //StartRenderer renderer;
    const static int WINDOW_WIDTH = 2048;
    const static int WINDOW_HEIGHT = 1024;

    ~GameMainWindow();

//Setting an error callback
    static void error_callback(int error_code, const char *description);

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    static void window_refresh_callback(GLFWwindow* window);

    GameRenderer get_Renderer();

    static void set_Renderer(GameRenderer& renderer);

private:
    inline static GameRenderer render;

};

#endif // GAMEMAINWINDOW_H