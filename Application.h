#include "MouseButton.h"
#include "Key.h"
#include "Cell.h"

class Application {
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock clock;

	MouseButton leftMouseButton = MouseButton(sf::Mouse::Left);

	Key rKey = Key(sf::Keyboard::R);
	Key cKey = Key(sf::Keyboard::C);
	Key pKey = Key(sf::Keyboard::P);
	Key qKey = Key(sf::Keyboard::Q);

	Cell cells[35][35];

	int columnLength = 35;
	int rowHeight = 35;

	int generationUpdateInterval = 2;

	bool paused;
	bool ranGeneration;

	void create();
	void loop();

	void generateGrid();
	void updateGeneration();
	void drawCells();

	void checkInput();
public:
	void run();
};
