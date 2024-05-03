#pragma once
#include "imgui.h"
#include "imgui_stdlib.h"
#include <GLFW/glfw3.h>

class MyGui
{
public:
	MyGui(GLFWwindow* window);
	~MyGui();

	void StartFrame();
	void Render();

	ImGuiIO& GetIO();

private:
	void SetDarkStyle();
};