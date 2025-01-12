#pragma once
#include <fstream>
#include "GameEditorControler.h"
#include "NameFile.h"




class GeneralManager
{
public:
	//constructor
	GeneralManager();

	//public function
	void runGeneralManager();


private:
	//member
	bool m_stopEditing;
	bool m_fileExists;
	bool m_firstTime;

	//private functions
	void updateWindowSize(int& row, int& col);

};