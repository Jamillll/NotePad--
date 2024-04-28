#include "TextFile.h"

namespace TextLibrary
{
	TextFile::TextFile(std::string inputPath)
	{
		m_Path = inputPath;
	}

	std::string TextFile::GetPath()
	{
		return m_Path;
	}

	std::string TextFile::GetContent()
	{
		std::fstream file(m_Path);

		std::string content;
		std::string currentLine;

		while (std::getline(file, currentLine))
		{
			content += currentLine + "\n";
		}

		file.close();
		return content;
	}

	void TextFile::CommitContent(std::string* content)
	{
		const char* charPath = m_Path.c_str();
		remove(charPath);

		std::ofstream file(charPath);
		file << *content;
		file.close();
	}
};