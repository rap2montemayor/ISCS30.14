#include "ResourceManager.hpp"

namespace poly {

template <typename ResourceType>
ResourceType* ResourceManager<ResourceType>::getResource(
        const std::string resourceName) {
    if (isValid(resourceName) and isLoaded(resourceName)) {
        return resourceMap[resourceName].get();
    } else {
        return nullptr;
    }
}

template <typename ResourceType>
bool ResourceManager<ResourceType>::request(const std::string resourceName) {
    if (not isValid(resourceName)) return false;
    if (not isLoaded(resourceName)) {
        resourceMap[resourceName] = load(resourcePaths[resourceName]);
        if (resourceMap[resourceName] == nullptr) {
            resourceMap.erase(resourceName);
            return false;
        }
    }
    ++useCount[resourceName];
    return true;
}

template <typename ResourceType>
void ResourceManager<ResourceType>::release(const std::string resourceName) {
    if (not isValid(resourceName)) return;
    if (isLoaded(resourceName)) {
        // Unload if useCount is zero.
        --useCount[resourceName];
        if (useCount[resourceName] == 0) {
            resourceMap.erase(resourceName);
            useCount.erase(resourceName);
        }
    }
}

template <typename ResourceType>
bool ResourceManager<ResourceType>::loadConfig(const std::string configPath) {
    std::ifstream config;
    config.open(configPath);
    if (config.is_open()) {
        std::string line;
        while (std::getline(config, line)) {
            std::istringstream linestream(line);
            std::string name, path;
            linestream >> name >> path;
            resourcePaths[name] = path;
        }
        config.close();
        return true;
    } else {
        return false;
    }
}

template <typename ResourceType>
bool ResourceManager<ResourceType>::isValid(const std::string resourceName) {
    return resourcePaths.count(resourceName);
}

template <typename ResourceType>
bool ResourceManager<ResourceType>::isLoaded(const std::string resourceName) {
    return resourceMap.count(resourceName);
}

}
