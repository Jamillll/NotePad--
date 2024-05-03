#include "TextManager.h"

#include <sstream>
#include <vector>

namespace TextLibrary
{
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
	}

	void TextManager::OpenFile(std::string inputFilePath)
	{
		m_TextFile = new TextFile(inputFilePath);
		m_Content = m_TextFile->GetContent();
		m_OriginalContent = m_TextFile->GetContent();
	}

	bool TextManager::SaveFile()
	{
		if (m_TextFile == nullptr) return false;

		m_TextFile->CommitContent(&m_Content);
		m_OriginalContent = m_Content;

		return true;
	}

	void TextManager::SaveAsFile(std::string inputFilePath)
	{
		m_TextFile = new TextFile(inputFilePath);
		m_TextFile->CommitContent(&m_Content);
		m_OriginalContent = m_Content;
	}

	TextManager::~TextManager()
	{
		delete m_TextFile;
	}

};