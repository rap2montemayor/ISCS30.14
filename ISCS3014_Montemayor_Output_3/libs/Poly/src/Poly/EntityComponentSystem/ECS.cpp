#include "Poly/EntityComponentSystem/ECS.hpp"

namespace poly {

EntityID ECS::nextEntityID = 0;

const EntityID ECS::createEntity() {
    return nextEntityID++;
}

void ECS::deleteEntity(const EntityID& id) {
    for (auto& [compID, pool]: poolMap) {
        pool->deleteEntityData(id);
    }
}

const EntityList ECS::queryComponents(const ComponentList& components) {
    auto sizeComp = [&](const ComponentID& l, const ComponentID& r) {
        return poolMap[l]->getSize() < poolMap[r]->getSize();
    };

    auto notInComponent = [&](const EntityID& id, const ComponentID& comp) {
        return not poolMap[comp]->hasEntity(id);
    };

    auto notInAllComponents = [&](const EntityID& id){
        return std::any_of(components.begin(), components.end(),
            [&](const ComponentID& comp) { return notInComponent(id, comp); }
        );
    };

    const ComponentID smallest = *std::min_element(
        components.begin(), components.end(), sizeComp
    );
    
    EntityList entities = poolMap[smallest]->getEntities();
    std::remove_if(entities.begin(), entities.end(), notInAllComponents);

    return entities;
}

}
