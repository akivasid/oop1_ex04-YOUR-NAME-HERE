#pragma once
#include <SFML/Graphics.hpp>
#include "Pictures.h"



class Tile {

public:
	//constructor
	Tile(const std::string& tileViewName, const sf::Vector2f& size, const sf::Vector2f& loc);

	//public functions 
	const std::string getViewName() const;
	void deleteTile(sf::RenderWindow& window, const Pictures& pictures);
	const sf::Sprite create(const Pictures& pictures) const; 
	void draw(sf::RenderWindow& window, const Pictures& pictures) const;
	bool isTile(const sf::Vector2f location, const Pictures& pictures) const; 
	void setPlayer(sf::RenderWindow& window, const Pictures& pictures);
	void setRock(sf::RenderWindow& window, const Pictures& pictures);
	void setWall(sf::RenderWindow& window, const Pictures& pictures);
	void setGuard(sf::RenderWindow& window, const Pictures& pictures);
	void setDoor(sf::RenderWindow& window, const Pictures& pictures);

	
private:
	std::string m_viewName;
	sf::Vector2f m_size; 
	sf::Vector2f m_loc; 
};