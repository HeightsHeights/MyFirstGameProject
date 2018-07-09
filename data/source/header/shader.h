#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glut.h>
#include <fstream>

class ShaderManager {
private:
    GLuint programID;
    GLuint vertexShaderID;
    GLuint fragmentShaderID;

    static unsigned long getFileLength(std::ifstream &file);
    static int loadShaderFile(const char *filename, GLchar **ShaderSource, unsigned long *len);
    static int unloadshader(GLbyte **ShaderSource);

    static GLuint loadShader(const char *file, int type);

public:
    ShaderManager(const char *vertex_filename, const char *fragment_filename);
    void start();
    void stop();
    void cleanUp();

protected:
    virtual void bindAttributes() = 0;
    void bindAttribute(int attribute, const char *variableName);
};

////////////////////////////////////////////////////////////////
//　
////////////////////////////////////////////////////////////////

class StaticShader : public ShaderManager {
private:
public:
    StaticShader();

protected:
    void bindAttributes();
};