#pragma once

#include "ResourceManager.hpp"

#include <SFML/Audio.hpp>

namespace poly {

class MusicManager : public ResourceManager<sf::Music> {
protected:
    ResourcePtr load(const std::string resourcePath) {
        ResourcePtr resource = std::make_unique<sf::Music>();
        if (not resource->openFromFile(resourcePath)) {
            return nullptr;
        } else {
            return resource;
        }
    }
};

}