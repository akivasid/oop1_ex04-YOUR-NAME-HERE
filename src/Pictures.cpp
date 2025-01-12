#include "Pictures.h"

Pictures::Pictures()
	:m_imagesBoard(GeneralSizes::TILES_TOOLBAR + 1), m_imagesName(GeneralSizes::TILES_TOOLBAR + 1)
{
    std::vector <char> toolbarOrder;
    std::ifstream name_file(NameFile::INPUT_FILE_TOOLBAR);

    char ch;
    while (name_file >> ch) 
        toolbarOrder.push_back(ch);
   
    if (loadFile(toolbarOrder) == -1)
        std::cerr << "Error: Failed to load image file\n";
}


const sf::Texture& Pictures::getImageByName(const std::string& name) const
{
    for (int i = 0; i < GeneralSizes::TILES_TOOLBAR + 1; i++)
        if (name == m_imagesName[i])
            return  m_imagesBoard[i];
}


const std::string Pictures::getImageName(int index) const
{
    return m_imagesName[index];
}


sf::Vector2u Pictures::getImageSizeByName(const std::string& name)
{
    for (int i = 0; i < GeneralSizes::TILES_TOOLBAR + 1; i++)
        if (name == m_imagesName[i])
            return  m_imagesBoard[i].getSize();
    return sf::Vector2u(0, 0);
}


int Pictures::loadFile(const std::vector <char>& toolbarOrder)
{
    int i;
    
    for (i = 0; i < 5; i++)
    {
        switch (toolbarOrder[i])
        {
        case ToolbarKeys::PLAYER:
            if (!m_imagesBoard[i].loadFromFile(NamePictures::PLAYER))
                return -1;
            m_imagesName[i] = ModeId::PLAYER;
            break;

        case ToolbarKeys::DOOR:
            if (!m_imagesBoard[i].loadFromFile(NamePictures::DOOR))
                return -1;
            m_imagesName[i] = ModeId::DOOR;
            break;

        case ToolbarKeys::GUARD:
            if (!m_imagesBoard[i].loadFromFile(NamePictures::GUARD))
                return -1;
            m_imagesName[i] = ModeId::GUARD;
            break;

        case ToolbarKeys::WALL:
            if (!m_imagesBoard[i].loadFromFile(NamePictures::WALL))
                return -1;
            m_imagesName[i] = ModeId::WALL;
            break;

        case ToolbarKeys::ROCK:
            if (!m_imagesBoard[i].loadFromFile(NamePictures::ROCK))
                return -1;
            m_imagesName[i] = ModeId::ROCK;
            break;
        }
    }

    if (!m_imagesBoard[i].loadFromFile(NamePictures::DELETE))
        return -1;
    m_imagesName[i++] = ModeId::DELETE;

    if (!m_imagesBoard[i].loadFromFile(NamePictures::CLEAR))
        return -1;
    m_imagesName[i++] = ModeId::CLEAR;

    if (!m_imagesBoard[i].loadFromFile(NamePictures::SAVE))
        return -1;
    m_imagesName[i++] = ModeId::SAVE;

    if (!m_imagesBoard[i].loadFromFile(NamePictures::BACKGRAUND_BOARD))
        return -1;
    m_imagesName[i] = ModeId::BLANK;

    return 0;
}