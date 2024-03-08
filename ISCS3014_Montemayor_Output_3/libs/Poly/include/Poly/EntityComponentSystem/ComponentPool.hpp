#pragma once

#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

#include "ComponentPoolBase.hpp"

namespace poly {

// Templated concrete component pool class. Everything here must only be
// accessed through EntityComponentSystem. These MUST NOT be accessed directly
// due to the use of void pointers.
template <typename ComponentType>
class ComponentPool : public ComponentPoolBase {
    // sparse contains indices for dense
    std::unordered_map<EntityID, int> sparse;

    // dense contains actual component data. This is done to make them as
    // compact as possible for cache-friendliness.
    std::vector<std::pair<EntityID, ComponentType>> dense;

public:
    ComponentPool();

    // Returns a void* to an entity's component.
    void* getEntityData(const EntityID id) override;

    // Sets the data associated with id to whatever is pointed to by data.
    void setEntityData(const EntityID id, const void* data) override;

    void deleteEntityData(const EntityID id) override;

    // Gets the number of entities being tracked by this component pool.
    const int getSize() override;

    // Checks if this component pool has an entry for this entity.
    const bool hasEntity(const EntityID id) override;

    const EntityList getEntities() override;
};

}

#include "ComponentPool.inl"
