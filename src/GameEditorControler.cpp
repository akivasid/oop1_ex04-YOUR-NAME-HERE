#include "GameEditorControler.h"

GameEditorControler::GameEditorControler(const int row, const int col, const bool& fileExists)
	:m_info(row, col), m_picturesBoard(), m_editingMode(ModeId::BLANK),
	m_toolbar(m_picturesBoard, m_info.getToolbarSize()),
	m_board(m_info, m_picturesBoard, fileExists)
{}


bool GameEditorControler::runGameEditor()
{
	sf::RenderWindow window(sf::VideoMode(unsigned(m_info.getWindowSize().x), unsigned(m_info.getWindowSize().y)),
							NameFile::NAME_WINDOW);
	bool stopEditing = true;

	handleEvents(window, stopEditing);

	return stopEditing;
}


void GameEditorControler::darwAll(sf::RenderWindow& window, const bool drawWeakSprite, const sf::Sprite& weakSprite) const
{
	window.clear();
	m_toolbar.draw(window, m_picturesBoard);
	m_board.draw(window, m_picturesBoard);
	if (drawWeakSprite)
		window.draw(weakSprite);
	window.display();
}

void GameEditorControler::handleEvents(sf::RenderWindow& window, bool& stopEditing)
{
	sf::Sprite weakSprite;
	bool drawWeakSprite = false;
	

	while (window.isOpen())
	{
		
		darwAll(window, drawWeakSprite, weakSprite);
		drawWeakSprite = false;
		
		sf::Event event;
		if (window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				handleClick(window, sf::Vector2f(float(event.mouseButton.x), float(event.mouseButton.y)), stopEditing);
				if (!stopEditing)
					return;
				break;
			case sf::Event::MouseMoved:
				if (m_editingMode == ModeId::CLEAR || m_editingMode == ModeId::SAVE
					|| m_editingMode == ModeId::BLANK || m_editingMode == ModeId::DELETE)
					break;

				sf::Vector2f locMove = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
				sf::Vector2f locMoveIndex(m_board.getColRow(locMove, m_info));
				
				if ( m_toolbar.isToolbar(locMove, m_picturesBoard) 
						|| !m_board.locationIsAvailable(sf::Vector2i(locMoveIndex)))
					break;
				
				
				drawWeakSprite = true;
				locMoveIndex = sf::Vector2f(locMoveIndex.x * GeneralSizes::SIZE_TILE,
											locMoveIndex.y * GeneralSizes::SIZE_TILE + m_info.getToolbarSize());
				weakSprite = setWeakSprite(locMoveIndex);
				break;
			}
		}
	}
}



sf::Sprite GameEditorControler::setWeakSprite(const sf::Vector2f location) const
{
	sf::Sprite sprite;
	sprite.setTexture(m_picturesBoard.getImageByName(m_editingMode));

	sprite.setPosition(location);
	sprite.setScale(GeneralSizes::SIZE_TILE / m_picturesBoard.getImageByName(m_editingMode).getSize().x,
		GeneralSizes::SIZE_TILE / m_picturesBoard.getImageByName(m_editingMode).getSize().y);
	sprite.setColor(sf::Color(225, 225, 225, 190));
	return sprite;
}



void GameEditorControler::handleClick(sf::RenderWindow& window, const sf::Vector2f& location, bool& stopEditing)
{
	if (m_toolbar.isToolbar(location, m_picturesBoard))
	{
		m_editingMode = m_toolbar.getToolbarState(location, m_picturesBoard);
		
		if (m_editingMode == ModeId::CLEAR)
		{
			stopEditing = false;
			window.close();
		}
		
		else if (m_editingMode == ModeId::SAVE)
			m_board.copyToFile();
		
		return;
	}

	else if (m_board.isBoard(location, m_info))
		handleClickBoard(window, m_board.getColRow(location, m_info));//send index not pixel

}


void GameEditorControler::handleClickBoard(sf::RenderWindow& window, const sf::Vector2i& indexLocation)
{
	
		
	if (m_board.locationIsAvailable(indexLocation))
	{
		if (m_editingMode == ModeId::DOOR)
			m_board.setDoor(indexLocation, window, m_picturesBoard);

		else if (m_editingMode == ModeId::GUARD)
			m_board.setGuard(indexLocation, window, m_picturesBoard);

		else if (m_editingMode == ModeId::PLAYER)
			m_board.setPlayer(indexLocation, window, m_picturesBoard);

		else if (m_editingMode == ModeId::ROCK)
			m_board.setRock(indexLocation, window, m_picturesBoard);

		else if (m_editingMode == ModeId::WALL)
			m_board.setWall(indexLocation, window, m_picturesBoard);
	}

	else if (m_editingMode == ModeId::DELETE)
		m_board.deleteBoardTile(indexLocation, window, m_picturesBoard);

}