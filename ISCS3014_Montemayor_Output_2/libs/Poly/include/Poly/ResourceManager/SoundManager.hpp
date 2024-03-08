#pragma once

#include "ResourceManager.hpp"

#include <SFML/Audio.hpp>

namespace poly {

class SoundManager : public ResourceManager<sf::SoundBuffer> {
protected:
    ResourcePtr load(const std::string resourcePath) {
        ResourcePtr resource = std::make_unique<sf::SoundBuffer>();
        if (not resource->loadFromFile(resourcePath)) {
            return nullptr;
        } else {
            return resource;
        }
    }
};

}