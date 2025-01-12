#include "Toolbar.h"

Toolbar::Toolbar(const Pictures& pictures,  const float toolbarSize)
{
    for (int i = 0; i < GeneralSizes::TILES_TOOLBAR; i++) 
    { 
        m_toolbar.emplace_back(pictures.getImageName(i),
                      sf::Vector2f(toolbarSize, toolbarSize), sf::Vector2f(i * toolbarSize, 0.f));
    }
}


void Toolbar::draw(sf::RenderWindow& window, const Pictures& picture) const
{
	for (int i = 0; i < GeneralSizes::TILES_TOOLBAR; i++)
		m_toolbar[i].draw(window, picture);
}


bool Toolbar::isToolbar(const sf::Vector2f location, const Pictures& pictures) const
{
    for (int i = 0; i < GeneralSizes::TILES_TOOLBAR; i++)
        if (m_toolbar[i].isTile(location, pictures))
            return true;
    return false;
}


std::string Toolbar::getToolbarState(const sf::Vector2f location, const Pictures& pictures) const
{
     for (int i = 0; i < m_toolbar.size(); i++)
        if (m_toolbar[i].isTile(location, pictures))
            return m_toolbar[i].getViewName();
    
     return ModeId::BLANK;
}
