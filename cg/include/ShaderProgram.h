#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

using namespace std;

class ShaderProgram
{
public:
    inline static int shaderProgramID;

    ShaderProgram();
    ~ShaderProgram();

    /**
     * @return the OpenGL ID of the shader program
     */
    int getShaderProgramID() ;

    /**
     * Deletes the shader program associated with this  object
     * (and stored in the field shaderProgramID).
     */
    void deleteShaderProgram();
    /**
     * Loads a vertex and a fragment shader from two files,
     * creeates a shader program object (on the GPU)
     * and links the shaders to this shader program.
     * The shader program ID is stores in an instance variable of this program object.
     * @param path Directory path of the shader files
     * @param vertexShaderFileName  File name (including file name extension) of the
     * vertex shader)
     * @param fragmentShaderFileName File name (including file name extension) of the
     * fragment shader)
     */
    void loadShaderAndCreateProgram(const char* path, const char* vertexShaderFileName,
                                           const char* fragmentShaderFileName);


    /**
     * Creates a shader object, compiles a shader of a given
     * shader typefrom a character string array.
     * Checks compile status and outputs the error log.
     *
     * @param shaderType OpenGL shader type (e.g. GL_VERTEX_SHADER)
     * @param ShaderString CHaracter string conating the shader source code
     * @return OpenGL shader ID (on the GPU)
     */
    int createAndCompileShader(int shaderType, const string& ShaderString);


private:

    /** Loads the contents of a (text) file into a string variable.
   * @param fileName name of the file including the (relative) path
   * @return contents of the (text) file
   */
    string loadFileToString(const string& fileName);

    // Utility function for checking shader compilation/linking errors.
    void checkCompileErrors(unsigned int shader, const string& type);

};

#endif //SHADERPROGRAM_H