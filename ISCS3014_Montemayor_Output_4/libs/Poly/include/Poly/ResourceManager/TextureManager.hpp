#pragma once

#include "ResourceManager.hpp"

#include <SFML/Graphics.hpp>

namespace poly {

class TextureManager : public ResourceManager<sf::Texture> {
protected:
    ResourcePtr load(const std::string resourcePath) {
        ResourcePtr resource = std::make_unique<sf::Texture>();
        if (not resource->loadFromFile(resourcePath)) {
            return nullptr;
        } else {
            return resource;
        }
    }
};

}