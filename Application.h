#include "Cell.h"

class Application {
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock clock;

	Cell cells[35][35];

	int columnLength = 35;
	int rowHeight = 35;

	int generationUpdateInterval = 2;

	bool paused;
	bool ranGeneration;
	bool mouseButtonPressed;
	bool rPressed;
	bool pPressed;

	void create();
	void loop();

	void generateGrid();
	void updateGeneration();
	void drawCells();

	void checkInput();
public:
	void run();
};
