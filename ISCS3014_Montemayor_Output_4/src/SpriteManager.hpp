#ifndef SRC_SPRITEMANAGER_HPP_
#define SRC_SPRITEMANAGER_HPP_

#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>

#include <Poly/Logging.hpp>

// Give this thing a sprite type
// it registers it and gives back a handle
// use that handle to set the texture and texture rect
class SpriteManager {
public:
    SpriteManager();
    int registerSpriteType(const std::string& spriteName);
    int getSpriteID(const std::string& spriteName);
    void setSpriteRect(int id, sf::IntRect textureRect);
    const sf::IntRect& getSpriteRect(int id);
    void readSpriteData(const std::string& spriteData);
    void setSpriteSheet(sf::Texture* texture);
    sf::Texture* getSpriteSheet();
private:
    int nextSpriteID;
    std::vector<sf::IntRect> spriteRects;
    std::unordered_map<std::string, int> spriteIDs;
    sf::Texture* spriteSheet;
};


#endif // SRC_SPRITEMANAGER_HPP_
