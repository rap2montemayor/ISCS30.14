#pragma once

#include <SFML/Graphics.hpp>

#include <string>

#include "Poly/Core.hpp"
#include "Poly/ResourceManager.hpp"

#include "Level.hpp"
#include "Logger.hpp"
#include "SpriteManager.hpp"
#include "TileManager.hpp"

class Scene : public poly::Scene {
public:
    Scene(poly::Game& game);
    void init() override;
    void processInput(poly::InputContainer inputs) override;
    void render(poly::Window& window) override;
    void update(double deltaTime) override;
    void exit() override;

private:
    poly::TextureManager textureManager;
    SpriteManager spriteManager;
    TileManager tileManager;
    Level level;
};

