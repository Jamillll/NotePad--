#pragma once
#include "TextFile.h"
#include <GLFW/glfw3.h>

class TextManager
{
private:
	TextFile* m_TextFile = nullptr;

public:
	std::string m_Content;

	TextManager(TextFile* inputFile);
	TextManager();

	std::string GetFileName();

	void OpenFile(TextFile* inputFile);
	void SaveContent(GLFWwindow* window);

	~TextManager();
};