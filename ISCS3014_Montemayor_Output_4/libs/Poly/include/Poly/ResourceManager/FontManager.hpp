#pragma once

#include "ResourceManager.hpp"

#include <SFML/Graphics.hpp>

namespace poly {

class FontManager : public ResourceManager<sf::Font> {
protected:
    ResourcePtr load(const std::string resourcePath) {
        ResourcePtr resource = std::make_unique<sf::Font>();
        if (not resource->loadFromFile(resourcePath)) {
            return nullptr;
        } else {
            return resource;
        }
    }
};

}