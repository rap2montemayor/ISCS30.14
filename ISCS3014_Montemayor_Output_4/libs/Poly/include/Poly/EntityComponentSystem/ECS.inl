#include "ECS.hpp"

namespace poly {

template <typename... Components>
void ECS::runSystem(const SystemFunction& function) {
    ComponentList components;
    (components.push_back(std::type_index(typeid(Components))),...);
    EntityList entities = queryComponents(components);
    function(entities);
}

template <typename ComponentType>
ComponentType& ECS::getData(const EntityID& entity) {
    const std::type_index idx(typeid(ComponentType));
    return *reinterpret_cast<ComponentType*>(
        poolMap[idx]->getEntityData(entity)
    );
}

template <typename ComponentType>
void ECS::setData(const EntityID& id, const ComponentType& data) {
    const std::type_index idx(typeid(ComponentType));
    poolMap[idx]->setEntityData(id, &data);
}

template <typename ComponentType>
void ECS::registerComponent() {
    const std::type_index idx(typeid(ComponentType));
    poolMap[idx] = std::make_unique<ComponentPool<ComponentType>>();
}

template <typename ComponentType>
const bool ECS::hasData(const EntityID& id) {
    const std::type_index idx(typeid(ComponentType));
    return poolMap[idx]->hasEntity(id);
}

}