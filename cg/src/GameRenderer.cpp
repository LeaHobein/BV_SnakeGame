#define GLM_ENABLE_EXPERIMENTAL

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "GameRenderer.h"
#include "InteractionHandler.h"

GameRenderer::GameRenderer(){ //= default;
    modelviewMat = glm::mat4x4 (1.0f);
    projMat = glm::mat4x4 (1.0f);

}

GameRenderer::~GameRenderer() = default;

void GameRenderer::init() {
    // BEGIN: Preparing scene
    // BEGIN: Allocating vertex array objects and buffers for each object
    GLsizei numbOfObjects = 2;
    // create vertex array objects for noOfObjects objects (VAO)
    vertex_array_object = new GLuint[numbOfObjects];
    glGenVertexArrays(numbOfObjects, vertex_array_object);
    if (vertex_array_object[0] < 1)
        cout << "Error allocating vertex array object (VAO)." << endl;

    // create vertex buffer objects for noOfObjects objects (VBO)
    vertex_buffer = new GLuint[numbOfObjects];
    glGenBuffers(numbOfObjects, vertex_buffer);
    if (vertex_buffer[0] < 1)
        cout << "Error allocating vertex buffer object (VBO)." << endl;

    // create index buffer objects for noOfObjects objects (IBO)
    index_buffer_object = new GLuint[numbOfObjects];
    glGenBuffers(numbOfObjects, index_buffer_object);
    if (index_buffer_object[0] < 1)
        cout << "Error allocating index buffer object." << endl;
    // END: Allocating vertex array objects and buffers for each object

    // Initialize objects to be drawn (see respective sub-methods)
    initObject0();
    initObject1();

    // Specify light parameters
    GLfloat lightPosition[4] = {0.0f, 3.0f, 3.0f, 1.0f};
    GLfloat lightAmbientColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightDiffuseColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightSpecularColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    light0 = LightSource(lightPosition, lightAmbientColor,
                         lightDiffuseColor, lightSpecularColor);

    // Switch on back face culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //   glCullFace(GL_FRONT);
    // Switch on depth test
    glEnable(GL_DEPTH_TEST);

    // defining polygon drawing mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Set background color
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    InteractionHandler::setEyeZ(0.5f);

}
void GameRenderer::initObject1(){
    glBindVertexArray(vertex_array_object[1]);
    shaderProgram1 = ShaderProgram();
    shaderProgram1.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAME0),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAME0));

    banana = Model();
    banana.loadModel("../resources/banana/banana_mod.obj");

    vector<Mesh> bananaMeshes = banana.getMeshes();
    vector<vertex> bananaVertices = banana.getVertices(bananaMeshes[0]);
    vector<GLuint> bananaIndices = banana.getIndices(bananaMeshes[0]);

    vector<GLfloat> Vertices;

    for (int i = 0; i < bananaVertices.size(); i++) {
        Vertices.push_back(bananaVertices[i].position.x);
        Vertices.push_back(bananaVertices[i].position.y);
        Vertices.push_back(bananaVertices[i].position.z);
        Vertices.push_back(bananaVertices[i].normal.x);
        Vertices.push_back(bananaVertices[i].normal.y);
        Vertices.push_back(bananaVertices[i].normal.z);
        Vertices.push_back(bananaVertices[i].texcoords.x);
        Vertices.push_back(bananaVertices[i].texcoords.y);
    }
    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[1]);
    // floats use 4 bytes in Java
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (Vertices.size() * sizeof(Vertices[0])),
                 &Vertices[0], GL_STATIC_DRAW);
    //&bunnyVertices[0]
    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[1]);
    // integers use 4 bytes
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (bananaIndices.size() * sizeof(bananaIndices[0])),
                 &bananaIndices[0], GL_STATIC_DRAW);

    // Activate and order vertex buffer object data for the vertex shader
    // The vertex buffer contains: position (3), normals (3), texture coordinates (2)
    // Defining input for vertex shader
    // Pointer for the vertex shader to the position information per vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(Vertices[0]), nullptr);
    // Pointer for the vertex shader to the normal information per vertex
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(Vertices[0]),
                          (void *) (3 * sizeof(Vertices[0])));
    // Pointer for the vertex shader to the texture coordinates information per vertex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(Vertices[0]),
                          (void *) (6 * sizeof(Vertices[0])));

    // Specification of material parameters (blue material)
    /*float matEmission[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float matAmbient[4] =  {0.0f, 0.0f, 0.1f, 1.0f};
    float matDiffuse[4] =  {0.1f, 0.2f, 0.7f, 1.0f};
    float matSpecular[4] = {0.7f, 0.7f, 0.7f, 1.0f};
    float matShininess = 200.0f;*/

    // Metallic material
    GLfloat matEmission[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat matAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat matDiffuse[4] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat matSpecular[4] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat matShininess = 200.0f;

    material0 = Material(matEmission, matAmbient, matDiffuse, matSpecular, matShininess);

    // Load and prepare texture
    /*int width = 0;
    int height = 0;
    int bitDepth = 0;*/
    int width = 612;
    int height = 464;
    int bitDepth = 24;
    GLuint textureID = 1;

    string TEXTURE_PATH_FILE2 = string(BANANA_TEXTURE_PATH) + string(BANANA_TEXTURE_FILE_NAME0);
    const char *texturePathAndFileName2 = TEXTURE_PATH_FILE2.c_str();

    unsigned char *texture2 = stbi_load(texturePathAndFileName2, &width, &height, &bitDepth, 3);
    if (!texture2) {
        cout << "Failed to find: " << texturePathAndFileName2 << endl;
    }
    cout<<texturePathAndFileName2<<endl;
    // Activate and use texture as 2D texture (might have to go to "display()")
    glGenTextures(2, &textureID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // set the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // load the texture in OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(texture2);

    // END: Prepare bunny for drawing
}

void GameRenderer::initObject0() {
    glBindVertexArray(vertex_array_object[0]);
    shaderProgram0 = ShaderProgram();
    shaderProgram0.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAME0),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAME0));

    //loading Standford bunny
    /*bunny.loadModel("../resources/bunny/reconstruction/bun_zipper.ply");*/
    bunny = Model();
    bunny.loadModel("../resources/apple/apple_mod.obj");


    vector<Mesh> bunnyMeshes = bunny.getMeshes();
    vector<vertex> bunnyVertices = bunny.getVertices(bunnyMeshes[0]);
    vector<GLuint> bunnyIndices = bunny.getIndices(bunnyMeshes[0]);


    // The vertex buffer should contain: position (3), normals (3), texture coordinates (2)
    vector<GLfloat> Vertices;
    for (int i = 0; i < bunnyVertices.size(); i++) {
        Vertices.push_back(bunnyVertices[i].position.x);
        Vertices.push_back(bunnyVertices[i].position.y);
        Vertices.push_back(bunnyVertices[i].position.z);
        Vertices.push_back(bunnyVertices[i].normal.x);
        Vertices.push_back(bunnyVertices[i].normal.y);
        Vertices.push_back(bunnyVertices[i].normal.z);
        Vertices.push_back(bunnyVertices[i].texcoords.x);
        Vertices.push_back(bunnyVertices[i].texcoords.y);
    }


    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[0]);
    // floats use 4 bytes in Java
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (Vertices.size() * sizeof(Vertices[0])),
                 &Vertices[0], GL_STATIC_DRAW);
    //&bunnyVertices[0]
    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[0]);
    // integers use 4 bytes
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (bunnyIndices.size() * sizeof(bunnyIndices[0])),
                 &bunnyIndices[0], GL_STATIC_DRAW);

    // Activate and order vertex buffer object data for the vertex shader
    // The vertex buffer contains: position (3), normals (3), texture coordinates (2)
    // Defining input for vertex shader
    // Pointer for the vertex shader to the position information per vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(Vertices[0]), nullptr);
    // Pointer for the vertex shader to the normal information per vertex
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(Vertices[0]),
                          (void *) (3 * sizeof(Vertices[0])));
    // Pointer for the vertex shader to the texture coordinates information per vertex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(Vertices[0]),
                          (void *) (6 * sizeof(Vertices[0])));

    // Specification of material parameters (blue material)
    /*float matEmission[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float matAmbient[4] =  {0.0f, 0.0f, 0.1f, 1.0f};
    float matDiffuse[4] =  {0.1f, 0.2f, 0.7f, 1.0f};
    float matSpecular[4] = {0.7f, 0.7f, 0.7f, 1.0f};
    float matShininess = 200.0f;*/

    // Metallic material
    GLfloat matEmission[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat matAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat matDiffuse[4] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat matSpecular[4] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat matShininess = 200.0f;

    material0 = Material(matEmission, matAmbient, matDiffuse, matSpecular, matShininess);

    // Load and prepare texture
    /*int width = 0;
    int height = 0;
    int bitDepth = 0;*/
    int width = 612;
    int height = 464;
    int bitDepth = 24;
    GLuint textureID = 0;

    string TEXTURE_PATH_FILE = string(TEXTURE_PATH) + string(TEXTURE_FILE_NAME0);
    const char *texturePathAndFileName = TEXTURE_PATH_FILE.c_str();

    unsigned char *texture = stbi_load(texturePathAndFileName, &width, &height, &bitDepth, 3);
    if (!texture) {
        cout << "Failed to find: " << texturePathAndFileName << endl;
    }
    cout<<texturePathAndFileName<<endl;
    // Activate and use texture as 2D texture (might have to go to "display()")
    glGenTextures(2, &textureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // set the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // load the texture in OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(texture);

    // END: Prepare bunny for drawing
}


void GameRenderer::display(GLFWwindow* window) {

    //Clear and set a color to the background (GLAD)
    glClearColor(0.97f, 0.97f, 0.97f, 1.0f);
    //Clear the frame buffer (GLAD)
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    //Switch on depth test
    glEnable(GL_DEPTH_TEST);

    float ratio;
    int width, height;
    glm::mat4x4 lookAtMat, rot1Mat, rot2Mat, translMat;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = (float) width / (float) height;
    glViewport(0, 0, width, height);


    //Apply view transform
    //Camera positioning is steered by the interaction handler
    //setup camera
    cout << "EyeZ: "<< InteractionHandler::getEyeZ() << endl;

    lookAtMat= glm::lookAt(glm::vec3(0.0f, 0.0f, InteractionHandler::getEyeZ()), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0.0f,1.0f,0.0f));
    translMat = glm::translate(glm::vec3(InteractionHandler::getxPosition(), InteractionHandler::getyPosition(), 0.0f));
    rot1Mat = glm::rotate(InteractionHandler::getAngleXaxis(),glm::vec3(1.0f, 0.0f, 0.0f));
    rot2Mat = glm::rotate(InteractionHandler::getAngleYaxis(),glm::vec3(0.0f, 1.0f, 0.0f));

    // Controlling the interaction settings
    cout << "Camera: z = " << InteractionHandler::getEyeZ() << ", " <<
         "x-Rot: " << InteractionHandler::getAngleXaxis() <<
         ", y-Rot: " << InteractionHandler::getAngleYaxis() <<
         ", x-Translation: " << InteractionHandler::getxPosition() <<
         ", y-Translation: " << InteractionHandler::getyPosition() << endl;// definition of translation of model (Model/Object Coordinates --> World Coordinates)


    //Model view matrix
    // Model is located at the origin (0,0,0): First rotate then translate.
    // Model : transMat * rot2Mat * rot1Mat * identMat;
    // View : lookAtMat
    modelviewMat = lookAtMat * translMat * rot2Mat * rot1Mat;

    // Projection matrix
    projMat = glm::perspective(glm::radians(45.0f), (GLfloat) ratio, 0.1f, 10000.0f);

    float lightPos[3] = {0.0f, 3.0f, 0.0f};

    displayObject0(lightPos);
    displayObject1(lightPos);

}


void GameRenderer::displayObject0(float* LightPosition){

    // Get a handle for our "MV" and "MVP" uniform
    // Only during the initialisation
    GLint mp_location = glGetUniformLocation(shaderProgram0.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgram0.getShaderProgramID(), "modelviewMatrix");
    GLint mvit_location = glGetUniformLocation(shaderProgram0.getShaderProgramID(), "modelviewITMatrix");

    //glBindVertexArray(vertex_array_object);
    glUseProgram(shaderProgram0.getShaderProgramID());

    // transpose inverse of the actual model view matrix for calculation with the normals
    glm::mat4x4 modelviewITMat(1.0f);
    modelviewITMat = glm::transpose(glm::inverse(modelviewMat));

    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &modelviewMat[0][0]);
    glUniformMatrix4fv(mvit_location, 1, GL_FALSE, &modelviewITMat[0][0]);

    // transfer parameters of light source
    glUniform4fv(3, 1, light0.getPosition());
    glUniform4fv(4, 1, light0.getAmbient());
    glUniform4fv(5, 1, light0.getDiffuse());
    glUniform4fv(6, 1, light0.getSpecular());

    // transfer material parameters
    glUniform4fv(7, 1, material0.getEmission());
    glUniform4fv(8, 1, material0.getAmbient());
    glUniform4fv(9, 1, material0.getDiffuse());
    glUniform4fv(10, 1, material0.getSpecular());
    glUniform1f(11, material0.getShininess());

    glBindVertexArray(vertex_array_object[0]);

    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLES, (GLsizei) bunny.getNoOfIndices(bunny), GL_UNSIGNED_INT, nullptr);
}

void GameRenderer::displayObject1(float* LightPosition){

    // Get a handle for our "MV" and "MVP" uniform
    // Only during the initialisation
    GLint mp_location = glGetUniformLocation(shaderProgram1.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgram1.getShaderProgramID(), "modelviewMatrix");
    GLint mvit_location = glGetUniformLocation(shaderProgram1.getShaderProgramID(), "modelviewITMatrix");

    //glBindVertexArray(vertex_array_object);
    glUseProgram(shaderProgram1.getShaderProgramID());

    // transpose inverse of the actual model view matrix for calculation with the normals
    glm::mat4x4 modelviewITMat(1.0f);
    modelviewITMat = glm::transpose(glm::inverse(modelviewMat));

    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &modelviewMat[0][0]);
    glUniformMatrix4fv(mvit_location, 1, GL_FALSE, &modelviewITMat[0][0]);

    // transfer parameters of light source
    glUniform4fv(3, 1, light0.getPosition());
    glUniform4fv(4, 1, light0.getAmbient());
    glUniform4fv(5, 1, light0.getDiffuse());
    glUniform4fv(6, 1, light0.getSpecular());

    // transfer material parameters
    glUniform4fv(7, 1, material0.getEmission());
    glUniform4fv(8, 1, material0.getAmbient());
    glUniform4fv(9, 1, material0.getDiffuse());
    glUniform4fv(10, 1, material0.getSpecular());
    glUniform1f(11, material0.getShininess());

    glBindVertexArray(vertex_array_object[1]);

    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLES, (GLsizei) banana.getNoOfIndices(banana), GL_UNSIGNED_INT, nullptr);

}


void GameRenderer::reshape(GLFWwindow* window) {
    display(window);
    glfwSwapBuffers(window);
    // important, waits until rendering result in double buffering is done,
    // making resizing less ugly
    glFinish();
}

void GameRenderer::dispose() {
    glUseProgram(0);
    glUseProgram(1);
    shaderProgram0.deleteShaderProgram();
    shaderProgram1.deleteShaderProgram();

    //glDeleteProgram(shaderProgram0.getShaderProgramID());
    //Vertex Array Object (VAO) und Vertex Buffer (VBO) freigeben
    glBindVertexArray(0);
    glBindVertexArray(1);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteVertexArrays(1, vertex_array_object);
    glDeleteBuffers(1, vertex_buffer);
    glDeleteBuffers(1, index_buffer_object);

    // Textur und Ressourcen freigeben
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_TEXTURE_2D, 1);

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
}