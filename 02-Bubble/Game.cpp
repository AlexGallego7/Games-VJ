#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene = new Menu();
	scene->init();
}

bool Game::update(int deltaTime)
{
	scene->update(deltaTime);
	scene = scene->changeScene();
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->render();
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;

	if (scene->getEscena() == 0) {
		if (key == 'i') {
			scene = new InstruccionsScene();
			scene->init();
		}
	}
	if (scene->getEscena() == 1) {
		if (key == 'm') {
			scene = new Menu();
			scene->init();
		}
	}
	if (scene->getEscena() == 3) {
		if (key == 'm') {
			scene = new Menu();
			scene->init();
		}
	}

	


}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





