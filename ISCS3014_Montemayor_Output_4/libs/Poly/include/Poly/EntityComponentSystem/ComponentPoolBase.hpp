#pragma once

#include "Entity.hpp"

namespace poly {

// An abstract base class for component pools. This will be used to make a
// container of component pools via polymorphism.
class ComponentPoolBase {
    // Only the ECS should have access to this interface. Hence, a friend class
    // instead of a public interface.
    friend class ECS;

    // Returns a void* to an entity's component data.
    virtual void* getEntityData(const EntityID id) = 0;

    // Sets the entity's component data to whatever is in the data pointer.
    virtual void setEntityData(const EntityID id, const void* data) = 0;

    virtual void deleteEntityData(const EntityID id) = 0;

    // Gets the number of entities being tracked by this component pool.
    virtual const int getSize() = 0;

    // Checks if this component pool has an entry for this entity.
    virtual const bool hasEntity(EntityID id) = 0;

    virtual const EntityList getEntities() = 0;
};

}
