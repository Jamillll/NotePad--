#include "TextManager.h"

#include <sstream>
#include <vector>

#include <windows.h>
#include <commdlg.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

TextManager::TextManager(TextFile* inputFile)
{
	m_TextFile = inputFile;
	m_Content = m_TextFile->GetContent();
	m_OriginalContent = m_TextFile->GetContent();
}

TextManager::TextManager()
{

}

std::string TextManager::GetFileName()
{
	if (m_TextFile == nullptr) return "";

	std::string filePath = m_TextFile->GetPath();
	std::string output;

	std::stringstream stringStream(filePath);
	std::vector<std::string> strings;

	while (getline(stringStream, output, '\\'))
	{
		strings.push_back(output);
	}

	return strings[strings.size() - 1];
}

bool TextManager::IsEdited()
{
	return m_Content != m_OriginalContent;
	;
}

void TextManager::OpenFile(TextFile* inputFile)
{
	m_TextFile = inputFile;
	m_Content = m_TextFile->GetContent();
	m_OriginalContent = m_TextFile->GetContent();
}

void TextManager::OpenFile(GLFWwindow* window)
{
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

	if (GetOpenFileNameA(&ofn) == true)
	{
		m_TextFile = new TextFile(ofn.lpstrFile);
		m_Content = m_TextFile->GetContent();
		m_OriginalContent = m_TextFile->GetContent();
	}
}

void TextManager::SaveFile(GLFWwindow* window)
{
	if (m_TextFile != nullptr)
	{
		m_TextFile->CommitContent(&m_Content);
		m_OriginalContent = m_Content;
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
			m_OriginalContent = m_Content;
		}
	}
}

TextManager::~TextManager()
{
	delete m_TextFile;
}
