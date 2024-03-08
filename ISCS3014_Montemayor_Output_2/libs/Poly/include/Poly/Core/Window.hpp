#pragma once

#include <vector>
#include <utility>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace poly {

using InputContainer = std::vector<sf::Event>;

class Window {
	friend class Game;

	sf::RenderWindow renderWindow;
	unsigned int width;
	unsigned int height;
	unsigned int style;
	const char* title;

public:
	Window() = default;

	// Render a drawable object to the render window.
	void render(sf::Drawable& drawable);

	const std::pair<unsigned int, unsigned int> getDimensions();

	const unsigned int getStyle();

	const char* getTitle();

	sf::RenderWindow& getRenderWindow();

private:
	// Initializes the underlying render window. This can be called again to
	// recreate the window.
	void init(const unsigned int width, const unsigned int height,
		const char* title, const unsigned int style);

	// Prepares the render window for rendering.
	void beginRender();

	// Display what has been rendered to the screen.
	void endRender();

	// Polls all events from the render window and passes them to the input
	// manager for processing.
	const InputContainer pollInput();
};

}
