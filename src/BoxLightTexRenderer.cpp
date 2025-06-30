// Create an OS Window using Windowing API GLFW  for OpenGL
// (alternative Windowing APIs for OpenGL: GLUT/FreeGLUT, Qt aso.)
// Inspired by https://www.glfw.org/docs/3.3/quick.html and
// https://www.glfw.org/docs/3.3/input_guide.html
// Merijam Gotzes
// 14.03.2024, 02.05.2024


#define GLM_ENABLE_EXPERIMENTAL

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "BoxLightTexRenderer.h"
#include "InteractionHandler.h"

// Constructor: Initialize matrices and create the sphere object
BoxLightTexRenderer::BoxLightTexRenderer() {
    projMat = glm::mat4x4 (1.0f);
    viewMat = glm::mat4x4 (1.0f);
    // Create one sphere geometry that will be used for both eyes
    sphere0 = new Sphere(1.0f, 32, 16); // radius=1, 32 sectors, 16 stacks
}

BoxLightTexRenderer::~BoxLightTexRenderer() {
    delete sphere0;
}

void BoxLightTexRenderer::init() {
    // BEGIN: Preparing scene
    // BEGIN: Allocating vertex array objects and buffers for each object
    glGenVertexArrays(NUMB_OF_OBJECTS, vertex_array_object);
    glGenBuffers(NUMB_OF_OBJECTS, vertex_buffer);
    glGenBuffers(NUMB_OF_OBJECTS, index_buffer_object);

    // Initialize objects to be drawn
    initObject0(); // Box
    initObject1(); // Pyramid
    initObject2(); // Sphere (for eyes)

    // Load shader once
    shaderProgram0 = ShaderProgram();
    shaderProgram0.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAME0),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAME0));

    // Specify light parameters
    GLfloat lightPosition[4] = {0.0f, 3.0f, 5.0f, 1.0f};
    GLfloat lightAmbientColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightDiffuseColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightSpecularColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    light0 = LightSource(lightPosition, lightAmbientColor,
                             lightDiffuseColor, lightSpecularColor);

    // Switch on back face culling and depth test
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);

    // Set background color
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    InteractionHandler::setEyeZ(5.0f);
}

// Initializes the Box geometry and material
void BoxLightTexRenderer::initObject0() {
    glBindVertexArray(vertex_array_object[0]);

    GLfloat color0[3] = {0.7f, 0.7f, 0.7f};
    GLfloat* cubeVertices = box0.makeBoxVertices( 1.0f,  0.87f, 1.0f, color0);
    GLint* cubeIndices = box0.makeBoxIndicesForTriangleStrip();

    // Activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (box0.getNoOfVerticesForBox() * 11 * sizeof(GLfloat)),
                 cubeVertices, GL_STATIC_DRAW);

    // Activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (box0.getNoOfIndicesForBox() * sizeof(GLint)),
                 cubeIndices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(9 * sizeof(GLfloat)));

    // Material for snake skin
    GLfloat matEmission[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat matAmbient[4] =  {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat matDiffuse[4] =  {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat matSpecular[4] = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat matShininess = 32.0f;
    material0 = Material(matEmission, matAmbient, matDiffuse, matSpecular, matShininess);

    // Load and prepare texture
    int width = 0, height = 0, bitDepth = 0;
    string TEXTURE_PATH_FILE = string(TEXTURE_PATH) + string(TEXTURE_FILE_NAME0);
    unsigned char* textureData = stbi_load(TEXTURE_PATH_FILE.c_str(), &width, &height, &bitDepth, 0);
    if (!textureData) {
        cout << "Failed to find: " <<  TEXTURE_PATH_FILE << endl;
    }

    glGenTextures(1, &textureID0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(textureData);
}

// Initializes the Pyramid geometry
void BoxLightTexRenderer::initObject1() {
    glBindVertexArray(vertex_array_object[1]);

    GLfloat color0[3] = {0.7f, 0.7f, 0.7f};
    GLfloat* pyramidVertices = pyramid0.makePyramidVertices(1.0f, 0.87f, 1.0f, color0);
    GLint* pyramidIndices = pyramid0.makePyramidIndices();

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, pyramid0.getNoOfVerticesForPyramid() * 11 * sizeof(GLfloat), pyramidVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, pyramid0.getNoOfIndicesForPyramid() * sizeof(GLint), pyramidIndices, GL_STATIC_DRAW);

    // Set vertex attribute pointers (same layout as box)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(9 * sizeof(GLfloat)));
}

// Initializes the Sphere geometry and material
void BoxLightTexRenderer::initObject2() {
    glBindVertexArray(vertex_array_object[2]);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[2]);
    glBufferData(GL_ARRAY_BUFFER, sphere0->getVertexSize(), sphere0->getVertices(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere0->getIndexCount() * sizeof(GLuint), sphere0->getIndices(), GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(9 * sizeof(GLfloat)));

    // Material for the black eyes
    GLfloat matEmission[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat matAmbient[4]  = {0.01f, 0.01f, 0.01f, 1.0f};
    GLfloat matDiffuse[4]  = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat matSpecular[4] = {0.05f, 0.05f, 0.05f, 1.0f};
    GLfloat matShininess   = 10.0f;
    materialEyes = Material(matEmission, matAmbient, matDiffuse, matSpecular, matShininess);
}


// Main display function, called every frame
void BoxLightTexRenderer::display(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    if (width == 0 || height == 0) {
        return;
    }

    ratio = (float)width / (float)height;
    glViewport(0, 0, width, height);

    // Set up camera (view matrix)
    viewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, InteractionHandler::getEyeZ()), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // Set up projection matrix
    projMat = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 10000.0f);

    // Create base model matrix for the entire snake from user interaction
    glm::mat4 translMat = glm::translate(glm::vec3(InteractionHandler::getxPosition(), InteractionHandler::getyPosition(), 0.0f));
    glm::mat4 rot1Mat = glm::rotate(InteractionHandler::getAngleXaxis(), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 rot2Mat = glm::rotate(InteractionHandler::getAngleYaxis(), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 baseModelMat = translMat * rot2Mat * rot1Mat;

    //Activate shader and bind texture
    glUseProgram(shaderProgram0.getShaderProgramID());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID0);


    // 1. Draw the head box
    drawObject(0, box0.getNoOfIndicesForBox(), GL_TRIANGLE_STRIP, baseModelMat, material0, true);

    // 2. Draw the Pyramid (nose), attached to the front of the head box
    glm::mat4 pyramidModelMat = baseModelMat * glm::translate(glm::vec3(0.0f, 0.0f, 0.5f));
    drawObject(1, pyramid0.getNoOfIndicesForPyramid(), GL_TRIANGLES, pyramidModelMat, material0, true);

    // 3. Draw the Eyes
    glm::mat4 eyeScale = glm::scale(glm::vec3(0.1f, 0.1f, 0.1f));
    glm::mat4 eye1ModelMat = pyramidModelMat * glm::translate(glm::vec3(-0.25f, 0.15f, 0.5f)) * eyeScale;
    drawObject(2, sphere0->getIndexCount(), GL_TRIANGLES, eye1ModelMat, materialEyes, false);
    glm::mat4 eye2ModelMat = pyramidModelMat * glm::translate(glm::vec3(0.25f, 0.15f, 0.5f)) * eyeScale;
    drawObject(2, sphere0->getIndexCount(), GL_TRIANGLES, eye2ModelMat, materialEyes, false);

    //draw snake segments
    float boxLength = 1.0f;
    float gap = 0.2f;
    for (int i = 1; i <= numberOfBodySegments; ++i) {
        // Berechne die Position für jedes Segment
        // Jedes Segment wird hinter das vorherige verschoben
        float zOffset = -i * (boxLength + gap);
        glm::mat4 segmentTranslation = glm::translate(glm::vec3(0.0f, 0.0f, zOffset));

        // Die Transformation des Segments basiert auf der Transformation des Kopfes
        glm::mat4 segmentModelMat = baseModelMat * segmentTranslation;

        // Zeichne  Segment. Wir können die Geometrie des Kopf-Würfels wiederverwenden (Index 0)
        drawObject(0, box0.getNoOfIndicesForBox(), GL_TRIANGLE_STRIP, segmentModelMat, material0, true);
    }
}

/**
 * Generic function to draw an object with a given transformation, material, and texture setting.
 * @param objectIndex The VAO index for the object.
 * @param indexCount The number of indices to draw.
 * @param drawMode The OpenGL draw mode (e.g., GL_TRIANGLES).
 * @param modelMatrix The object's model matrix (world transformation).
 * @param material The material properties for the object.
 * @param useTexture Boolean to tell the shader whether to apply the texture.
 */
void BoxLightTexRenderer::drawObject(int objectIndex, int indexCount, GLenum drawMode, const glm::mat4& modelMatrix, const Material& material, bool useTexture) {
    // Get uniform locations
    GLint proj_location = glGetUniformLocation(shaderProgram0.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgram0.getShaderProgramID(), "modelviewMatrix");
    GLint mvit_location = glGetUniformLocation(shaderProgram0.getShaderProgramID(), "modelviewITMatrix");
    GLint useTex_location = glGetUniformLocation(shaderProgram0.getShaderProgramID(), "useTexture");
    GLint tex_location = glGetUniformLocation(shaderProgram0.getShaderProgramID(), "tex");

    // Calculate and send matrices
    glm::mat4 modelviewMat = viewMat * modelMatrix;
    glm::mat4 modelviewITMat = glm::transpose(glm::inverse(modelviewMat));
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &modelviewMat[0][0]);
    glUniformMatrix4fv(mvit_location, 1, GL_FALSE, &modelviewITMat[0][0]);

    // Transfer light and material parameters using hardcoded layout locations
    glUniform4fv(4, 1, light0.getAmbient());
    glUniform4fv(5, 1, light0.getDiffuse());
    glUniform4fv(6, 1, light0.getSpecular());

    glUniform4fv(7, 1, material.getEmission());
    glUniform4fv(8, 1, material.getAmbient());
    glUniform4fv(9, 1, material.getDiffuse());
    glUniform4fv(10, 1, material.getSpecular());
    glUniform1f(11, material.getShininess());

    // Tell the shader which texture unit to use for the 'tex' sampler
    glUniform1i(tex_location, 0);

    // Tell the shader whether to use the texture or not
    glUniform1i(useTex_location, useTexture);

    // Bind the VAO for the specific object and draw it
    glBindVertexArray(vertex_array_object[objectIndex]);
    glDrawElements(drawMode, indexCount, GL_UNSIGNED_INT, nullptr);
}


void BoxLightTexRenderer::reshape(GLFWwindow* window) {
    display(window);
    glfwSwapBuffers(window);
    glFinish();
}

void BoxLightTexRenderer::dispose() {
    glUseProgram(0);
    shaderProgram0.deleteShaderProgram();

    // Unbind and delete all OpenGL objects
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);

    glDeleteVertexArrays(NUMB_OF_OBJECTS, vertex_array_object);
    glDeleteBuffers(NUMB_OF_OBJECTS, vertex_buffer);
    glDeleteBuffers(NUMB_OF_OBJECTS, index_buffer_object);
    glDeleteTextures(1, &textureID0);

    // Statische Arrays werden nicht mit delete[] gelöscht

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
}
