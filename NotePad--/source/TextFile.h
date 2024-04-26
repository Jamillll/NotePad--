#pragma once
#include <fstream>
#include <string>

class TextFile
{
private:
	std::string m_Path;

public:
	TextFile(std::string inputPath);

	std::string GetContent();

	void CommitContent(std::string* content);
};