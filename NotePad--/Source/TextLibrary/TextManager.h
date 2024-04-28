#pragma once
#include "TextFile.h"
#include <GLFW/glfw3.h>

namespace TextLibrary
{
	class TextManager
	{
	private:
		TextFile* m_TextFile = nullptr;
		bool m_IsEdited = false;
		std::string m_OriginalContent;

	public:
		std::string m_Content;

		TextManager(TextFile* inputFile);
		TextManager();

		std::string GetFileName();

		bool IsEdited();

		void OpenFile(TextFile* inputFile);
		void OpenFile(GLFWwindow* window);
		void SaveFile(GLFWwindow* window);

		~TextManager();
	};
};