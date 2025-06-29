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
    GLsizei numbOfObjects = 14;
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
    //inits für Shapes
    initObjectA();
    initObjectB();
    initObject2();
    initObject3();
    initObject4();
    initObject5();
    initCony();
    initIce();
    initCube();
    initRoof();
    initField();
    initBall();

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

//init-Funktionen für Shapes
void GameRenderer::initObjectA(){
    // BEGIN: Prepare a sphere for drawing (object 0)
    // create sphere data for rendering a sphere using an index array into a vertex array
    glBindVertexArray(vertex_array_object[12]);
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
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[12]);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (sphere0.getNoOfVertices() * sizeof(sphereVertices[0])),
                 sphereVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[12]);

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
    glBindVertexArray(vertex_array_object[13]);
    shaderProgramB = ShaderProgram();
    shaderProgramB.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAMEb),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAMEb));

    GLfloat color1[3] = {0.1f, 0.1f, 0.8f};
    box0 = Box();
    GLfloat* cubeVertices = box0.makeBoxVertices( 0.8f,  0.5f, 0.4f, color1);
    GLint* cubeIndices = box0.makeBoxIndicesForTriangleStrip();

    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[13]);
    // floats use 4 bytes in Java
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (box0.getNoOfVerticesForBox() * sizeof(cubeVertices[0])),
                 cubeVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[13]);
    // integers use 4 bytes
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (box0.getNoOfIndicesForBox() * sizeof(cubeIndices[0])),
                 cubeIndices, GL_STATIC_DRAW);

    // Activate and order vertex buffer object data for the vertex shader
    // The vertex buffer contains: position (3), color (3), normals (3)
    // Defining input for vertex shader
    // Pointer for the vertex shader to the position information per vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(cubeVertices[0]), nullptr);
    // Pointer for the vertex shader to the color information per vertex
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(cubeVertices[0]),
                          (void *) (3 * sizeof(cubeVertices[0])));
    // Pointer for the vertex shader to the normal information per vertex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(cubeVertices[0]),
                          (void *) (6 * sizeof(cubeVertices[0])));
    // END: Prepare cube for drawing

}

void GameRenderer::initObject2(){
    glBindVertexArray(vertex_array_object[2]);
    shaderProgram2 = ShaderProgram();
    shaderProgram2.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAME2),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAME2));

    GLfloat color2[3] = {0.2f, 0.8f, 0.2f};
    cone0 = Cone(64);
    GLfloat* coneVertices = cone0.makeVertices( 0.2f,  0.6f, 1.0f, color2);
    GLint* coneIndices = cone0.makeIndicesForTriangleStrip();

    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[2]);
    // floats use 4 bytes in Java
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (cone0.getNoOfVertices() * sizeof(coneVertices[0])),
                 coneVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[2]);
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
    glBindVertexArray(vertex_array_object[3]);
    shaderProgram3 = ShaderProgram();
    shaderProgram3.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAME3),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAME3));

    GLfloat color3[3] = {0.8f, 0.8f, 0.1f};
    roof0 = Roof();
    GLfloat* roofVertices = roof0.makeVertices( 0.8f,  1.1f, 0.5f, color3);
    GLint* roofIndices = roof0.makeIndicesForTriangleStrip();

    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[3]);
    // floats use 4 bytes in Java
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (roof0.getNoOfVertices() * sizeof(roofVertices[0])),
                 roofVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[3]);
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

void GameRenderer::initObject4(){
    glBindVertexArray(vertex_array_object[4]);
    shaderProgram2 = ShaderProgram();
    shaderProgram2.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAME2),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAME2));

    GLfloat color4[3] = {0.6f, 0.4f, 0.2f};
    treelog = Cone(32);
    GLfloat* treelogVertices = treelog.makeVertices( 0.1f,  0.1f, 0.8f, color4);
    GLint* treelogIndices = treelog.makeIndicesForTriangleStrip();

    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[4]);
    // floats use 4 bytes in Java
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (treelog.getNoOfVertices() * sizeof(treelogVertices[0])),
                 treelogVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[4]);
    // integers use 4 bytes
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (treelog.getNoOfIndices() * sizeof(treelogIndices[0])),
                 treelogIndices, GL_STATIC_DRAW);

    // Activate and order vertex buffer object data for the vertex shader
    // The vertex buffer contains: position (3), color (3), normals (3)
    // Defining input for vertex shader
    // Pointer for the vertex shader to the position information per vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(treelogVertices[0]), nullptr);
    // Pointer for the vertex shader to the color information per vertex
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(treelogVertices[0]),
                          (void *) (3 * sizeof(treelogVertices[0])));
    // Pointer for the vertex shader to the normal information per vertex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(treelogVertices[0]),
                          (void *) (6 * sizeof(treelogVertices[0])));
    // END: Prepare cube for drawing
}

void GameRenderer::initObject5(){
    glBindVertexArray(vertex_array_object[5]);
    shaderProgram2 = ShaderProgram();
    shaderProgram2.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAME2),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAME2));

    GLfloat color5[3] = {0.2f, 1.0f, 0.4f};
    treecrown = Cone(32);
    GLfloat* treecrownVertices = treecrown.makeVertices( 0.001f,  0.3f, 0.6f, color5);
    GLint* treecrownIndices = treecrown.makeIndicesForTriangleStrip();

    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[5]);
    // floats use 4 bytes in Java
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (treecrown.getNoOfVertices() * sizeof(treecrownVertices[0])),
                 treecrownVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[5]);
    // integers use 4 bytes
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (treecrown.getNoOfIndices() * sizeof(treecrownIndices[0])),
                 treecrownIndices, GL_STATIC_DRAW);

    // Activate and order vertex buffer object data for the vertex shader
    // The vertex buffer contains: position (3), color (3), normals (3)
    // Defining input for vertex shader
    // Pointer for the vertex shader to the position information per vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(treecrownVertices[0]), nullptr);
    // Pointer for the vertex shader to the color information per vertex
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(treecrownVertices[0]),
                          (void *) (3 * sizeof(treecrownVertices[0])));
    // Pointer for the vertex shader to the normal information per vertex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(treecrownVertices[0]),
                          (void *) (6 * sizeof(treecrownVertices[0])));
    // END: Prepare cube for drawing
}

void GameRenderer::initCony(){
    glBindVertexArray(vertex_array_object[6]);
    shaderProgram2 = ShaderProgram();
    shaderProgram2.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAME2),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAME2));

    GLfloat color6[3] = {0.9f, 0.8f, 0.6f};
    cony = Cone(32);
    GLfloat* conyVertices = cony.makeVertices( 0.2f,  0.001f, 0.8f, color6);
    GLint* conyIndices = cony.makeIndicesForTriangleStrip();

    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[6]);
    // floats use 4 bytes in Java
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (cony.getNoOfVertices() * sizeof(conyVertices[0])),
                 conyVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[6]);
    // integers use 4 bytes
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (cony.getNoOfIndices() * sizeof(conyIndices[0])),
                 conyIndices, GL_STATIC_DRAW);

    // Activate and order vertex buffer object data for the vertex shader
    // The vertex buffer contains: position (3), color (3), normals (3)
    // Defining input for vertex shader
    // Pointer for the vertex shader to the position information per vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(conyVertices[0]), nullptr);
    // Pointer for the vertex shader to the color information per vertex
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(conyVertices[0]),
                          (void *) (3 * sizeof(conyVertices[0])));
    // Pointer for the vertex shader to the normal information per vertex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(conyVertices[0]),
                          (void *) (6 * sizeof(conyVertices[0])));
    // END: Prepare cube for drawing
}

void GameRenderer::initIce(){
    glBindVertexArray(vertex_array_object[7]);
    // Shader program for object 0
    shaderProgramA = ShaderProgram();
    shaderProgramA.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAMEa),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAMEa));

    GLfloat color7[3] = {0.9f, 0.7f, 0.8f};
    ice = Sphere(32, 32);
    GLfloat* iceVertices = ice.makeVertices(0.18f, color7);
    GLint* iceIndices = ice.makeIndicesForTriangleStrip();

    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[7]);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (ice.getNoOfVertices() * sizeof(iceVertices[0])),
                 iceVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[7]);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (ice.getNoOfIndices() * sizeof(iceIndices[0])),
                 iceIndices, GL_STATIC_DRAW);

    // Activate and order vertex buffer object data for the vertex shader
    // Defining input variables for vertex shader
    // Pointer for the vertex shader to the position information per vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(iceVertices[0]), nullptr);
    // Pointer for the vertex shader to the color information per vertex
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(iceVertices[0]), (void*) (3 * sizeof(iceVertices[0])));
    // Pointer for the vertex shader to the normal information per vertex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(iceVertices[0]), (void*) (6 * sizeof(iceVertices[0])));
    // END: Prepare sphere for drawing
}

void GameRenderer::initCube(){
    glBindVertexArray(vertex_array_object[8]);
    shaderProgramB = ShaderProgram();
    shaderProgramB.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAMEb),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAMEb));

    GLfloat color8[3] = {0.8f, 0.3f, 0.9f};
    cube = Box();
    GLfloat* cubeVertices = cube.makeBoxVertices( 0.8f,  0.4f, 0.4f, color8);
    GLint* cubeIndices = cube.makeBoxIndicesForTriangleStrip();

    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[8]);
    // floats use 4 bytes in Java
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (cube.getNoOfVerticesForBox() * sizeof(cubeVertices[0])),
                 cubeVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[8]);
    // integers use 4 bytes
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (cube.getNoOfIndicesForBox() * sizeof(cubeIndices[0])),
                 cubeIndices, GL_STATIC_DRAW);

    // Activate and order vertex buffer object data for the vertex shader
    // The vertex buffer contains: position (3), color (3), normals (3)
    // Defining input for vertex shader
    // Pointer for the vertex shader to the position information per vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(cubeVertices[0]), nullptr);
    // Pointer for the vertex shader to the color information per vertex
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(cubeVertices[0]),
                          (void *) (3 * sizeof(cubeVertices[0])));
    // Pointer for the vertex shader to the normal information per vertex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(cubeVertices[0]),
                          (void *) (6 * sizeof(cubeVertices[0])));
    // END: Prepare cube for drawing
}

void GameRenderer::initRoof(){
    glBindVertexArray(vertex_array_object[9]);
    shaderProgram3 = ShaderProgram();
    shaderProgram3.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAME3),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAME3));

    GLfloat color9[3] = {0.2f, 0.8f, 0.6f};
    roof = Roof();
    GLfloat* roofVertices = roof.makeVertices( 0.6f,  0.8f, 0.4f, color9);
    GLint* roofIndices = roof.makeIndicesForTriangleStrip();

    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[9]);
    // floats use 4 bytes in Java
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (roof.getNoOfVertices() * sizeof(roofVertices[0])),
                 roofVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[9]);
    // integers use 4 bytes
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (roof.getNoOfIndices() * sizeof(roofIndices[0])),
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

void GameRenderer::initField(){
    glBindVertexArray(vertex_array_object[10]);
    shaderProgramB = ShaderProgram();
    shaderProgramB.loadShaderAndCreateProgram(const_cast<char *>(SHADER_PATH),
                                              const_cast<char *>(VERTEX_SHADER_FILE_NAMEb),
                                              const_cast<char *>(FRAGMENT_SHADER_FILE_NAMEb));

    GLfloat color10[3] = {0.3f, 0.3f, 0.3f};
    field = Box();
    GLfloat* fieldVertices = field.makeBoxVertices( 10.0f,  0.1f, 10.0f, color10);
    GLint* fieldIndices = field.makeBoxIndicesForTriangleStrip();

    // activate and initialize vertex buffer object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[10]);
    // floats use 4 bytes in Java
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (field.getNoOfVerticesForBox() * sizeof(fieldVertices[0])),
                 fieldVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[10]);
    // integers use 4 bytes
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (field.getNoOfIndicesForBox() * sizeof(fieldIndices[0])),
                 fieldIndices, GL_STATIC_DRAW);

    // Activate and order vertex buffer object data for the vertex shader
    // The vertex buffer contains: position (3), color (3), normals (3)
    // Defining input for vertex shader
    // Pointer for the vertex shader to the position information per vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(fieldVertices[0]), nullptr);
    // Pointer for the vertex shader to the color information per vertex
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(fieldVertices[0]),
                          (void *) (3 * sizeof(fieldVertices[0])));
    // Pointer for the vertex shader to the normal information per vertex
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(fieldVertices[0]),
                          (void *) (6 * sizeof(fieldVertices[0])));
    // END: Prepare cube for drawing
}

void GameRenderer::initBall(){
    // BEGIN: Prepare a sphere for drawing (object 0)
    // create sphere data for rendering a sphere using an index array into a vertex array
    glBindVertexArray(vertex_array_object[11]);
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
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[11]);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (ball.getNoOfVertices() * sizeof(ballVertices[0])),
                 ballVertices, GL_STATIC_DRAW);

    // activate and initialize index buffer object (IBO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object[11]);

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
    //displayObjectB();
    //displayObject2();
    //displayObject3();
    //displayObject4();
    //displayObject5();
    //displayCony();
    //displayIce();
    //serialHouse(0.6f, 5);
    displayField();

    if (grid != nullptr) {
        glBindVertexArray(grid->getVAO());
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe zum testen
        glDrawElements(GL_TRIANGLES, grid->getIndexCount(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    float time = glfwGetTime();
    displayBall(time);


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

    glBindVertexArray(vertex_array_object[12]);
    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLE_STRIP, sphere0.getNoOfIndices(), GL_UNSIGNED_INT, nullptr);
}

void GameRenderer::displayObjectB(){

    // Get a handle for our "MV" and "MVP" uniform
    // Only during the initialisation
    GLint mp_location = glGetUniformLocation(shaderProgramB.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgramB.getShaderProgramID(), "modelviewMatrix");

    //glBindVertexArray(vertex_array_object);
    glUseProgram(shaderProgramB.getShaderProgramID());

    glm::mat4x4  model(1.0f);
    model = glm::translate(modelviewMat, glm::vec3(0.0f, 1.5f, 0.0f));
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &model[0][0]);
    glBindVertexArray(vertex_array_object[13]);
    // Draws the elements in the order defined by the index buffer object (IBO)
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
    glBindVertexArray(vertex_array_object[2]);
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
    glBindVertexArray(vertex_array_object[3]);
    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLE_STRIP, roof0.getNoOfIndices(), GL_UNSIGNED_INT, nullptr);
}

void GameRenderer::displayObject4(){

    // Get a handle for our "MV" and "MVP" uniform
    // Only during the initialisation
    GLint mp_location = glGetUniformLocation(shaderProgram2.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgram2.getShaderProgramID(), "modelviewMatrix");

    //glBindVertexArray(vertex_array_object);
    glUseProgram(shaderProgram2.getShaderProgramID());

    glm::mat4x4  model(1.0f);
    model = glm::translate(modelviewMat, glm::vec3(0.0f, 0.0f, 0.0f));

    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &model[0][0]);
    glBindVertexArray(vertex_array_object[4]);
    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLE_STRIP, treelog.getNoOfIndices(), GL_UNSIGNED_INT, nullptr);
}

void GameRenderer::displayObject5(){

    // Get a handle for our "MV" and "MVP" uniform
    // Only during the initialisation
    GLint mp_location = glGetUniformLocation(shaderProgram2.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgram2.getShaderProgramID(), "modelviewMatrix");

    //glBindVertexArray(vertex_array_object);
    glUseProgram(shaderProgram2.getShaderProgramID());

    glm::mat4x4  model(1.0f);
    model = glm::translate(modelviewMat, glm::vec3(0.0f, 0.7f, 0.0f));
    //model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &model[0][0]);
    glBindVertexArray(vertex_array_object[5]);
    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLE_STRIP, treecrown.getNoOfIndices(), GL_UNSIGNED_INT, nullptr);
}

void GameRenderer::displayCony(){
    GLint mp_location = glGetUniformLocation(shaderProgram2.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgram2.getShaderProgramID(), "modelviewMatrix");

    //glBindVertexArray(vertex_array_object);
    glUseProgram(shaderProgram2.getShaderProgramID());

    glm::mat4x4  model(1.0f);
    model = glm::translate(modelviewMat, glm::vec3(0.0f, 0.0f, 0.6f));

    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &model[0][0]);
    glBindVertexArray(vertex_array_object[6]);
    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLE_STRIP, cony.getNoOfIndices(), GL_UNSIGNED_INT, nullptr);
}

void GameRenderer::displayIce(){
    GLint mp_location = glGetUniformLocation(shaderProgramA.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgramA.getShaderProgramID(), "modelviewMatrix");

    //glBindVertexArray(vertex_array_object);
    glUseProgram(shaderProgramA.getShaderProgramID());

    glm::mat4x4  model(1.0f);

    model = glm::translate(modelviewMat, glm::vec3(0.0, 0.44, 0.6));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &model[0][0]);

    glBindVertexArray(vertex_array_object[7]);
    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLE_STRIP, ice.getNoOfIndices(), GL_UNSIGNED_INT, nullptr);
}

void GameRenderer::displayHouse(float z){
    glm::mat4x4  model(1.0f);

    model = glm::translate(modelviewMat, glm::vec3(0.0f, 0.0f, 0.0f + z));
    displayCube(model);

    model = glm::translate(modelviewMat, glm::vec3(0.0f, 0.4f, 0.0f + z));
    displayRoof(model);
}

void GameRenderer::displayCube(glm::mat4x4 m){
    GLint mp_location = glGetUniformLocation(shaderProgramB.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgramB.getShaderProgramID(), "modelviewMatrix");

    //glBindVertexArray(vertex_array_object);
    glUseProgram(shaderProgramB.getShaderProgramID());

    glm::mat4x4  model = m;
    //model = glm::translate(modelviewMat, glm::vec3(0.0f, 0.0f, 0.0f));

    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &model[0][0]);
    glBindVertexArray(vertex_array_object[8]);
    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLE_STRIP, cube.getNoOfIndicesForBox(), GL_UNSIGNED_INT, nullptr);
}

void GameRenderer::displayRoof(glm::mat4x4 m){
    GLint mp_location = glGetUniformLocation(shaderProgram3.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgram3.getShaderProgramID(), "modelviewMatrix");

    //glBindVertexArray(vertex_array_object);
    glUseProgram(shaderProgram3.getShaderProgramID());

    glm::mat4x4  model = m;
    //model = glm::translate(modelviewMat, glm::vec3(0.0f, 0.4f, 0.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &model[0][0]);
    glBindVertexArray(vertex_array_object[9]);
    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLE_STRIP, roof.getNoOfIndices(), GL_UNSIGNED_INT, nullptr);
}

void GameRenderer::serialHouse(float z, int a){
    for(int i=0; i<a; i++){
        displayHouse(i * z);
    }
}

void GameRenderer::displayField(){
    GLint mp_location = glGetUniformLocation(shaderProgramB.getShaderProgramID(), "projectionMatrix");
    GLint mv_location = glGetUniformLocation(shaderProgramB.getShaderProgramID(), "modelviewMatrix");

    //glBindVertexArray(vertex_array_object);
    glUseProgram(shaderProgramB.getShaderProgramID());

    glm::mat4x4  model(0.1f);
    model = glm::translate(modelviewMat, glm::vec3(0.0f, -0.05f, 0.0f));

    glUniformMatrix4fv(mp_location, 1, GL_FALSE, &projMat[0][0]);
    glUniformMatrix4fv(mv_location, 1, GL_FALSE, &model[0][0]);
    glBindVertexArray(vertex_array_object[10]);
    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLE_STRIP, field.getNoOfIndicesForBox(), GL_UNSIGNED_INT, nullptr);
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

    glBindVertexArray(vertex_array_object[11]);
    // Draws the elements in the order defined by the index buffer object (IBO)
    glDrawElements(GL_TRIANGLE_STRIP, ball.getNoOfIndices(), GL_UNSIGNED_INT, nullptr);
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