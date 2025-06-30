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

#ifndef BOXLIGHTTEXMAINWINDOW_H
#define BOXLIGHTTEXMAINWINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "BoxLightTexRenderer.h"

#include <iostream>

using namespace std;

class BoxLightTexMainWindow {
public:
    explicit BoxLightTexMainWindow();

    //StartRenderer renderer;
    const static int WINDOW_WIDTH = 2048;
    const static int WINDOW_HEIGHT = 1024;

    ~BoxLightTexMainWindow();

//Setting an error callback
    static void error_callback(int error_code, const char *description);

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    static void window_refresh_callback(GLFWwindow* window);

    BoxLightTexRenderer get_Renderer();

    static void set_Renderer(BoxLightTexRenderer& renderer);

private:
    inline static BoxLightTexRenderer render;

};

#endif // BOXLIGHTTEXMAINWINDOW_H