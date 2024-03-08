#include "Renderer.hpp"

Renderer::Renderer(poly::ECS& ecs, poly::Window& window)
    : ecs(ecs), window(window) {}

void Renderer::render() {
    ecs.runSystem<Position, Size, Sprite>(
        [&](poly::EntityList& entities) {
            renderSystem(entities);
        }
    );
}

void Renderer::renderSystem(poly::EntityList& entities) {
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::White);
    for (const poly::EntityID& id: entities) {
        const auto& size = ecs.getData<Size>(id);
        const auto& pos = ecs.getData<Position>(id);
        const auto& [texture, textureRect] = ecs.getData<Sprite>(id);
        rect.setSize({size.x, size.y});
        rect.setPosition({pos.x-size.x/2, pos.y-size.y/2});
        rect.setTexture(texture);
        rect.setTextureRect(textureRect);
        window.render(rect);
    }
}
