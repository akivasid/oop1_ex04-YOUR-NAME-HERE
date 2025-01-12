#include "Board.h"


Board::Board(const WindowInformation& info, const Pictures& pictures, const bool fileExists)
    :m_rows(info.getRows()), m_cols(info.getCols())
{
     if (!fileExists)
        firstReboot(info);
    else
      readFromFile(info);
}


void Board::firstReboot(const WindowInformation& info)
{
    m_board.resize(m_rows);
    sf::Vector2f size(GeneralSizes::SIZE_TILE, GeneralSizes::SIZE_TILE);

    for (int i = 0; i < m_rows; i++)
        for (int j = 0; j < m_cols; j++)
        {
            sf::Vector2f loc(j * GeneralSizes::SIZE_TILE, i * GeneralSizes::SIZE_TILE + info.getToolbarSize());
            m_board[i].emplace_back(ModeId::BLANK, size, loc);
        }
}


void Board::readFromFile(const WindowInformation& info)
{
    m_board.resize(m_rows);
    sf::Vector2f size(GeneralSizes::SIZE_TILE, GeneralSizes::SIZE_TILE);

    std::string filename = NameFile::OUTPUT_FILE_NAME;
    std::ifstream file(filename);
    std::string line;

    if (file.good())
    {
        for (int i = 0; i < m_rows; i++)
        {
            std::getline(file, line);

            for (int j = 0; j < m_cols; j++)
            {
                sf::Vector2f loc(j * GeneralSizes::SIZE_TILE, i * GeneralSizes::SIZE_TILE + info.getToolbarSize());

                if (ToolbarKeys::DOOR == line[j])
                    m_board[i].emplace_back(ModeId::DOOR, size, loc);

                else if (ToolbarKeys::GUARD == line[j])
                    m_board[i].emplace_back(ModeId::GUARD, size, loc);

                else if (ToolbarKeys::PLAYER == line[j])
                    m_board[i].emplace_back(ModeId::PLAYER, size, loc);

                else if (ToolbarKeys::ROCK == line[j])
                    m_board[i].emplace_back(ModeId::ROCK, size, loc);

                else if (ToolbarKeys::WALL == line[j])
                    m_board[i].emplace_back(ModeId::WALL, size, loc);
                
                else if (ToolbarKeys::SPACE == line[j])
                    m_board[i].emplace_back(ModeId::BLANK, size, loc);
            }
        }
    }
}
   

void Board::copyToFile()
{
    int j;
    std::string filename = NameFile::OUTPUT_FILE_NAME;
    std::ofstream file(filename);
    if (file.good())
    {
        for (int i = 0; i < m_rows; i++)
        {
            for (j = 0; j < m_cols; j++)
            {
                if (m_board[i][j].getViewName() == ModeId::DOOR)
                    file << ToolbarKeys::DOOR;

                else if (m_board[i][j].getViewName() == ModeId::GUARD)
                    file << ToolbarKeys::GUARD;

                else if (m_board[i][j].getViewName() == ModeId::PLAYER)
                    file << ToolbarKeys::PLAYER;

                else if (m_board[i][j].getViewName() == ModeId::ROCK)
                    file << ToolbarKeys::ROCK;

                else if (m_board[i][j].getViewName() == ModeId::WALL)
                    file << ToolbarKeys::WALL;

                else if (m_board[i][j].getViewName() == ModeId::BLANK)
                    file << ToolbarKeys::SPACE;
            }
            
             file << '\n';
        }
        file.close();
    }
}


bool Board::isBoard(const sf::Vector2f& location, const WindowInformation& info)
{
    if (location.x <= info.getWindowSize().x && location.y <= info.getWindowSize().y && location.x >= 0 && location.y >= 0)
        return true;
    return false;
}


bool Board::locationIsAvailable(const sf::Vector2i& location)
{
    if (m_board[location.y][location.x].getViewName() == ModeId::BLANK)
        return true;
    return false;
}


sf::Vector2i Board::getColRow(const sf::Vector2f& pixelLocation, const WindowInformation& info)
{
    return sf::Vector2i(int(pixelLocation.x / GeneralSizes::SIZE_TILE),
                        int((pixelLocation.y - info.getToolbarSize()) / GeneralSizes::SIZE_TILE));
}


std::string Board::getTileView(const sf::Vector2i& indexLocation) const
{
    return m_board[indexLocation.y][indexLocation.x].getViewName();
}


void Board::setDoor(const sf::Vector2i& indexLocation, sf::RenderWindow& window, const Pictures& pictures)
{
    if (doorExists())
        deleteBoardTile(getDoorIndex(), window, pictures);
    m_board[indexLocation.y][indexLocation.x].setDoor(window, pictures);
}


void Board::deleteBoardTile(const sf::Vector2i& location, sf::RenderWindow& window, const Pictures& pictures)
{
    m_board[location.y][location.x].deleteTile(window, pictures);
}


sf::Vector2i Board::getDoorIndex() const
{
    for (int i = 0; i < m_rows; i++)
        for (int j = 0; j < m_cols; j++)
            if (m_board[i][j].getViewName() == ModeId::DOOR)
                return sf::Vector2i(j, i);
    return sf::Vector2i(-1, -1);
}


bool Board::doorExists() const
{
    for (int i = 0; i < m_rows; i++)
        for (int j = 0; j < m_cols; j++)
            if (m_board[i][j].getViewName() == ModeId::DOOR)
                return true;
    return false;
}


sf::Vector2i Board::getPlayerIndex() const
{
    for (int i = 0; i < m_rows; i++)
        for (int j = 0; j < m_cols; j++)
            if (m_board[i][j].getViewName() == ModeId::PLAYER)
                return sf::Vector2i(j, i);
    return sf::Vector2i(-1, -1);
}


bool Board::playerExists() const
{
    for (int i = 0; i < m_rows; i++)
        for (int j = 0; j < m_cols; j++)
            if (m_board[i][j].getViewName() == ModeId::PLAYER)
                return true;
    return false;
}


void Board::setPlayer(const sf::Vector2i& indexLocation, sf::RenderWindow& window, const Pictures& pictures)
{
    if (playerExists())
        deleteBoardTile(getPlayerIndex(), window, pictures);
    m_board[indexLocation.y][indexLocation.x].setPlayer(window, pictures);
}


void Board::setGuard(const sf::Vector2i& indexLocation, sf::RenderWindow& window, const Pictures& pictures)
{
    m_board[indexLocation.y][indexLocation.x].setGuard(window, pictures);
}


void Board::setRock(const sf::Vector2i& indexLocation, sf::RenderWindow& window, const Pictures& pictures)
{
    m_board[indexLocation.y][indexLocation.x].setRock(window, pictures);
}


void Board::setWall(const sf::Vector2i& indexLocation, sf::RenderWindow& window, const Pictures& pictures)
{
    m_board[indexLocation.y][indexLocation.x].setWall(window, pictures);
}


void Board::draw(sf::RenderWindow& window, const Pictures& pictures) const 
{
    for (int i = 0; i < m_board.size(); i++) {
        for (int j = 0; j < m_board[i].size(); j++) {
            m_board[i][j].draw(window, pictures);
        }
    }
}