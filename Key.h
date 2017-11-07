#include <SFML/Graphics.hpp>

class Key {
	sf::Keyboard::Key key;

	bool pressed;
public:
	Key(sf::Keyboard::Key);

	bool getKey();
	bool getKeyDown();
};
