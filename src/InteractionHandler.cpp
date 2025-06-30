// Create an OS Window using Windowing API GLFW  for OpenGL
// (alternative Windowing APIs for OpenGL: GLUT/FreeGLUT, Qt aso.)
// Inspired by https://www.glfw.org/docs/3.3/quick.html and
// https://www.glfw.org/docs/3.3/input_guide.html
// Merijam Gotzes
// 14.03.2024

#include "InteractionHandler.h"



InteractionHandler::~InteractionHandler() = default;

InteractionHandler::InteractionHandler() = default;

float InteractionHandler::getEyeZ() {
    return eyeZ;
}

void InteractionHandler::setEyeZ(float ieyeZ) {
    InteractionHandler::eyeZ = ieyeZ;
}


float InteractionHandler::getEyeZInc() {
    return InteractionHandler::eyeZInc;
}

void InteractionHandler::setEyeZInc(float ieyeZInc) {

}

float InteractionHandler::getAngleXaxis() {
    return InteractionHandler::angleXaxis;
}

void InteractionHandler::setAngleXaxis(float iangleXaxis) {
    InteractionHandler::angleXaxis = iangleXaxis;
}

float InteractionHandler::getAngleYaxis() {
    return InteractionHandler::angleYaxis;
}

void InteractionHandler::setAngleYaxis(float iangleYaxis) {
    InteractionHandler::angleYaxis = iangleYaxis;
}

float InteractionHandler::getAngleXaxisInc() {
    return InteractionHandler::angleXaxisInc;
}

void InteractionHandler::setAngleXaxisInc(float iangleXaxisInc) {
    InteractionHandler::angleXaxisInc = iangleXaxisInc;
}

 float InteractionHandler::getAngleYaxisInc() {
    return InteractionHandler::angleYaxisInc;
}

void InteractionHandler::setAngleYaxisInc(float iangleYaxisInc) {
    InteractionHandler::angleYaxisInc = iangleYaxisInc;
}

float InteractionHandler::getxPosition() {
    return InteractionHandler::xPosition;
}

void InteractionHandler::setxPosition(float ixPosition) {
    InteractionHandler::xPosition = ixPosition;
}

float InteractionHandler::getyPosition() {
    return InteractionHandler::yPosition;
}

void InteractionHandler::setyPosition(float iyPosition) {
    InteractionHandler::yPosition = iyPosition;
}

float InteractionHandler::getxPositionInc() {
    return InteractionHandler::xPositionInc;
}

void InteractionHandler::setxPositionInc(float ixPositionInc) {
    InteractionHandler::xPositionInc = ixPositionInc;
}

float InteractionHandler::getyPositionInc() {
    return InteractionHandler::yPositionInc;
}

void InteractionHandler::setyPositionInc(float iyPositionInc) {
    InteractionHandler::yPositionInc = iyPositionInc;
}

float InteractionHandler::getMouseRotationFactor() {
    return InteractionHandler::mouseRotationFactor;
}

float InteractionHandler::getMouseTranslationFactor() {
    return InteractionHandler::mouseTranslationFactor;
}

float InteractionHandler::getMouseWheelScrollFactor() {
    return InteractionHandler::mouseWheelScrollFactor;
}

//Setting a key callback (GLFW)
//Close window by pressing key ESC
void InteractionHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //InteractionHandler interaction;
    // https://www.glfw.org/docs/3.3/group__keys.html
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if ( key == GLFW_KEY_LEFT_CONTROL || key == GLFW_KEY_RIGHT_CONTROL)
        ctrlKeyPressed = action == GLFW_PRESS;

    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        if (ctrlKeyPressed)
            xPosition += xPositionInc;
        else
            angleYaxis += angleYaxisInc;

    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        if (ctrlKeyPressed)
            xPosition -= xPositionInc;
        else
            angleYaxis -= angleYaxisInc;


    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        if (ctrlKeyPressed)
            yPosition -= yPositionInc;
        else
            angleXaxis += angleXaxisInc;


    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        if (ctrlKeyPressed)
            yPosition += yPositionInc;
        else
            angleXaxis -= angleXaxisInc;


    // Move camera into negative z-direction
    if (key == GLFW_KEY_N && action == GLFW_PRESS)
        eyeZ = eyeZ - eyeZInc;

    // Mover camera into positive z-direction
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
        eyeZ = eyeZ + eyeZInc;
}

//Setting a mouse button callback (GLFW)
void InteractionHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
}

void InteractionHandler::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {

    double xmouse, ymouse;
    glfwGetCursorPos(window, &xmouse,&ymouse);
    currentMouseLocationX = (int) xmouse;
    currentMouseLocationY = (int) ymouse;
    int deltaX = currentMouseLocationX - lastMouseLocationX;
    int deltaY = currentMouseLocationY - lastMouseLocationY;
    lastMouseLocationX = currentMouseLocationX;
    lastMouseLocationY = currentMouseLocationY;

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        //leftMouseButtonPressed = true;

        angleYaxis += angleYaxisInc * mouseRotationFactor * (float) -deltaX;
        angleXaxis += angleXaxisInc * mouseRotationFactor * (float) -deltaY;
        cout << "angleXaxis: " << angleXaxis << endl;
        cout << "angleYaxis: " << angleYaxis << endl;

        return;
    }
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        //rightMouseButtonPressed = true;
        xPosition += xPositionInc * mouseTranslationFactor * (float) -deltaX;
        yPosition += yPositionInc * mouseTranslationFactor * (float) +deltaY;
        cout << "xPosition: " << xPosition << endl;
        cout << "yPosition: " << yPosition << endl;

        return;
    }
}

void InteractionHandler::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    wheelRotation = (float) yoffset;

    if (wheelRotation!=0)
        eyeZ += eyeZInc * mouseWheelScrollFactor * wheelRotation;
}


