#include <iostream>
#include <GLFW/glfw3.h>
#include "TextLibrary/TextFile.h"
#include "TextLibrary/TextManager.h"
#include "MyGui.h"

GLFWwindow* SetupWindow(); // check below main

int main(int argc, char* argv[])
{
    GLFWwindow* window = SetupWindow();
    MyGui myGui(window);
    ImGuiIO& io = myGui.GetIO();

    if (window == nullptr) return -1;

    TextLibrary::TextManager textManager;

    if (argc == 2)
    {
        textManager.OpenFile(argv[1]);
    }

    while (true)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        // Save Shortcut
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_S))
        {
            if (textManager.SaveFile() == false)
            {
                textManager.SaveAsFile(myGui.SaveFileDialog());
            }
        }

        //if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_ENTER))
        //{
        //    textManager.OpenFile(window);
        //    textManager.m_Content;
        //}

        // Start the Dear ImGui frame
        myGui.StartFrame();

        // Main Window
        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        ImGui::Begin("Notepad--", nullptr, io.ConfigFlags);
        if (ImGui::Button("Open"))
        {
            textManager.OpenFile(myGui.OpenFileDialog());
        }
        ImGui::SameLine();
        if (ImGui::Button("Save"))
        {
            if (textManager.SaveFile() == false)
            {
                textManager.SaveAsFile(myGui.SaveFileDialog());
            }
        }
        ImGui::InputTextMultiline("##Contents", &textManager.m_Content, ImVec2(io.DisplaySize.x, io.DisplaySize.y - 39));
        ImGui::End();

        // Set window title appropriately
        std::string fileName = textManager.GetFileName();
        bool isEdited = textManager.IsEdited();
        if (fileName.empty())
        {
            fileName = "Notepad--";
        }
        if (isEdited)
        {
            fileName += "*";
        }
        glfwSetWindowTitle(window, fileName.c_str());

        // handle user closing window
        if (glfwWindowShouldClose(window))
        {
            if (!isEdited)
            {
                goto closeWindow;
            }

            bool confirmClose = false;
            if (myGui.WarningWindow("Are you sure you want to close without saving?", &confirmClose))
            {
                if (confirmClose)
                {
                    goto closeWindow;
                }
                else glfwSetWindowShouldClose(window, false);
            }
        }

        // Rendering
        myGui.Render();

        glfwSwapBuffers(window);
    }

closeWindow:
    glfwTerminate();
    return 0;
}

GLFWwindow* SetupWindow()
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

    return window;
}