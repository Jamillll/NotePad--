#include <iostream>
#include <GLFW/glfw3.h>
#include "TextFile.h"
#include "TextManager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

GLFWwindow* SetupWindow(ImGuiIO& io); // check below main

int main(int argc, char* argv[])
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    GLFWwindow* window = SetupWindow(io);

    if (window == nullptr) return -1;

    TextManager textManager;

    if (argc == 2)
    {
        TextFile* file = new TextFile(argv[1]);
        textManager.OpenFile(file);
    }

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        ImGui::Begin("Notepad--", nullptr, io.ConfigFlags);
        ImGui::InputTextMultiline("##Contents", &textManager.m_Content, ImVec2(io.DisplaySize.x, io.DisplaySize.y - 20));
        ImGui::End();

        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_S))
        {
            textManager.SaveContent(window);
        }

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

GLFWwindow* SetupWindow(ImGuiIO& io)
{
    if (!glfwInit())
        return nullptr;

    GLFWwindow* window = glfwCreateWindow(640, 480, "Notepad--", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    io.ConfigFlags |= ImGuiWindowFlags_NoTitleBar;
    io.ConfigFlags |= ImGuiWindowFlags_NoMove;
    io.ConfigFlags |= ImGuiWindowFlags_NoResize;
    io.ConfigFlags |= ImGuiWindowFlags_NoCollapse;
    io.ConfigFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    io.ConfigFlags |= ImGuiWindowFlags_NoBackground;

    ImGui::StyleColorsDark();
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    return window;
}