#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Pictures.h"
#include "Tile.h"
#include "Toolbar.h"
#include "Board.h"
#include "WindowInformation.h"

class GameEditorControler {

public:
    //constructor
    GameEditorControler(const int row, const int col, const bool& fileExists);
    
    //public functions
     bool runGameEditor();

private:
    //members
    WindowInformation m_info;
    std::string m_editingMode;
    Pictures m_picturesBoard; 
    Toolbar m_toolbar;
    Board m_board; 

    //private functions
    void darwAll(sf::RenderWindow& window, const bool drawWeakSprite,const sf::Sprite& weakSprite) const;
    void handleEvents(sf::RenderWindow& window, bool& stopEditing);
    void handleClick(sf::RenderWindow& window, const sf::Vector2f& location, bool& stopEditing);
    void handleClickBoard(sf::RenderWindow& window, const sf::Vector2i& indexLocation);
    sf::Sprite setWeakSprite(const sf::Vector2f location) const;
};
