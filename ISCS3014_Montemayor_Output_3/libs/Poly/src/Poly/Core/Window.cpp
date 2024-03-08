#include "Poly/Core/Window.hpp"

namespace poly {

void Window::init(const unsigned int width, const unsigned int height,
        const char* title, const unsigned int style) {
    this->width = width;
    this->height = height;
    this->title = title;
    this->style = style;
    renderWindow.create(sf::VideoMode(width, height), title, style);
    renderWindow.setVerticalSyncEnabled(true);
}

void Window::beginRender() {
    renderWindow.clear();
}

void Window::render(sf::Drawable& drawable) {
    renderWindow.draw(drawable);
}

void Window::endRender() {
    renderWindow.display();
}

void Window::pollInput() {
    inputs.clear();
    sf::Event inputEvent;
    while (renderWindow.pollEvent(inputEvent)) {
        inputs.push_back(inputEvent);
    }
}

const std::pair<unsigned int, unsigned int> Window::getDimensions() {
    return {width, height};
}

const unsigned int Window::getStyle() {
    return style;
}

const char* Window::getTitle() {
    return title;
}

const sf::View& Window::getDefaultView() {
    return renderWindow.getDefaultView();
}

const sf::View& Window::getView() {
    return renderWindow.getView();
}

void Window::setView(const sf::View& view) {
    renderWindow.setView(view);
}

const InputContainer& Window::getInputs() {
    return inputs;
}

}
