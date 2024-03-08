#include "Renderer.hpp"

Renderer::Renderer(poly::ECS& ecs, poly::Window& window, Controller& controller)
    : ecs(ecs), window(window), controller(controller) {
    poly::logInfo("Renderer::Renderer");
}

void Renderer::render() {
    ecs.runSystem<Position, Size, Sprites>(
        [&](poly::EntityList entities) {
            // poly::logInfo("Rendering", entities.size(), "entities");
            renderSystem(entities);
        }
    );
}

void Renderer::updatePlayerSprites(double deltaTime) {
    auto& collision = ecs.getData<Collision>(player);
    auto& sprites = ecs.getData<Sprites>(player);

    if (not (collision.direction & Collision::Below)) {
        return;
    }

    // refer to this. yes i'm sorry
    // const std::pair<int, std::string> spriteRects[] = {
    //     {0, "IdleLeft"},
    //     {1, "IdleRight"},
    //     {2, "MoveLeft1"},
    //     {3, "MoveRight1"},
    //     {4, "MoveLeft2"},
    //     {5, "MoveRight2"},
    // };
    
    const int parity = sprites.currentSprite % 2;
    const bool movingLeft = controller.isPressed(InputState::Left);
    const bool movingRight = controller.isPressed(InputState::Right);
    
    if (parity == 1 and movingLeft) {
        sprites.currentSprite = 0;
    } else if (parity == 0 and movingRight) {
        sprites.currentSprite = 1;
    }

    sprites.timeToNext -= deltaTime;
    while (sprites.timeToNext < 0) {
        sprites.timeToNext += 0.05;
        // 1 = odd
        // 0 = even
        if (movingLeft) {
            sprites.currentSprite += 2;
        } else if (movingRight) {
            sprites.currentSprite += 2;
        } else {
            sprites.currentSprite = parity;
        }
        sprites.currentSprite %= sprites.endSprite;
    }
}


void Renderer::renderSystem(poly::EntityList entities) {
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::White);
    for (const poly::EntityID& i: entities) {
        const auto& size = ecs.getData<Size>(i);
        const auto& pos = ecs.getData<Position>(i);
        const auto& sprites = ecs.getData<Sprites>(i);
        rect.setTexture(sprites.spriteSheet);
        rect.setTextureRect(sprites.spriteRects[sprites.currentSprite]);
        rect.setSize({size.x, size.y});
        rect.setPosition({pos.x, pos.y});
        window.render(rect);
    }
}