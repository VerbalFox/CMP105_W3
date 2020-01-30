#include "Level.h"
#include <ctime>

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	if (!font.loadFromFile("font/arial.ttf")) {

	}

	text.setFont(font);
	text.setCharacterSize(16);

	rect.setFillColor(sf::Color(218, 165, 32));
	rect.setSize(sf::Vector2f(110, 60));
	rect.setPosition(100, 100);

	circle.setFillColor(sf::Color(218, 165, 32));
	circle.setRadius(30);
	circle.setPosition(100, 500);

	fourDirectionBouncyBoy.setFillColor(sf::Color::Magenta);
	fourDirectionBouncyBoy.setRadius(30);
	fourDirectionBouncyBoy.setPosition(100, 500);

	playerCircle.setFillColor(sf::Color::Red);
	playerCircle.setRadius(30);
	playerCircle.setPosition(window->getSize().x * .5, window->getSize().y * .5);
}

Level::~Level()
{
	srand(time(0));
}

// handle user input
void Level::handleInput(float dt)
{
	playerHeading = sf::Vector2f(
		(int)input->isKeyDown(sf::Keyboard::Right) + ((int)input->isKeyDown(sf::Keyboard::Left) * -1),
		(int)input->isKeyDown(sf::Keyboard::Down) + ((int)input->isKeyDown(sf::Keyboard::Up) * -1)
	);
}

// Update game objects
void Level::update(float dt)
{

	if (input->isKeyDown(sf::Keyboard::Add)) {
		speed += dt * 50;
	}

	if (input->isKeyDown(sf::Keyboard::Subtract)) {
		speed -= dt * 50;
	}

	if (playerCircle.getPosition().x > window->getSize().x - (playerCircle.getRadius() * 2)) {
		playerHeading.x = std::min(0, -1);
	}
	
	if (playerCircle.getPosition().y > window->getSize().y - (playerCircle.getRadius() * 2)) {
		playerHeading.y = std::min(0, -1);
	}

	if (playerCircle.getPosition().x < 0) {
		playerHeading.x = std::max(0, 1);
	}

	if (playerCircle.getPosition().y < 0) {
		playerHeading.y = std::max(0, 1);
	}

	if (circle.getPosition().x > window->getSize().x - (circle.getRadius() * 2) || 
		circle.getPosition().x < 0) {
		circleHeading.x *= -1;
	}
	
	if (rect.getPosition().x > window->getSize().x - (rect.getSize().x) ||
		rect.getPosition().x < 0) {
		rectHeading.x *= -1;
	}

	if (fourDirectionBouncyBoy.getPosition().x > window->getSize().x - (fourDirectionBouncyBoy.getRadius() * 2) ||
		fourDirectionBouncyBoy.getPosition().x < 0) {
		fourDirectionBouncyHeader.x *= -1;
	}

	if (fourDirectionBouncyBoy.getPosition().y > window->getSize().y - (fourDirectionBouncyBoy.getRadius() * 2) ||
		fourDirectionBouncyBoy.getPosition().y < 0) {
		fourDirectionBouncyHeader.y *= -1;
	}

	circle.setPosition(sf::Vector2f(
		circle.getPosition().x + (circleHeading.x * dt * speed),
		circle.getPosition().y + (circleHeading.y * dt * speed)
	));

	rect.setPosition(sf::Vector2f(
		rect.getPosition().x + (rectHeading.x * dt * speed),
		rect.getPosition().y + (rectHeading.y * dt * speed)
	)); 
	
	playerCircle.setPosition(sf::Vector2f(
		playerCircle.getPosition().x + (playerHeading.x * dt * speed),
		playerCircle.getPosition().y + (playerHeading.y * dt * speed)
	));
	
	fourDirectionBouncyBoy.setPosition(sf::Vector2f(
		fourDirectionBouncyBoy.getPosition().x + (fourDirectionBouncyHeader.x * dt * speed),
		fourDirectionBouncyBoy.getPosition().y + (fourDirectionBouncyHeader.y * dt * speed)
	));

	text.setString(std::to_string(speed));
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(playerCircle);
	window->draw(text);
	window->draw(fourDirectionBouncyBoy);
	window->draw(circle);
	window->draw(rect);
	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}