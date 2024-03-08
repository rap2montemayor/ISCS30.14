#include "Level.hpp"

#include <fstream>
#include "Logger.hpp"
#include "Constants.hpp"

Level::Level(SpriteManager& spriteManager, TileManager& tileManager) :
       player(startPosition.first, startPosition.second), spriteManager(spriteManager),
       tileManager(tileManager), renderer(spriteManager, player) { }

void Level::init() {
    renderer.animateTiles(floorTiles);
    renderer.animateTiles(objectTiles);
}

void Level::render(poly::Window& window) {
    sf::RenderWindow& renderWindow = window.getRenderWindow();
    sf::View view;
    
    auto& [posx, posy] = player.getSpritePosition();
    auto [sizex, sizey] = renderWindow.getSize(); 
    view.setSize({sizex, sizey});
    view.setCenter(posx+tileSize.first/2.0, posy+tileSize.second/2.0);
    renderWindow.setView(view);

    for (size_t i = 0; i < floorTiles.size(); ++i) {
        for (size_t j = 0; j < floorTiles[i].size(); ++j) {
            renderer.renderTile(*floorTiles[i][j], window, i, j);
        }
    }
    renderer.renderPlayer(window);
    for (size_t i = 0; i < objectTiles.size(); ++i) {
        for (size_t j = 0; j < objectTiles[i].size(); ++j) {
            renderer.renderTile(*objectTiles[i][j], window, i, j);
        }
    }
}

void Level::update(double deltaTime) {
    controller.updateSpeedupState();

    if (controller.isSpeedUp()) {
        deltaTime *= 5;
    }
    
    renderer.update(deltaTime);
    
    if (controller.isEnabled()) {
        controller.updateInputState();
        movePlayer(controller.getDirection(), true); 
    }
}

void Level::readLevelData(const std::string& levelData) {
    Logger::logInfo("Starting Level::readLevelData");

    std::ifstream ifs(levelData);
    if (ifs.is_open()) {
        int rows, cols;
        ifs >> rows >> cols;

        floorTiles.resize(cols);
        for (auto& row : floorTiles) {
            row.resize(rows);
        }

        std::string tile;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                ifs >> tile;
                int id = tileManager.getTileID(tile);
                floorTiles[i][j] = tileManager.createTile(id);
                // int firstSprite = floorTiles[i][j]->getCurrentSpriteID();
                // Logger::logInfo("Created tile with first sprite ID "
                    // + std::to_string(firstSprite));
            }
        }
    } else {
        Logger::logError("Level data not found");
    }

    Logger::logInfo("Ending Level::readLevelData");
}

void Level::readObjectData(const std::string& objectData) {
    Logger::logInfo("Starting Level::readObjectData");

    std::ifstream ifs(objectData);
    if (ifs.is_open()) {
        int rows, cols;
        ifs >> rows >> cols;

        objectTiles.resize(cols);
        for (auto& row : objectTiles) {
            row.resize(rows);
        }

        std::string tile;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                ifs >> tile;
                int id = tileManager.getTileID(tile);
                objectTiles[i][j] = tileManager.createTile(id);
                // int firstSprite = objectTiles[i][j]->getCurrentSpriteID();
                // Logger::logInfo("Created object with first sprite ID "
                    // + std::to_string(firstSprite));
            }
        }
    } else {
        Logger::logError("Object data not found");
    }

    Logger::logInfo("Ending Level::readObjectData");
}

void Level::readPlayerSpriteData(const std::string& playerSpriteData) {
    Logger::logInfo("Starting Level::readPlayerSpriteData");

    std::ifstream ifs(playerSpriteData);
    if (ifs.is_open()) {
        std::vector<int> sprites(12);
        std::string spriteName;
        for (int i = 0; i < 12; ++i) {
            if (not ifs.good()) {
                Logger::logWarning("Missing player sprites. Only "
                    + std::to_string(i) + " were found");
            } else {
                ifs >> spriteName;
                sprites[i] = spriteManager.getSpriteID(spriteName);
            }
        }
        player.setSprites(sprites);
    } else {
        Logger::logError("Level data not found");
    }

    Logger::logInfo("Ending Level::readPlayerSpriteData");
}

bool Level::checkCollision(const Direction& direction) {
    auto [row, col] = player.getEndPosition(direction);
    auto inbounds = [](size_t l, size_t r, size_t x) {
        return l <= x and x < r;
    };
    
    // check out of bounds
    if (not inbounds(0, floorTiles.size(), row)) {
        return false;
    } else if (not inbounds(0, floorTiles[0].size(), col)) {
        return false;
    } else if (not floorTiles[row][col]->getPassable()) {
        return false;
    } else if (not objectTiles[row][col]->getPassable()) {
        return false;
    } else {
        return true;
    }
}

void Level::movePlayer(Direction direction, bool animate) {
    if (direction == Direction::None) {
        return;
    }

    if (checkCollision(direction)) {
        player.setMoveDirection(direction);
        renderer.moveSprite(direction);
        controller.disable();
        renderer.timedCallback(moveInterval, [this] { onMoveEnd(); });
        player.move(direction);
        if (animate) {
            renderer.moveAnimate(direction);
        }
    } else if (animate) {
        renderer.changePlayerFace(direction);
    }
}

void Level::onMoveEnd() {
    controller.enable();
    // check collision response
    auto& [row, col] = player.getGridPosition();
    bool responded = handleTileEnter(objectTiles[row][col]->getOnEnter());
    if (not responded) {
        handleTileEnter(floorTiles[row][col]->getOnEnter());
    }
}

bool Level::handleTileEnter(EnterResponse response) {
    bool responded = true;
    switch (response) {
    case EnterResponse::Continue:
        movePlayer(player.getMoveDirection(), false);
        break;
    case EnterResponse::MoveUp:
        movePlayer(Direction::Up, false);
        break;
    case EnterResponse::MoveDown:
        movePlayer(Direction::Down, false);
        break;
    case EnterResponse::MoveLeft:
        movePlayer(Direction::Left, false);
        break;
    case EnterResponse::MoveRight:
        movePlayer(Direction::Right, false);
        break;
    case EnterResponse::NoResponse:
        responded = false;
    default:
        break;
    }
    return responded;
}