#include "Poly/Core/Scene.hpp"

namespace poly {

Scene::Scene(Window& window)
    : window(window), nextSceneConstructor(nullptr),
        exited(false) {}

const bool Scene::isExited() {
    return exited;
}

Scene::SceneConstructor Scene::getNextSceneConstructor() {
    return nextSceneConstructor;
}

}