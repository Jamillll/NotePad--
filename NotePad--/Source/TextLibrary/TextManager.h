#pragma once
#include "TextFile.h"

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

		void OpenFile(std::string inputFilePath);

		bool SaveFile();
		void SaveAsFile(std::string inputFilePath);

		~TextManager();
	};
};