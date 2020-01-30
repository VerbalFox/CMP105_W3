#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	sf::CircleShape circle;
	sf::Vector2f circleHeading = sf::Vector2f(1, 0);
	sf::RectangleShape rect;
	sf::Vector2f rectHeading = sf::Vector2f(1, 0);
	float speed = 250;
	sf::CircleShape fourDirectionBouncyBoy;
	sf::Vector2f fourDirectionBouncyHeader = sf::Vector2f(1, 1);

	sf::CircleShape playerCircle;
	sf::Vector2f playerHeading = sf::Vector2f(0, 0);

	sf::Font font;
	sf::Text text;

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
};