#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <memory>

#include "SpriteManager.hpp"
#include "Tile.hpp"

// Was initially planning to implement different tiles as subclasses of a base
// class. Midway through I decided not to but I had already written all this
// stuff. It still works and I didn't feel like refactoring.

using TilePointer = std::unique_ptr<Tile>;
using TileGrid = std::vector<std::vector<TilePointer>>;

class TileManager {
public:
    TileManager(SpriteManager& SpriteManager);

    void readTileData(const std::string& tileData);

    int getTileID(const std::string& tileName);

    template <typename T>
    int registerTileType(const std::vector<int>& sprites, bool passable,
        EnterResponse onEnter);
    
    std::unique_ptr<Tile> createTile(int tileID);
    
private:
    using TileConstructor = std::function<std::unique_ptr<Tile>()>;
    using TileFactory = std::unordered_map<int, TileConstructor>;

    SpriteManager& spriteManager;
    int nextTileID;
    TileFactory tileFactory;
    std::unordered_map<std::string, int> tileIDs;
};

#include "TileManager.inl"
