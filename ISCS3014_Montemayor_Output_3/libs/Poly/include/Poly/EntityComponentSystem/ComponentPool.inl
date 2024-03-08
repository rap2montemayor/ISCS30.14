#include "ComponentPool.hpp"

namespace poly {

template <typename ComponentType>
ComponentPool<ComponentType>::ComponentPool() {
    // Reserve ahead of time to avoid having to reallocate many times.
    sparse.reserve(512);
    dense.reserve(512);
}

template <typename ComponentType>
void* ComponentPool<ComponentType>::getEntityData(const EntityID id) {
    // If entity does not have data for this component, return nullptr. ECS
    // must check for this. May want to throw an exception instead.
    if (sparse.count(id) == 0) {
        return nullptr;
    } else {
        return reinterpret_cast<void*>(&(dense[sparse[id]].second));
    }
}

template <typename ComponentType>
void ComponentPool<ComponentType>::setEntityData(
        const EntityID id, const void* data) {
    // If entity does not have data for this component, create it.
    if (sparse.count(id) == 0) {
        sparse[id] = dense.size();
        dense.push_back({id, ComponentType()});
        dense.back().first = id;
    }
    dense[sparse[id]].second = *reinterpret_cast<const ComponentType*>(data);
}

template <typename ComponentType>
void ComponentPool<ComponentType>::deleteEntityData(const EntityID id) {
    // Do nothing if entity is not present.
    if (sparse.count(id) == 0) {
        return;
    }

    // Swap sparse and dense contents.
    std::swap(sparse[dense[sparse[id]].first], sparse[dense.back().first]);
    std::swap(dense[sparse[id]], dense.back());

    // We can now safely delete.
    sparse.erase(dense.back().first);
    dense.pop_back();
}

template <typename ComponentType>
const int ComponentPool<ComponentType>::getSize() {
    return dense.size();
}

template <typename ComponentType>
const bool ComponentPool<ComponentType>::hasEntity(const EntityID id) {
    return sparse.count(id);
}

template <typename ComponentType>
const EntityList ComponentPool<ComponentType>::getEntities() {
    EntityList entities;
    entities.reserve(dense.size());
    for (auto& [entityID, data]: dense) {
        entities.push_back(entityID);
    }
    return entities;
}

}
