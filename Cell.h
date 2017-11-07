#include <SFML/Graphics.hpp>

class Cell {
	sf::RectangleShape rectangleShape;
	sf::Color aliveColor = sf::Color(0, 0, 0);
	sf::Color deadColor = sf::Color(255, 255, 255);

	float x, y;
	float width, height;

	bool alive;
public:
	void create(float, float, float, float);
	void setAlive(bool);

	sf::RectangleShape cellShape() { return rectangleShape; }

	bool isAlive() { return alive; }
	bool tempAlive = false;

	int aliveNeighbors = 0;
};
