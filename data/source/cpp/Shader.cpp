#include "../header/shader.h"
#include "../header/glsl.h"
#include <stdio.h>

const char* VERTEX_FILE   = "data/source/shader/vertexShader.vert";
const char* FRAGMENT_FILE = "data/source/shader/fragmentShader.frag";

ShaderManager::ShaderManager(const char* vertex_filename, const char* fragment_filename)
{
    vertexShaderID   = loadShader(vertex_filename, GL_VERTEX_SHADER);
    fragmentShaderID = loadShader(fragment_filename, GL_FRAGMENT_SHADER);
    programID        = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    bindAttribute(0, "position");
    glLinkProgram(programID);
    glValidateProgram(programID);
}
// /////////////////////////////////////////////
// unsigned long ShaderManager::getFileLength(std::ifstream& file)
// {
//     if (!file.good())
//         return 0;

//     unsigned long pos = file.tellg();
//     file.seekg(0, std::ios::end);
//     unsigned long len = file.tellg();
//     file.seekg(std::ios::beg);

//     return len;
// }

// int ShaderManager::loadShaderFile(const char* filename, GLchar** ShaderSource, unsigned long* len)
// {
//     std::ifstream file;
//     file.open(filename, std::ios::in); // opens as ASCII!
//     if (!file)
//         return -1;

//     *len = getFileLength(file);

//     if (len == 0)
//         return -2; // Error: Empty File

//     *ShaderSource = (GLchar*)new char[*len + 1];
//     if (*ShaderSource == 0)
//         return -3; // can't reserve memory

//     *ShaderSource[*len] = 0;

//     unsigned int i = 0;
//     while (file.good()) {
//         *ShaderSource[i] = file.get(); // get character from file.
//         if (!file.eof())
//             i++;
//     }

//     *ShaderSource[i] = 0; // 0-terminate it at the correct position

//     file.close();

//     return 0; // No Error
// }

// int ShaderManager::unloadshader(GLbyte** ShaderSource)
// {
//     if (*ShaderSource != 0)
//         delete[] * ShaderSource;
//     *ShaderSource = 0;
// }

/////////////////////////////////////////////
void ShaderManager::start()
{
    glUseProgram(programID);
}
void ShaderManager::stop()
{
    glUseProgram(0);
}
void ShaderManager::bindAttribute(int attribute, const char* variableName)
{
    glBindAttribLocation(programID, attribute, variableName);
}

GLuint ShaderManager::loadShader(const char* file, int type)
{
    GLuint ShaderID = glCreateShader(type);
    //読み込み/////////////////////////////////////////////
    if (readShaderSource(ShaderID, file))
        exit(1);
    //コンパイル///////////////////////////////////////////
    GLint compiled;
    glCompileShader(ShaderID);
    glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        printf("error compile shader\n");
    }

    return ShaderID;
}

void ShaderManager::bindAttributes()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StaticShader::StaticShader()
    : ShaderManager(VERTEX_FILE, FRAGMENT_FILE)
{
}
void StaticShader::bindAttributes()
{
    bindAttribute(0, "position");
}