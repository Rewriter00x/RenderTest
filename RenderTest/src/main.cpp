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
#include "glm/ext/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
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
            -50.f,  -50.f,  0.f,  0.f,
             50.f,  -50.f,  1.f,  0.f,
             50.f,   50.f,  1.f,  1.f,
            -50.f,   50.f,  0.f,  1.f,
        };

        unsigned int indices[6] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexBuffer vb(positions, 16 * sizeof(float));
        VertexBufferLayout layout({ { GL_FLOAT, 2 }, { GL_FLOAT, 2 } });
        IndexBuffer ib(indices, 6);
        VertexArray va(vb, layout, ib);

        glm::mat4 proj = glm::ortho(0.f, 1920.f, 0.f, 1080.f, -1.f, 1.f); // our space
        glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f)); // our pov

        Shader shader("res/shaders/Basic.shader");

        Texture texture("res/textures/apple.png");
        texture.BindToSlot(0);
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        layout.Unbind();
        ib.Unbind();

        Renderer renderer;

        glm::vec3 translationA(200.f, 200.f, 0.f);
        glm::vec3 translationB(400.f, 200.f, 0.f);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                glm::mat4 model = glm::translate(glm::mat4(1.f), translationA); // object transform
                glm::mat4 mvp = proj * view * model;

                shader.SetUniformMat4f("u_MVP", mvp);

                renderer.Draw(va, shader);
            }

            {
                glm::mat4 model = glm::translate(glm::mat4(1.f), translationB); // object transform
                glm::mat4 mvp = proj * view * model;

                shader.SetUniformMat4f("u_MVP", mvp);

                renderer.Draw(va, shader);
            }

            {
                ImGui::Begin("Hello, world!");

                ImGui::SliderFloat("TranslationA X", &translationA.x, 0.0f, 1920.0f);    
                ImGui::SliderFloat("TranslationA Y", &translationA.y, 0.0f, 1080.0f);
                ImGui::SliderFloat("TranslationB X", &translationB.x, 0.0f, 1920.0f);
                ImGui::SliderFloat("TranslationB Y", &translationB.y, 0.0f, 1080.0f);
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}