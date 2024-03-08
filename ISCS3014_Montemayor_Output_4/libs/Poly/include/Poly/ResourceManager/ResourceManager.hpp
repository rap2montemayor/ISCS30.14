#pragma once

#include <exception>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>

namespace poly {

// Handles loading and unloading of files.
// Users must define an explicit specialization of the load() function for
// every resource type that will be used. Built-in specializations are
// provided for sf::Texture, sf::Font, sf::SoundBuffer and sf::Music.
template <typename Resource>
class ResourceManager {
    std::unordered_map<std::string, std::unique_ptr<Resource>> resourceMap;
    std::unordered_map<std::string, std::string> resourcePaths;
    std::unordered_map<std::string, int> useCount;

public:
    ResourceManager() = default;

    // Gets the raw pointer of the resource with the specified name. The
    // resource name must have been present in the config AND must have been
    // requested. Otherwise returns a nullptr.
    Resource* getResource(const std::string resourceName);

    // Informs the manager that a resource with the specified name will be
    // used. Returns false if the name was not present in the config file or if
    // the resource could not be loaded.
    bool request(const std::string resourceName);

    // Informs the manager that a resource is no longer being used. Each 
    // request must eventually be followed by a corresponding release.
    // Does nothing if called with an invalid resource name.
    void release(const std::string resourceName);

    // Config should be a list of names and path pairs separated by a single
    // space. There must be no other space in the line. Does not check for
    // proper formatting.
    bool loadConfig(const std::string configPath);

protected:
    using ResourcePtr = std::unique_ptr<Resource>;
    // An explicit specialization must be implemented for every resource type
    // that will be used.
    //
    // This takes a string containing the relative path to a resource and
    // returns a unique pointer to where it was loaded to. If the resource does
    // not exist, a nullptr should be returned.
    virtual ResourcePtr load(const std::string resourcePath) = 0;

private:
    // Return true if resourceName was in the config. Returns false otherwise.
    bool isValid(const std::string resourceName);

    // Return true if resourceName is in resourceMap. Returns False otherwise.
    // isLoaded implies isValid.
    bool isLoaded(const std::string resourceName);
};

}

#include "ResourceManager.inl"
