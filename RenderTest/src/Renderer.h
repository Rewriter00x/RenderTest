#pragma once

#include <GL/glew.h>

class VertexArray;
class Shader;

#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCall(x)\
    GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Draw(const VertexArray& va, const Shader& shader) const;
    void Clear() const;

};
