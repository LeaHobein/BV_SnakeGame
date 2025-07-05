#include <string>
#include "ShaderProgram.h"


    //Constructor
    ShaderProgram::ShaderProgram()= default;
    ShaderProgram::~ShaderProgram() = default;

    /**
     * @return the OpenGL ID of the shader program
     */
    int ShaderProgram::getShaderProgramID() {
        return shaderProgramID;
    }

    /**
    * Deletes the shader program associated with this  object
    * (and stored in the field shaderProgramID).
    */
    void ShaderProgram::deleteShaderProgram() {
    glDeleteProgram(shaderProgramID);
    }
    /**
     * Loads a vertex and a fragment shader from two files,
     * creates a shader program object (on the GPU)
     * and links the shaders to this shader program.
     * The shader program ID is stores in an instance variable of this program object.
     * @param path Directory path of the shader files
     * @param vertexShaderFileName  File name (including file name extension) of the
     * vertex shader)
     * @param fragmentShaderFileName File name (including file name extension) of the
     * fragment shader)
     */
    void ShaderProgram::loadShaderAndCreateProgram(const char* path, const char* vertexShaderFileName,
                                    const char* fragmentShaderFileName) {

        shaderProgramID = glCreateProgram();

        //Load vertex shader source from file
        string vertexShaderString;
        //string vertexCode;
        int vertexShader;
        string vertexPathAndFileName = string(path) +  string(vertexShaderFileName);
        vertexShaderString = loadFileToString(vertexPathAndFileName);
        vertexShader = createAndCompileShader(GL_VERTEX_SHADER, vertexShaderString);
        //Load fragment shader source from file
        string fragmentShaderString;
        int fragmentShader;
        string fragmentPathAndFileName = string(path) + string (fragmentShaderFileName);
        fragmentShaderString = loadFileToString(fragmentPathAndFileName);
        fragmentShader = createAndCompileShader(GL_FRAGMENT_SHADER,fragmentShaderString);
        // Create the shader program object and attach the shader object to it.
        // Stores the OpenGL shader program ID in the instance variable shaderProgramID.
        glAttachShader(shaderProgramID, vertexShader);
        glAttachShader(shaderProgramID, fragmentShader);
        // Link the program
        glLinkProgram(shaderProgramID);

        checkCompileErrors(shaderProgramID, "PROGRAM");

        // The shader objects can be deleted because they are linked to the program.
        glDetachShader(shaderProgramID, vertexShader);
        glDeleteShader(vertexShader);
        glDetachShader(shaderProgramID, fragmentShader);
        glDeleteShader(fragmentShader);
    }

    /**
     * Creates a shader object, compiles a shader of a given
     * shader typefrom a character string array.
     * Checks compile status and outputs the error log.
     *
     * @param shaderType OpenGL shader type (e.g. GL_VERTEX_SHADER)
     * @param ShaderString Character string conating the shader source code
     * @return OpenGL shader ID (on the GPU)
     */
    int ShaderProgram::createAndCompileShader(int shaderType, const string& ShaderString){
        int shader;
        const char *ShaderCode = ShaderString.c_str();
        shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &ShaderCode, nullptr);
        glCompileShader(shader);
        if(shaderType == GL_VERTEX_SHADER)
            checkCompileErrors(shader, "VERTEX");
        else
            checkCompileErrors(shader, "FRAGMENT");

        return shader;
    }

    /** Loads the contents of a (text) file into a string variable.
   * @param fileName name of the file including the (relative) path
   * @return contents of the (text) file
   */
    string ShaderProgram::loadFileToString(const string& fileName) {
        ifstream ShaderFile;
        string fileContent;
        // Enable ifstream objects to throw exceptions:
        try {
            stringstream ShaderStream;
            // open files
            ShaderFile.open(fileName);
            // read file's buffer contents into streams
            ShaderStream << ShaderFile.rdbuf();
            // close file handlers
            ShaderFile.close();
            // convert stream into string
            fileContent = ShaderStream.str();
        }
        catch (ifstream::failure e) {
            cout << "Shader files couldn't be read successfully!" << endl;
        }
        return fileContent;
    }   

    // Utility function for checking shader compilation/linking errors.
    void ShaderProgram::checkCompileErrors(unsigned int shader, const string& type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                cout <<"Error, shader compilation, type: " << type << "-------" << infoLog << endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                cout << "Error, program linking, type: " << type << "-------" << infoLog << endl;
            }
        }
    }







