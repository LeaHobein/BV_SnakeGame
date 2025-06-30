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

#include "BoxLightTexMainWindow.h"
#include "InteractionHandler.h"

BoxLightTexMainWindow::BoxLightTexMainWindow() = default;
BoxLightTexMainWindow::~BoxLightTexMainWindow() = default;

//Setting an error callback
void BoxLightTexMainWindow::error_callback(int error_code, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

// Resize window (by OS or user resize) this callback function executes (GLFW)
void BoxLightTexMainWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void BoxLightTexMainWindow::window_refresh_callback(GLFWwindow* window){
    auto* mainWindow = static_cast<BoxLightTexMainWindow*>(glfwGetWindowUserPointer(window));
    BoxLightTexRenderer startRenderer = mainWindow->get_Renderer();
    startRenderer.reshape(window);
}

BoxLightTexRenderer BoxLightTexMainWindow::get_Renderer(){
    return render;
}

void BoxLightTexMainWindow::set_Renderer(BoxLightTexRenderer& renderer){
    render = renderer;
}

int main() {

    BoxLightTexRenderer rend = BoxLightTexRenderer();
    BoxLightTexMainWindow::set_Renderer(rend);
    //Setting a GLFW error callback (GLFW)
    glfwSetErrorCallback(BoxLightTexMainWindow::error_callback);

    //Init: Open a simple OS window for OpenGL (GLFW)
    //Initialize the library GLFW
    if(!glfwInit())
    {
        cout << "Failed to initialize library GLFW" << endl;
        return -1;
    }

    GLFWwindow *window;
    window = glfwCreateWindow(BoxLightTexMainWindow::WINDOW_WIDTH,
                              BoxLightTexMainWindow::WINDOW_HEIGHT,
                              "Start Code Main GLFW Window - OpenGL Programmable Pipeline using GLAD",
                              nullptr, nullptr);
    //Set some hints to the next call to glfwCreateWindow (optional)
    // By default, the OpenGL context GLFW creates may have any version.
    // You can require a minimum OpenGL version by setting the GLFW_CONTEXT_VERSION_MAJOR
    // and GLFW_CONTEXT_VERSION_MINOR hints before creation
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create a simple OS window for OpenGL (GLFW)

    //Setting up the GLFW window: Successful?
    if (!window) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    double xpos = 0;
    double ypos = 0;

    //Create a key callback (GLFW)
    glfwSetKeyCallback(window, InteractionHandler::key_callback);
    //Create a mouse button callback (GLFW)
    glfwSetMouseButtonCallback(window, InteractionHandler::mouse_button_callback);
    glfwSetScrollCallback(window, InteractionHandler::scroll_callback);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback( window, InteractionHandler::cursor_position_callback); // doing nothing for now
    //Make the window's context current (GLFW)
    glfwMakeContextCurrent(window);
    //Setting up a frame buffer callback for window changes
    glfwSetWindowRefreshCallback(window,
                                 BoxLightTexMainWindow::window_refresh_callback);
    glfwSetFramebufferSizeCallback(window, BoxLightTexMainWindow::framebuffer_size_callback);

    // Initialize OpenGL canvas (GLAD)
    // Initialize OpenGL extension loader library GLAD
    // Load all OpenGL function pointers (GLAD)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glfwSwapInterval(1);

    //TODO: Capture input devices: keyboard, mouse, controller aso.
    rend.init();
    //Loop until the user closes the window (GLFW)
    while (!glfwWindowShouldClose(window)) {
        glfwGetCursorPos(window, &xpos, &ypos);
        InteractionHandler::lastMouseLocationX = (int) xpos;
        InteractionHandler::lastMouseLocationY = (int) ypos;

        glfwSetFramebufferSizeCallback(window, BoxLightTexMainWindow::framebuffer_size_callback);

        rend.display(window);

        //Use double buffering (GLFW)
        glfwSwapBuffers(window);
        //Poll for and process events (GLFW)
        glfwPollEvents();
    }

    rend.dispose();

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}

