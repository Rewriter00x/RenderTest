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
        std::cerr << "[OpenGL Error] (" << error << "): "
            << function << ' ' << file << ": " << line << std::endl;
        res = false;
    }

    return res;
}

void GLClearScreen()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
