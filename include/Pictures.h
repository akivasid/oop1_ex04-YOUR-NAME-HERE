#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include "ModeId.h"
#include "NamePictures.h"
#include "GeneralSizes.h"
#include "NameFile.h"
#include "ToolbarKeys.h"



class Pictures {

public:
	//constructor
	Pictures();
	Pictures(const Pictures&) = delete; // Avoid using copy

	//public function
	const sf::Texture& getImageByName(const std::string& name) const;
	const std::string getImageName(int index) const;
	sf::Vector2u getImageSizeByName(const std::string& name);
	
private:
	//members
	std::vector <sf::Texture> m_imagesBoard;
	std::vector <std::string> m_imagesName;
	
	//private functions
	int loadFile(const std::vector <char>& toolbar);
};
