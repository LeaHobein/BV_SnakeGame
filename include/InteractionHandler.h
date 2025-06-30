// Create an OS Window using Windowing API GLFW  for OpenGL
// (alternative Windowing APIs for OpenGL: GLUT/FreeGLUT, Qt aso.)
// Inspired by https://www.glfw.org/docs/3.3/quick.html and
// https://www.glfw.org/docs/3.3/input_guide.html
// Merijam Gotzes
// 14.03.2024

#ifndef INTERACTIONHANDLER_H
#define INTERACTIONHANDLER_H

#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

class InteractionHandler {
public:
    inline static int currentMouseLocationX{};
    inline static int currentMouseLocationY{};
    inline static float eyeZInc = 0.01f;
// Variables for scene rotation
    inline static float angleXaxis = 0.0f;
    inline static float angleYaxis = 0.0f;
    inline static float angleXaxisInc = 1.0f;
    inline static float angleYaxisInc = 1.0f;
    // Variables for scene translation
    inline static float xPosition = 0.0f;
    inline static float yPosition = 0.0f;
    inline static float mouseTranslationFactor = 0.1f;
    inline static float mouseWheelScrollFactor = 10.0f;

    // Variables for camera distance
    inline static float eyeZ = 2.0f;
    inline static float xPositionInc = 0.1f;
    inline static float yPositionInc= 0.1f;
    // Variables for keyboard control
    inline static bool ctrlKeyPressed = false;
    // Variables for mouse control
    inline static bool leftMouseButtonPressed = false;
    inline static bool rightMouseButtonPressed = false;
    inline static int lastMouseLocationX{};
    inline static int lastMouseLocationY{};
    bool mouseButtonLeftDown{};
    // Taking care of the screen size (mapping of mouse coordinates to angle/translation)
    inline static float mouseRotationFactor = 0.1f;
    inline static float wheelRotation{};

    InteractionHandler();
    ~InteractionHandler();


    static void setEyeZ(float ieyeZ);
    static float getEyeZInc() ;
    void setEyeZInc(float ieyeZInc);

    static void setAngleXaxis(float iangleXaxis);

    static void setAngleYaxis(float iangleYaxis);
    static float getAngleXaxisInc() ;
    static void setAngleXaxisInc(float iangleXaxisInc);
    static float getAngleYaxisInc() ;
    static void setAngleYaxisInc(float iangleYaxisInc);

    static void setxPosition(float ixPosition);

    static void setyPosition(float iyPosition);
    static float getxPositionInc() ;
    static void setxPositionInc(float ixPositionInc);
    static float getyPositionInc() ;
    static void setyPositionInc(float iyPositionInc);
    static float getMouseRotationFactor() ;
    static float getMouseTranslationFactor() ;
    static float getMouseWheelScrollFactor() ;


    [[nodiscard]] static float getEyeZ() ;

    [[nodiscard]] static float getAngleXaxis() ;

    [[nodiscard]] static float getAngleYaxis() ;

    [[nodiscard]] static float getxPosition() ;

    [[nodiscard]] static float getyPosition() ;

    //Setting a mouse button callback (GLFW)
    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

    //Setting a key callback (GLFW)
    //Close window by pressing key ESC
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

};

#endif // INTERACTIONHANDLER_H