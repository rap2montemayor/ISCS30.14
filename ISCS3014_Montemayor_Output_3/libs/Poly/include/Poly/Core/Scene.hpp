#pragma once

#include "Window.hpp"
#include <functional>
#include <memory>

namespace poly {

// Base class for scenes.
// To use, subclass the scene and override all virtual constructors. Subclass
// must call the superclass constructor.
class Scene {
public:
    using SceneConstructor = std::function<std::unique_ptr<Scene>()>;
    
    Scene(Window& window);
    virtual void processInput() = 0;
    virtual void render() = 0;
    virtual void update(double deltaTime) = 0;

    virtual void init() = 0;
    virtual void exit() = 0;

    const bool isExited();

    SceneConstructor getNextSceneConstructor();

protected:
    Window& window;
    SceneConstructor nextSceneConstructor;
    bool exited;
};

}
