#define GLM_ENABLE_EXPERIMENTAL

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "GameRenderer.h"
#include "InteractionHandler.h"

//Grid
#include "Grid.h"


GameRenderer::GameRenderer(){ //= default;
    modelviewMat = glm::mat4x4 (1.0f);
    projMat = glm::mat4x4 (1.0f);

}

GameRenderer::~GameRenderer() = default;

void GameRenderer::init() {
    // BEGIN: Preparing scene
    // BEGIN: Allocating vertex array objects and buffers for each object
    GLsizei numbOfObjects = 8;
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
    initObject0(); // Apfel (behalten)
    initObject1(); // Banane (behalten)
    initObjectB(); // Schlange/Box (behalten)

    // Die folgenden Objekte werden aktuell nicht verwendet.
    // Ihre init-Funktionen wurden gelöscht, daher müssen wir die Aufrufe auskommentieren.
    // initObjectA();
    // initObject2();
    // initObject3();
    // initBall();
    // initPyramid();


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

    InteractionHandler::setEyeZ(10.0f);
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
        Vertices.push_back(bananaVertices[i].position.x); Vertices.push_back(bananaVertices[i].position.y); Vertices.push_back(bananaVertices[i].position.z);
        Vertices.push_back(bananaVertices[i].normal.x); Vertices.push_back(bananaVertices[i].normal.y); Vertices.push_back(bananaVertices[i].normal.z);
        Vertices.push_back(bananaVertices[i].texcoords.x); Vertices.push_back(bananaVertices[i].texcoords.y);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (Vertices.size() * sizeof(Vertices[0])), &Vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (bananaIndices.size() * sizeof(bananaIndices[0])), &bananaIndices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(Vertices[0]), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(Vertices[0]), (void *) (3 * sizeof(Vertices[0])));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(Vertices[0]), (void *) (6 * sizeof(Vertices[0])));

    int width, height, bitDepth;
    string TEXTURE_PATH_FILE2 = string(BANANA_TEXTURE_PATH) + string(BANANA_TEXTURE_FILE_NAME0);
    unsigned char *texture2 = stbi_load(TEXTURE_PATH_FILE2.c_str(), &width, &height, &bitDepth, 3);

    glGenTextures(1, &bananaTextureID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, bananaTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(texture2);
}

void GameRenderer::initObject0() {
    glBindVertexArray(vertex_array_object[0]);
    shaderProgram0 = ShaderProgram();
    shaderProgram0.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                            const_cast<char *>(VERTEX_SHADER_FILE_NAME0),
                                            const_cast<char *>(FRAGMENT_SHADER_FILE_NAME0));

    bunny = Model();
    bunny.loadModel("../resources/apple/apple_mod.obj");

    vector<Mesh> bunnyMeshes = bunny.getMeshes();
    vector<vertex> bunnyVertices = bunny.getVertices(bunnyMeshes[0]);
    vector<GLuint> bunnyIndices = bunny.getIndices(bunnyMeshes[0]);

    vector<GLfloat> Vertices;
    for (int i = 0; i < bunnyVertices.size(); i++) {
        Vertices.push_back(bunnyVertices[i].position.x); Vertices.push_back(bunnyVertices[i].position.y); Vertices.push_back(bunnyVertices[i].position.z);
        Vertices.push_back(bunnyVertices[i].normal.x); Vertices.push_back(bunnyVertices[i].normal.y); Vertices.push_back(bunnyVertices[i].normal.z);
        Vertices.push_back(bunnyVertices[i].texcoords.x); Vertices.push_back(bunnyVertices[i].texcoords.y);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (Vertices.size() * sizeof(Vertices[0])), &Vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (bunnyIndices.size() * sizeof(bunnyIndices[0])), &bunnyIndices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(Vertices[0]), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(Vertices[0]), (void *) (3 * sizeof(Vertices[0])));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(Vertices[0]), (void *) (6 * sizeof(Vertices[0])));

    GLfloat matEmission[4] = {0.0f, 0.0f, 0.0f, 1.0f}; GLfloat matAmbient[4] = {0.2f, 0.2f, 0.2f, 1.0f}; GLfloat matDiffuse[4] = {0.5f, 0.5f, 0.5f, 1.0f}; GLfloat matSpecular[4] = {0.7f, 0.7f, 0.7f, 1.0f}; GLfloat matShininess = 200.0f;
    material0 = Material(matEmission, matAmbient, matDiffuse, matSpecular, matShininess);

    int width, height, bitDepth;
    string TEXTURE_PATH_FILE = string(TEXTURE_PATH) + string(TEXTURE_FILE_NAME0);
    unsigned char *texture = stbi_load(TEXTURE_PATH_FILE.c_str(), &width, &height, &bitDepth, 3);

    glGenTextures(1, &appleTextureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, appleTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(texture);
}

//init-Funktionen für Shapes
void GameRenderer::initObjectA(){
    // BEGIN: Prepare a sphere for drawing (object 0)
    // create sphere data for rendering a sphere using an index array into a vertex array
    glBindVertexArray(vertex_array_object[2]);
    // Shader program for object 0
    shaderProgramA = ShaderProgram();
    shaderProgramA.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAMEa),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAMEa));

    GLfloat color0[3] = {0.8f, 0.1f, 0.1f};
    sphere0 = Sphere(64, 64);
    GLfloat* sphereVertices = sphere0.makeVertices(0.5f, color0);
    GLint* sphereIndices = sphere0.makeIndicesForTriangleStrip();

    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[2]);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (sphere0.getNoOfVertices() * sizeof(sphereVertices[0])),
                 sphereVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[2]);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (sphere0.getNoOfIndices() * sizeof(sphereIndices[0])),
                 sphereIndices, GL_STATIC_DRAW);

    // Activate and order vertex buffer object data for the vertex shader
    // Defining input variables for vertex shader
    // Pointer for the vertex shader to the position information per vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(sphereVertices[0]), nullptr);
    // Pointer for the vertex shader to the color information per vertex
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(sphereVertices[0]), (void*) (3 * sizeof(sphereVertices[0])));
    // Pointer for the vertex shader to the normal information per vertex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(sphereVertices[0]), (void*) (6 * sizeof(sphereVertices[0])));
    // END: Prepare sphere for drawing
}

void GameRenderer::initObjectB() {
    glBindVertexArray(vertex_array_object[3]);
    shaderProgramB = ShaderProgram();
    shaderProgramB.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                            const_cast<char *>(VERTEX_SHADER_FILE_NAME0),
                                            const_cast<char *>(FRAGMENT_SHADER_FILE_NAME0));

    box0 = Box();
    GLfloat* cubeVertices = box0.makeBoxVerticesWithTex(0.5f, 0.5f, 0.5f);
    GLint* cubeIndices = box0.makeBoxIndicesForTriangleStrip();

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[3]);
    glBufferData(GL_ARRAY_BUFFER, 192 * sizeof(GLfloat), cubeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (box0.getNoOfIndicesForBox() * sizeof(cubeIndices[0])),
                cubeIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (6 * sizeof(GLfloat)));

    int width, height, bitDepth;
    string snakeTexPath = string(SNAKE_TEXTURE_PATH) + string(SNAKE_TEXTURE_FILE_NAME0);
    unsigned char* textureData = stbi_load(snakeTexPath.c_str(), &width, &height, &bitDepth, 3);

    glGenTextures(1, &snakeTextureID);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, snakeTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(textureData);
}

void GameRenderer::initObject2(){
    glBindVertexArray(vertex_array_object[4]);
    shaderProgram2 = ShaderProgram();
    shaderProgram2.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAME2),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAME2));

    GLfloat color2[3] = {0.2f, 0.8f, 0.2f};
    cone0 = Cone(64);
    GLfloat* coneVertices = cone0.makeVertices( 0.2f,  0.6f, 1.0f, color2);
    GLint* coneIndices = cone0.makeIndicesForTriangleStrip();

    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[4]);
    // floats use 4 bytes in Java
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (cone0.getNoOfVertices() * sizeof(coneVertices[0])),
                 coneVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[4]);
    // integers use 4 bytes
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (cone0.getNoOfIndices() * sizeof(coneIndices[0])),
                 coneIndices, GL_STATIC_DRAW);

    // Activate and order vertex buffer object data for the vertex shader
    // The vertex buffer contains: position (3), color (3), normals (3)
    // Defining input for vertex shader
    // Pointer for the vertex shader to the position information per vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(coneVertices[0]), nullptr);
    // Pointer for the vertex shader to the color information per vertex
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(coneVertices[0]),
                          (void *) (3 * sizeof(coneVertices[0])));
    // Pointer for the vertex shader to the normal information per vertex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(coneVertices[0]),
                          (void *) (6 * sizeof(coneVertices[0])));
    // END: Prepare cube for drawing

}

void GameRenderer::initObject3(){
    glBindVertexArray(vertex_array_object[5]);
    shaderProgram3 = ShaderProgram();
    shaderProgram3.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAME3),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAME3));

    GLfloat color3[3] = {0.8f, 0.8f, 0.1f};
    roof0 = Roof();
    GLfloat* roofVertices = roof0.makeVertices( 0.8f,  1.1f, 0.5f, color3);
    GLint* roofIndices = roof0.makeIndicesForTriangleStrip();

    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[5]);
    // floats use 4 bytes in Java
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (roof0.getNoOfVertices() * sizeof(roofVertices[0])),
                 roofVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[5]);
    // integers use 4 bytes
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (roof0.getNoOfIndices() * sizeof(roofIndices[0])),
                 roofIndices, GL_STATIC_DRAW);

    // Activate and order vertex buffer object data for the vertex shader
    // The vertex buffer contains: position (3), color (3), normals (3)
    // Defining input for vertex shader
    // Pointer for the vertex shader to the position information per vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(roofVertices[0]), nullptr);
    // Pointer for the vertex shader to the color information per vertex
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(roofVertices[0]),
                          (void *) (3 * sizeof(roofVertices[0])));
    // Pointer for the vertex shader to the normal information per vertex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(roofVertices[0]),
                          (void *) (6 * sizeof(roofVertices[0])));
    // END: Prepare cube for drawing

}

void GameRenderer::initBall(){
    // BEGIN: Prepare a sphere for drawing (object 0)
    // create sphere data for rendering a sphere using an index array into a vertex array
    glBindVertexArray(vertex_array_object[6]);
    // Shader program for object 0
    shaderProgramA = ShaderProgram();
    shaderProgramA.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAMEa),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAMEa));

    GLfloat color11[3] = {0.2f, 0.9f, 0.3f};
    ball = Sphere(64, 64);
    GLfloat* ballVertices = ball.makeVertices(0.5f, color11);
    GLint* ballIndices = ball.makeIndicesForTriangleStrip();

    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[6]);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (ball.getNoOfVertices() * sizeof(ballVertices[0])),
                 ballVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[6]);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (ball.getNoOfIndices() * sizeof(ballIndices[0])),
                 ballIndices, GL_STATIC_DRAW);

    // Activate and order vertex buffer object data for the vertex shader
    // Defining input variables for vertex shader
    // Pointer for the vertex shader to the position information per vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(ballVertices[0]), nullptr);
    // Pointer for the vertex shader to the color information per vertex
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(ballVertices[0]), (void*) (3 * sizeof(ballVertices[0])));
    // Pointer for the vertex shader to the normal information per vertex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(ballVertices[0]), (void*) (6 * sizeof(ballVertices[0])));
    // END: Prepare sphere for drawing
}

void GameRenderer::initPyramid() {
    glBindVertexArray(vertex_array_object[7]);
    shaderProgramP = ShaderProgram();
    shaderProgramP.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAMEb),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAMEb));

    GLfloat color1[3] = {0.1f, 0.8f, 0.2f};
    pyramid = Pyramid();
    GLfloat* pyramidVertices = pyramid.makePyramidVertices( 2,  2, 2, color1);
    GLint* pyramidIndices = pyramid.makePyramidIndices();

    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[7]);
    // floats use 4 bytes in Java
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (pyramid.getNoOfVerticesForPyramid() * sizeof(pyramidVertices[0])),
                 pyramidVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[7]);
    // integers use 4 bytes
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (pyramid.getNoOfIndicesForPyramid() * sizeof(pyramidIndices[0])),
                 pyramidIndices, GL_STATIC_DRAW);

    // Activate and order vertex buffer object data for the vertex shader
    // The vertex buffer contains: position (3), color (3), normals (3)
    // Defining input for vertex shader
    // Pointer for the vertex shader to the position information per vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(pyramidVertices[0]), nullptr);
    // Pointer for the vertex shader to the color information per vertex
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(pyramidVertices[0]),
                          (void *) (3 * sizeof(pyramidVertices[0])));
    // Pointer for the vertex shader to the normal information per vertex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(pyramidVertices[0]),
                          (void *) (6 * sizeof(pyramidVertices[0])));
    // END: Prepare cube for drawing
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
    //displays für Shapes
    //displayObjectA();
    //displayObject2();
    //displayObject3();

    //displayPyramid();

    if (grid != nullptr) {
        glBindVertexArray(grid->getVAO());
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe zum testen
        glDrawElements(GL_TRIANGLES, grid->getIndexCount(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    float time = glfwGetTime();
    displayObjectB(time);
    //displaySnake(0.6f, 6, time);
    //displayBall(time);


}


void GameRenderer::displayObject0(float* LightPosition){
    glUseProgram(shaderProgram0.getShaderProgramID());
    // ... (Der ganze Code für Matrizen, Licht & Material aus der Originalfunktion bleibt hier)
    GLint mp_location = glGetUniformLocation(shaderProgram0.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgram0.getShaderProgramID(), "modelviewMatrix");
    GLint mvit_location = glGetUniformLocation(shaderProgram0.getShaderProgramID(), "modelviewITMatrix");
    glm::mat4x4 modelviewITMat(1.0f);
    modelviewITMat = glm::transpose(glm::inverse(modelviewMat));
    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &modelviewMat[0][0]);
    glUniformMatrix4fv(mvit_location, 1, GL_FALSE, &modelviewITMat[0][0]);
    glUniform4fv(3, 1, light0.getPosition()); glUniform4fv(4, 1, light0.getAmbient()); glUniform4fv(5, 1, light0.getDiffuse()); glUniform4fv(6, 1, light0.getSpecular());
    glUniform4fv(7, 1, material0.getEmission()); glUniform4fv(8, 1, material0.getAmbient()); glUniform4fv(9, 1, material0.getDiffuse()); glUniform4fv(10, 1, material0.getSpecular()); glUniform1f(11, material0.getShininess());

    // Apfel-Textur auf Slot 0 legen
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, appleTextureID);

    glBindVertexArray(vertex_array_object[0]);
    glDrawElements(GL_TRIANGLES, (GLsizei) bunny.getNoOfIndices(bunny), GL_UNSIGNED_INT, nullptr);
}

void GameRenderer::displayObject1(float* LightPosition){
    glUseProgram(shaderProgram1.getShaderProgramID());
    // ... (Der ganze Code für Matrizen, Licht & Material aus der Originalfunktion bleibt hier)
    GLint mp_location = glGetUniformLocation(shaderProgram1.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgram1.getShaderProgramID(), "modelviewMatrix");
    GLint mvit_location = glGetUniformLocation(shaderProgram1.getShaderProgramID(), "modelviewITMatrix");
    glm::mat4x4 modelviewITMat(1.0f);
    modelviewITMat = glm::transpose(glm::inverse(modelviewMat));
    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &modelviewMat[0][0]);
    glUniformMatrix4fv(mvit_location, 1, GL_FALSE, &modelviewITMat[0][0]);
    glUniform4fv(3, 1, light0.getPosition()); glUniform4fv(4, 1, light0.getAmbient()); glUniform4fv(5, 1, light0.getDiffuse()); glUniform4fv(6, 1, light0.getSpecular());
    glUniform4fv(7, 1, material0.getEmission()); glUniform4fv(8, 1, material0.getAmbient()); glUniform4fv(9, 1, material0.getDiffuse()); glUniform4fv(10, 1, material0.getSpecular()); glUniform1f(11, material0.getShininess());

    // Bananen-Textur auf Slot 0 legen
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bananaTextureID);

    glBindVertexArray(vertex_array_object[1]);
    glDrawElements(GL_TRIANGLES, (GLsizei) banana.getNoOfIndices(banana), GL_UNSIGNED_INT, nullptr);
}

//display-Funktionen für Shapes
void GameRenderer::displayObjectA(){
    // Get a handle for our "MV" and "MVP" uniform
    // Only during the initialisation
    GLint mp_location = glGetUniformLocation(shaderProgramA.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgramA.getShaderProgramID(), "modelviewMatrix");

    //glBindVertexArray(vertex_array_object);
    glUseProgram(shaderProgramA.getShaderProgramID());

    glm::mat4x4  model(1.0f);

    model = glm::translate(modelviewMat, glm::vec3(-1.5, 0, 0));

    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &model[0][0]);

    glBindVertexArray(vertex_array_object[2]);
    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLE_STRIP, sphere0.getNoOfIndices(), GL_UNSIGNED_INT, nullptr);
}

void GameRenderer::displayObjectB(float time){
    glUseProgram(shaderProgramB.getShaderProgramID());
    GLint mp_location = glGetUniformLocation(shaderProgramB.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgramB.getShaderProgramID(), "modelviewMatrix");
    GLint mvit_location = glGetUniformLocation(shaderProgramB.getShaderProgramID(), "modelviewITMatrix");

    // Die originale Bewegungslogik
    glm::mat4x4 model(1.0f);
    float timerZa, timerZb, goZa, goZb, goX, timerX, slitherX, slitherZ, scaleZ;
    if(time < 10.0f){ slitherX = sin(time*6) * 0.1f; timerZa = time; scaleZ = 1; if(time == 0.0f){goZa = 0.0f;} goZa = timerZa * 0.6f; if(goZa >= 4.0f){goZa = 4.0f;} goX = 0; goZb = 0; slitherZ = 0;
    } else if(time >= 10.0f && time < 15.0f){ slitherZ = sin(time*6) * 0.1f; goZa = 4.0f; timerX = time - 10.0f; scaleZ = 2; if(time == 10.0f){goX = 0.0f;} goX = timerX * 0.6f; if(goX >= 2.0f){goX = 2.0f;} slitherX = 0; goZb = 0;
    } else if(time >= 15.0f && time < 25.0f){ slitherX = sin(time*6) * 0.1f; goZa = 4.0f; goX = 2.0f; timerZb = time - 15.0f; scaleZ = 3; if(time == 15.0f){goZb = 0.0f;} goZb = timerZb * 0.6f; if(goZb >= 4.0f){goZb = 4.0f;} slitherZ = 0;
    } else { slitherX = sin(time*6) * 0.1f; goZa = 4.0f; goZb = 4.0f; goX = 2.0f; scaleZ = 4; slitherZ = 0; }
    model = glm::translate(modelviewMat, glm::vec3( 0.0f + slitherX + goX, 0.0f + 0.25f, 4.0f + slitherZ - goZa - goZb));
    model = glm::scale(model, glm::vec3(1, 1, scaleZ));

    glm::mat4x4 modelviewITMat = glm::transpose(glm::inverse(model));
    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(mvit_location, 1, GL_FALSE, &modelviewITMat[0][0]);
    glUniform4fv(3, 1, light0.getPosition()); glUniform4fv(4, 1, light0.getAmbient()); glUniform4fv(5, 1, light0.getDiffuse()); glUniform4fv(6, 1, light0.getSpecular());
    glUniform4fv(7, 1, material0.getEmission()); glUniform4fv(8, 1, material0.getAmbient()); glUniform4fv(9, 1, material0.getDiffuse()); glUniform4fv(10, 1, material0.getSpecular()); glUniform1f(11, material0.getShininess());

    // Schlangen-Textur auf Slot 0 legen
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, snakeTextureID);

    glBindVertexArray(vertex_array_object[3]);
    glDrawElements(GL_TRIANGLE_STRIP, box0.getNoOfIndicesForBox(), GL_UNSIGNED_INT, nullptr);
}

void GameRenderer::displayObject2(){

    // Get a handle for our "MV" and "MVP" uniform
    // Only during the initialisation
    GLint mp_location = glGetUniformLocation(shaderProgram2.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgram2.getShaderProgramID(), "modelviewMatrix");

    //glBindVertexArray(vertex_array_object);
    glUseProgram(shaderProgram2.getShaderProgramID());

    glm::mat4x4  model(1.0f);
    model = glm::translate(modelviewMat, glm::vec3(0.0f, -1.0f, 0.0f));

    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &model[0][0]);
    glBindVertexArray(vertex_array_object[4]);
    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLE_STRIP, cone0.getNoOfIndices(), GL_UNSIGNED_INT, nullptr);
}

void GameRenderer::displayObject3(){

    // Get a handle for our "MV" and "MVP" uniform
    // Only during the initialisation
    GLint mp_location = glGetUniformLocation(shaderProgram3.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgram3.getShaderProgramID(), "modelviewMatrix");

    //glBindVertexArray(vertex_array_object);
    glUseProgram(shaderProgram3.getShaderProgramID());

    glm::mat4x4  model(1.0f);
    model = glm::translate(modelviewMat, glm::vec3(1.5f, 0.0f, 0.0f));

    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &model[0][0]);
    glBindVertexArray(vertex_array_object[5]);
    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLE_STRIP, roof0.getNoOfIndices(), GL_UNSIGNED_INT, nullptr);
}

void GameRenderer::displayBall(float time){
    // Get a handle for our "MV" and "MVP" uniform
    // Only during the initialisation
    GLint mp_location = glGetUniformLocation(shaderProgramA.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgramA.getShaderProgramID(), "modelviewMatrix");

    //glBindVertexArray(vertex_array_object);
    glUseProgram(shaderProgramA.getShaderProgramID());

    glm::mat4x4  model(1.0f);
    float goY = sin(time*3) * 0.3f;
    float spinY = time * 30.0f;
    float timerZa;
    float timerZb;
    float goZa;
    float goZb;
    float goX;
    float timerX;
    float slitherX;
    float slitherZ;
    if(time < 10.0f){
        slitherX = sin(time*6) * 0.1f;
        timerZa = time;
        if(time = 0.0f){goZa = 0.0f;}
        goZa = timerZa * 0.6f;
        if(goZa >= 4.0f){goZa = 4.0f;}
    }
    if(time > 10.0f && time < 15.0f){
        slitherZ = sin(time*6) * 0.1f;
        goZa = 4.0f;
        timerX = time - 10.0f;
        if(time = 10.0f){goX = 0.0f;}
        goX = timerX * 0.6f;
        if(goX >= 2.0f){goX = 2.0f;}
    }
    if(time > 15.0f && time < 25.0f){
        slitherX = sin(time*6) * 0.1f;
        goZa = 4.0f;
        goX = 2.0f;
        timerZb = time - 15.0f;
        if(time = 15.0f){goZb = 0.0f;}
        goZb = timerZb * 0.6f;
        if(goZb >= 4.0f){goZb = 4.0f;}
    }
    if(time > 15.0f){
        goZa = 4.0f;
        goZb = 4.0f;
        goX = 2.0f;
    }

    model = glm::translate(modelviewMat, glm::vec3(0.0f + slitherX + goX,
                                                   0.5f + 0.3f + goY,
                                                   4 + slitherZ - goZa - goZb));
    model = glm::rotate(model, glm::radians(spinY), glm::vec3(0.0f, 1.0f, 0.0f));

    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &model[0][0]);

    glBindVertexArray(vertex_array_object[6]);
    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLE_STRIP, ball.getNoOfIndices(), GL_UNSIGNED_INT, nullptr);
}

void GameRenderer::displayPyramid(){

    // Get a handle for our "MV" and "MVP" uniform
    // Only during the initialisation
    GLint mp_location = glGetUniformLocation(shaderProgramP.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgramP.getShaderProgramID(), "modelviewMatrix");

    //glBindVertexArray(vertex_array_object);
    glUseProgram(shaderProgramP.getShaderProgramID());

    glm::mat4x4  model(1.0f);


    /*model = glm::translate(modelviewMat, glm::vec3(
        0.0f + slitherX + goX,
        0.0f + 0.25f,
        4 + slitherZ - goZa - goZb));*/
    model = glm::translate(modelviewMat, glm::vec3(0.0f,1.1f,0.0f));
    //model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //model = glm::scale(model, glm::vec3(1, 1, scaleZ));

    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &model[0][0]);
    glBindVertexArray(vertex_array_object[7]);
    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLE_STRIP, pyramid.getNoOfIndicesForPyramid(), GL_UNSIGNED_INT, nullptr);
}

void::GameRenderer::displaySnake(float z, int a, float time) {
    /*for (int i=0; i<a; i++) {
       displayObjectB(i * z, time);
    }*/
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
    //Shapes
    shaderProgramA.deleteShaderProgram();
    shaderProgramB.deleteShaderProgram();
    shaderProgram2.deleteShaderProgram();
    shaderProgram3.deleteShaderProgram();

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