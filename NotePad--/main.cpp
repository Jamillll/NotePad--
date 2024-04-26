#include <iostream>
#include "TextFile.h"
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

int main(int argc, char* argv[])
{
    using namespace std;

    if (argc != 2) return 1;
    TextFile file(argv[1]);

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Notepad--", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
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

    string contents = file.GetContent();
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
        ImGui::InputTextMultiline("##Contents", &contents, ImVec2(io.DisplaySize.x, io.DisplaySize.y - 20));
        ImGui::End();

        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_S))
        {
            file.CommitContent(contents);
        }

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}