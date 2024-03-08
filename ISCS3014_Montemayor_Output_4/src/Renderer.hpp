#ifndef SRC_RENDERER_HPP_
#define SRC_RENDERER_HPP_

#include <Poly/Logging.hpp>
#include <Poly/EntityComponentSystem.hpp>
#include <Poly/Core.hpp>

#include "Components.hpp"

class Renderer {
public:
    Renderer(poly::ECS& ecs, poly::Window& window);
    void render();
    void renderSystem(poly::EntityList& entities);

private:
    poly::ECS& ecs;
    poly::Window& window;
};

#endif // SRC_RENDERER_HPP_
