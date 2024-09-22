#include "Renderer.h"

#include <iostream>

#include "VertexArray.h"
#include "Shader.h"

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

void Renderer::Draw(const VertexArray& va, const Shader& shader) const
{
    va.Bind();
    shader.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
