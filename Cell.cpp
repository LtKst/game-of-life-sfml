  #include "Cell.h"

void Cell::create(float posX, float posY, float sizeX, float sizeY) {
	x = posX;
	y = posY;

	width = sizeX;
	height = sizeY;

	rectangleShape = sf::RectangleShape(sf::Vector2f(sizeX, sizeY));
	rectangleShape.setPosition(posX, posY);
	rectangleShape.setFillColor(alive ? aliveColor : deadColor);

	rectangleShape.setOutlineThickness(2);
	rectangleShape.setOutlineColor(sf::Color(0, 0, 0));
}

void Cell::setAlive(bool aliveValue) {
	alive = aliveValue;

	rectangleShape.setFillColor(alive ? aliveColor : deadColor);
}
