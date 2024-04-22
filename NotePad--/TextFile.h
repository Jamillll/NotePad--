#pragma once
#include <fstream>
#include <stdio.h>
#include <string>

class TextFile
{
private:
	std::string m_Path;

public:
	TextFile(std::string inputPath)
	{
		m_Path = inputPath;
	}

	std::string getContent()
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

	void commitContent(std::string content)
	{
		const char* charPath = m_Path.c_str();
		remove(charPath);

		std::ofstream file(charPath);
		file << content;
		file.close();
	}
};