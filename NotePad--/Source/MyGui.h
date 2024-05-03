#pragma once
#include "imgui.h"
#include "imgui_stdlib.h"
#include <GLFW/glfw3.h>

class MyGui
{
private:
	GLFWwindow* m_Window = nullptr;

public:
	MyGui(GLFWwindow* window);
	~MyGui();

	void StartFrame();
	void Render();

	std::string SaveFileDialog();
	std::string OpenFileDialog();

	ImGuiIO& GetIO();

private:
	void SetDarkStyle();
};