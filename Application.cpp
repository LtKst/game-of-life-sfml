#include <SFML/Graphics.hpp>
#include "Application.h"

void Application::run() {
	srand(time(0));

	printf("Press 'r' to randomize\nPress 'p' to pause or unpause\n");

	create();

	generateGrid();
	drawCells();

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		loop();
	}
}

void Application::create() {
	window.create(sf::VideoMode(720, 720), "Conway's Game of Life", sf::Style::Titlebar | sf::Style::Close);
}

void Application::generateGrid() {
	for (int i = 0; i < columnLength; i++) {
		for (int j = 0; j < rowHeight; j++) {
			cells[i][j].create(10 + 20 * i, 10 + 20 * j, 20, 20);

			int rnd = rand() % 2;

			cells[i][j].setAlive(rnd == 0);
		}
	}
}

void Application::loop() {
	window.clear(sf::Color(40, 45, 50));

	sf::Int64 usec = clock.getElapsedTime().asSeconds();

	if (usec % generationUpdateInterval == 0 && !ranGeneration && !paused) {
		updateGeneration();

		ranGeneration = true;
	}
	else if (usec % generationUpdateInterval != 0) {
		ranGeneration = false;
	}

	checkInput();

	drawCells();

	window.display();
}

void Application::updateGeneration() {
	// count alive neigbors
	for (int i = 0; i < columnLength; i++) {
		for (int j = 0; j < rowHeight; j++) {
			cells[i][j].aliveNeighbors = 0;

			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					if (i + x >= 0 && i + x < columnLength && j + y >= 0 && j + y < rowHeight && !(x == 0 && y == 0) && cells[i + x][j + y].isAlive()) {
						cells[i][j].aliveNeighbors++;
					}
				}
			}
		}
	}

	// set temp alive
	for (int i = 0; i < columnLength; i++) {
		for (int j = 0; j < rowHeight; j++) {
			if (cells[i][j].isAlive()) {
				if (cells[i][j].aliveNeighbors == 3 || cells[i][j].aliveNeighbors == 2) {
					cells[i][j].tempAlive = true;
				}
				else {
					cells[i][j].tempAlive = false;
				}
			}
			else {
				if (cells[i][j].aliveNeighbors == 3) {
					cells[i][j].tempAlive = true;
				}
				else {
					cells[i][j].tempAlive = false;
				}
			}
		}
	}

	// set alive
	for (int i = 0; i < columnLength; i++) {
		for (int j = 0; j < rowHeight; j++) {
			cells[i][j].setAlive(cells[i][j].tempAlive);
		}
	}
}

void Application::drawCells() {
	for (int i = 0; i < columnLength; i++) {
		for (int j = 0; j < rowHeight; j++) {
			window.draw(cells[i][j].cellShape());
		}
	}
}

void Application::checkInput() {
	// check if user clicked on a cell
	if (!mouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		for (int i = 0; i < columnLength; i++) {
			for (int j = 0; j < rowHeight; j++) {
				if (sf::Mouse::getPosition(window).x >= cells[i][j].cellShape().getPosition().x
					&& sf::Mouse::getPosition(window).x <= cells[i][j].cellShape().getPosition().x + cells[i][j].cellShape().getSize().x
					&& sf::Mouse::getPosition(window).y >= cells[i][j].cellShape().getPosition().y
					&& sf::Mouse::getPosition(window).y <= cells[i][j].cellShape().getPosition().y + cells[i][j].cellShape().getSize().y) {

					cells[i][j].setAlive(!cells[i][j].isAlive());

					printf(cells[i][j].isAlive() ? "Clicked on cell and brought it to life\n" : "Clicked on cell and killed it\n");

					window.draw(cells[i][j].cellShape());
				}
			}
		}

		mouseButtonPressed = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		mouseButtonPressed = false;
	}

	// check if the user randomized
	if (!rPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		for (int i = 0; i < columnLength; i++) {
			for (int j = 0; j < rowHeight; j++) {
				cells[i][j].create(10 + 20 * i, 10 + 20 * j, 20, 20);

				int rnd = rand() % 2;

				cells[i][j].setAlive(rnd == 0);
			}
		}

		printf("Randomized\n");

		rPressed = true;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		rPressed = false;
	}

	// check if the user paused
	if (!pPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		paused = !paused;

		printf(paused ? "Paused\n" : "Unpaused\n");

		pPressed = true;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		pPressed = false;
	}
}