#pragma once
#include "vector"
#include "Pictures.h"
#include "Toolbar.h"
#include "WindowInformation.h"


class Board {

public:
	//constructor
	Board(const WindowInformation& info, const Pictures& pictures, const bool fileExists);
	
	//public functions
	bool isBoard(const sf::Vector2f& location, const WindowInformation& info);
	bool locationIsAvailable(const sf::Vector2i& location);
	sf::Vector2i getColRow(const sf::Vector2f& pixelLocation, const WindowInformation& info);
	std::string getTileView(const sf::Vector2i& indexLocation) const;
	void setDoor(const sf::Vector2i& indexLocation, sf::RenderWindow& window, const Pictures& pictures);
	void setPlayer(const sf::Vector2i& indexLocation, sf::RenderWindow& window, const Pictures& pictures);
	void setGuard(const sf::Vector2i& indexLocation, sf::RenderWindow& window, const Pictures& pictures);
	void setRock(const sf::Vector2i& indexLocation, sf::RenderWindow& window, const Pictures& pictures);
	void setWall(const sf::Vector2i& indexLocation, sf::RenderWindow& window, const Pictures& pictures);
	bool doorExists() const;
	sf::Vector2i getDoorIndex() const;
	bool playerExists() const;
	sf::Vector2i getPlayerIndex() const;
	void deleteBoardTile(const sf::Vector2i& location, sf::RenderWindow& window, const Pictures& pictures);
	void copyToFile();
	void draw(sf::RenderWindow& window, const Pictures& pictures) const;
	

private:
	//members
	std::vector <std::vector<Tile>> m_board;
	int m_rows;
	int m_cols;

	//private functions
	void firstReboot(const WindowInformation& info);
	void readFromFile(const WindowInformation& info);
};