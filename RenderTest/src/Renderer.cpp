#include "Renderer.h"

#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    bool res = true;
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): "
            << function << ' ' << file << ": " << line << std::endl;
        res = false;
    }

    return res;
}

void GLUnbindAll()
{
    GLCall(glBindVertexArray(0));
    GLCall(glUseProgram(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
