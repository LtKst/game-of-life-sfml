#include "Key.h"

Key::Key(sf::Keyboard::Key keyboardKey) {
	key = keyboardKey;
}

bool Key::getKey() {
	return sf::Keyboard::isKeyPressed(key);
}

bool Key::getKeyDown() {
	if (!pressed) {
		pressed = sf::Keyboard::isKeyPressed(key);
		return sf::Keyboard::isKeyPressed(key);
	}
	else {
		pressed = sf::Keyboard::isKeyPressed(key);
		return false;
	}
}
