#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>
#include <typeinfo>
#include <typeindex>

#include "Entity.hpp"
#include "ComponentPool.hpp"

namespace poly {

class ECS {
    using ComponentID = std::type_index;
    using ComponentList = std::vector<std::type_index>;

    using SystemFunction = std::function<void(EntityList)>;
    using PoolPtr = std::unique_ptr<ComponentPoolBase>;
    using PoolMap = std::unordered_map<ComponentID, PoolPtr>;

    PoolMap poolMap;

    static EntityID nextEntityID;

public:
    ECS() = default;

    // Runs the system specified in the arguments. This function will pass
    // a vector of entity IDs that contain all components listed in the
    // template parameters.
    template <typename... Components>
    void runSystem(const SystemFunction& func);

    // "Creates" an entity and returns its ID.
    const EntityID createEntity();

    // Deletes an entity from all components
    void deleteEntity(const EntityID& id);

    // Returns a const reference to an entity's component data.
    template <typename ComponentType>
    ComponentType& getData(const EntityID& id);

    // Sets the data associated with the entity id to data.
    template <typename ComponentType>
    void setData(const EntityID& id, const ComponentType& data);

    // Returns true if the component specified in the template parameters holds
    // data for the entity specified in the function parameter.
    template <typename ComponentType>
    const bool hasData(const EntityID& id);

    // Creates a pool for the component specified in the template arguments.
    template <typename ComponentType>
    void registerComponent();

private:
    // Returns a vector of entity IDs that are tracked by all components
    // specified in the arguments.
    const EntityList queryComponents(const ComponentList& components);
};

}

#include "ECS.inl"
