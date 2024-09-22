#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cerr << "GLEW_NOT_OK" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        float positions[8] = {
            -.5f, -.5f,
             .5f, -.5f,
             .5f,  .5f,
            -.5f,  .5f,
        };

        unsigned int indices[6] = {
            0, 1, 2,
            2, 3, 0
        };

        VertexArray va;
        VertexBuffer vb(positions, 8 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        Shader shader("res/shaders/Basic.shader");
        shader.SetUniform4f("u_Color", .2f, .3f, .8f, 1.f);

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        layout.Unbind();
        ib.Unbind();

        float r = 0.f;
        float increment = .05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GLClearScreen();

            shader.Bind();
            shader.SetUniform4f("u_Color", r, .3f, .8f, 1.f);

            va.Bind();

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            if (r > 1.f || r < 0.f)
                increment *= -1;

            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}