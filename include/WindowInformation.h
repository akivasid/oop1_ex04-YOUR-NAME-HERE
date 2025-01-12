#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "ModeId.h"
#include "NamePictures.h"
#include "GeneralSizes.h"
#include "NameFile.h"
#include "ToolbarKeys.h"


class WindowInformation
{

public:
	//constructor
	WindowInformation(const int row, const int col);
	
	//public functions
	int getRows() const;
	int getCols() const;
	float getToolbarSize() const;
	sf::Vector2f getBoardSize() const;
	sf::Vector2f getWindowSize() const;
	


private:
	//members
	float m_toolbarSize;
	sf::Vector2f m_boardSize;
	sf::Vector2f m_windowSize;
	int m_col;
	int m_row;
};
