#include "Poly/Core/Window.hpp"

namespace poly {

void Window::init(const unsigned int width, const unsigned int height,
		const char* title, const unsigned int style) {
	this->width = width;
	this->height = height;
	this->title = title;
	this->style = style;
	renderWindow.create(sf::VideoMode(width, height), title, style);
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

const InputContainer Window::pollInput() {
	InputContainer inputs;
	sf::Event inputEvent;
    while (renderWindow.pollEvent(inputEvent)) {
		inputs.push_back(inputEvent);
    }
	return inputs;
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

sf::RenderWindow& Window::getRenderWindow() {
	return renderWindow;
}

}
