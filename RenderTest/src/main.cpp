#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "stb_image/stb_image.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

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

    stbi_set_flip_vertically_on_load(1);

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        float positions[16] = {
            -.5f, -.5f,  0.f,  0.f,
             .5f, -.5f,  1.f,  0.f,
             .5f,  .5f,  1.f,  1.f,
            -.5f,  .5f,  0.f,  1.f,
        };

        unsigned int indices[6] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(positions, 16 * sizeof(float));
        VertexBufferLayout layout({ { GL_FLOAT, 2 }, { GL_FLOAT, 2 } });
        IndexBuffer ib(indices, 6);
        va.AddVertexBuffer(vb, layout);
        va.AddIndexBuffer(ib);

        glm::mat4 proj = glm::ortho(-1.f, 1.f, -.75f, .75f, -1.f, 1.f);

        Shader shader("res/shaders/Basic.shader");
        shader.SetUniform4f("u_Color", .2f, .3f, .8f, 1.f);
        shader.SetUniformMat4f("u_MVP", proj);

        Texture texture("res/textures/apple.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        layout.Unbind();
        ib.Unbind();

        float r = 0.f;
        float increment = .05f;

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            shader.SetUniform4f("u_Color", r, .3f, .8f, 1.f);

            renderer.Draw(va, shader);

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