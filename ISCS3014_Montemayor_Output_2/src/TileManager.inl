#include "TileManager.hpp"

template <typename T>
int TileManager::registerTileType(const std::vector<int>& sprites,
        bool passable, EnterResponse onEnter) {
    std::string msg = "Registering tile with sprite IDs: ";
    for (const int& i: sprites) {
        msg += std::to_string(i) + " ";
    }
    Logger::logInfo(msg);

    tileFactory.emplace(nextTileID, [=] {
        return std::make_unique<T>(sprites, passable, onEnter);
    });
    return nextTileID++;
}
