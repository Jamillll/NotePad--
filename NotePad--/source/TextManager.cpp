#include "TextManager.h"

#include <windows.h>
#include <commdlg.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

TextManager::TextManager(TextFile* inputFile)
{
	m_TextFile = inputFile;
	m_Content = m_TextFile->GetContent();
}

TextManager::TextManager()
{
}

void TextManager::OpenFile(TextFile* inputFile)
{
	m_TextFile = inputFile;
	m_Content = m_TextFile->GetContent();
}

void TextManager::SaveContent(GLFWwindow* window)
{
	if (m_TextFile != nullptr)
	{
		m_TextFile->CommitContent(&m_Content);
	}
	else
	{
		//Windows API sorcery to summon the save dialog window

		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window(window);
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = "Text File (*.txt)\0*.txt\0";
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

		if (GetSaveFileNameA(&ofn) == true)
		{
			m_TextFile = new TextFile(ofn.lpstrFile);
			m_TextFile->CommitContent(&m_Content);
		}
	}
}

TextManager::~TextManager()
{
	delete m_TextFile;
}
