#include "GeneralManager.h"

GeneralManager::GeneralManager()
	:m_stopEditing(false), m_fileExists(false), m_firstTime(true)
{}


void GeneralManager::runGeneralManager()
{
	while (!m_stopEditing)
	{
		int row = 0, col = 0;
		m_fileExists = false;
		updateWindowSize(row, col);

		GameEditorControler gameEditor(row, col, m_fileExists);
		m_stopEditing = gameEditor.runGameEditor();
	}
}


void GeneralManager::updateWindowSize(int& row, int& col)
{
	std::string filename = NameFile::OUTPUT_FILE_NAME;
	std::ifstream file(filename);

	if (m_firstTime && file.good())
	{		
		std::string line;
		while (std::getline(file, line))
		{
			row++;
			col = line.size();
		}
		m_fileExists = true;
		m_firstTime = false;
	}

	else
	{
		std::cout << "Enter number of rows (tiles): ";
		std::cin >> row;
		std::cout << "Enter number of columns (tiles): ";
		std::cin >> col;
	}
}
