#include "WindowInformation.h"


WindowInformation::WindowInformation(const int row, const int col)
	:m_col(col), m_row(row), m_boardSize(sf::Vector2f(0, 0)), m_toolbarSize(0), m_windowSize(sf::Vector2f(0, 0))
{
	// editing-area/board size
	m_boardSize.y = m_row * GeneralSizes::SIZE_TILE;
	m_boardSize.x = m_col * GeneralSizes::SIZE_TILE;

	// toolbar size 
	m_toolbarSize = m_boardSize.x / GeneralSizes::TILES_TOOLBAR;
	

	// window size
	m_windowSize.y =  m_toolbarSize + m_boardSize.y; 
	m_windowSize.x = m_boardSize.x;

}



float WindowInformation::getToolbarSize() const
{
	return m_toolbarSize;
}


int WindowInformation::getRows() const
{
	return m_row;
}

int WindowInformation::getCols() const
{
	return m_col;
}



sf::Vector2f WindowInformation::getBoardSize() const
{
	return m_boardSize;
}


sf::Vector2f WindowInformation::getWindowSize() const
{
	return m_windowSize;
}


