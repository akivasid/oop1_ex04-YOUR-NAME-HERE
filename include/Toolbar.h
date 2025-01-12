#pragma once
#include "Tile.h"
#include "vector"
#include "Pictures.h"


class Toolbar {

public:
	//constructor
	Toolbar(const Pictures& pictures, const float toolbarSize);

	//public functions
	bool isToolbar(const sf::Vector2f location, const Pictures& pictures) const;
	std::string getToolbarState(const sf::Vector2f location, const Pictures& pictures) const;
	void draw(sf::RenderWindow& window, const Pictures& pictur) const;

private:
	std::vector <Tile> m_toolbar;
};

