#pragma once
#include <fstream>
#include <string>

namespace TextLibrary
{
	class TextFile
	{
	private:
		std::string m_Path;

	public:
		TextFile(std::string inputPath);

		std::string GetPath();
		std::string GetContent();

		void CommitContent(std::string* content);
	};
};