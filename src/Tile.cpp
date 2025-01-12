#include "Tile.h"


Tile::Tile(const std::string& tileViewName,  const sf::Vector2f& size, const sf::Vector2f& loc)
	:m_size(size), m_loc(loc), m_viewName(tileViewName)
{}


void Tile::deleteTile(sf::RenderWindow& window, const Pictures& pictures)
{
	m_viewName = ModeId::BLANK;
	draw(window, pictures);
}


void Tile::setDoor(sf::RenderWindow& window, const Pictures& pictures)
{
	m_viewName = ModeId::DOOR;
	draw(window, pictures);
}


void Tile::setPlayer(sf::RenderWindow& window, const Pictures& pictures)
{
	m_viewName = ModeId::PLAYER;
	draw(window, pictures);
}


void Tile::setRock(sf::RenderWindow& window, const Pictures& pictures)
{
	m_viewName = ModeId::ROCK;
	draw(window, pictures);
}


void Tile::setWall(sf::RenderWindow& window, const Pictures& pictures)
{
	m_viewName = ModeId::WALL;
	draw(window, pictures);
}


void Tile::setGuard(sf::RenderWindow& window, const Pictures& pictures)
{
	m_viewName = ModeId::GUARD;
	draw(window, pictures);
}

 
const sf::Sprite Tile::create(const Pictures& pictures) const
{
	sf::Sprite sprite(pictures.getImageByName(m_viewName));
	sprite.setPosition(m_loc);
	sprite.setScale(m_size.x / pictures.getImageByName(m_viewName).getSize().x,
					m_size.y / pictures.getImageByName(m_viewName).getSize().y);

	return sprite;
}


void Tile::draw(sf::RenderWindow& window, const Pictures& pictures) const
{
	window.draw(create(pictures));
}

bool Tile::isTile(const sf::Vector2f location, const Pictures& pictures) const
{
	sf::Sprite sprite = create(pictures);
	return sprite.getGlobalBounds().contains(location);
}


const std::string Tile::getViewName() const
{
	return m_viewName;
}