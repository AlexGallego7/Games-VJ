#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "EntState.h"
#include "EndScene.h"

void Game::init()
{
	bPlay = true;
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	scene = new Menu();
	scene->init();
	godmode = false;
	punch = false;
	totalExp = 0;
	exp = 0;
	lives = 8;
	Gui::instance().init();
	for (int i = 0; i < 15; i++) {
		charged_scenes.push_back(false);
	}
	EntState::instance().resize(15);
}

bool Game::update(int deltaTime)
{
	scene->update(deltaTime);
	scene = scene->changeScene();
	punch = false;

	
	
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

	if (key == 'g' || key == 'G') godmode = !godmode;
	if (key == ' ') punch = true;

	if (scene->getEscena() == 0) {
		if (key == 'i' || key == 'I') {
			scene = new InstruccionsScene();
			scene->init();
		}
	}
	else if (scene->getEscena() == 1) {
		if (key == 'm' || key == 'M') {
			scene = new Menu();
			scene->init();
		}
	}
	else if (scene->getEscena() == 2) {
		if (key == 'm' || key == 'M') {
			charged_scenes.clear();
			for (int i = 0; i < 15; i++) {
				charged_scenes.push_back(false);
			}
			Gui::instance().setKey(false);
			Gui::instance().setHelmet(false);
			Gui::instance().setChus(false);
			Gui::instance().setShoes(false);
			Gui::instance().setGreenBook(false);
			Gui::instance().setGreyBook(false);
			resetLives();
			resetExp();
			scene = new Menu();
			scene->init();
		}
		if (key == 'r' || key == 'R') {
			charged_scenes.clear();
			for (int i = 0; i < 15; i++) {
				charged_scenes.push_back(false);
			}
			Gui::instance().setKey(false);
			Gui::instance().setHelmet(false);
			Gui::instance().setChus(false);
			Gui::instance().setShoes(false);
			Gui::instance().setGreenBook(false);
			Gui::instance().setGreyBook(false);
			resetLives();
			resetExp();
			scene = new Scene("levels/lv01");
			scene->init();
		}
		if (key == '1') {
			scene->guardarEstado();
			scene = new Scene("levels/lv01");
			scene->init();
		}
		if (key == '2') {
			scene->guardarEstado();
			scene = new Scene("levels/lv04");
			scene->init();
		}
		if (key == '3') {
			scene->guardarEstado();
			scene = new Scene("levels/lv07");
			scene->init();
		}
		if (key == '4') {
			scene->guardarEstado();
			scene = new Scene("levels/lv010");
			scene->init();
		}
		if (key == '5') {
			scene->guardarEstado();
			scene = new Scene("levels/lv013");
			scene->init();
		}
		if (key == 'q' || key == 'Q') {
			if (Gui::instance().hasShoes()) Gui::instance().setShoes(false);
			else Gui::instance().setShoes(true);
		}
		if (key == 'w' || key == 'W') {
			if(Gui::instance().hasGreenBook()) Gui::instance().setGreenBook(false);
			else Gui::instance().setGreenBook(true);
		}
		if (key == 'e' || key == 'E') {
			if (Gui::instance().hasGreyBook()) Gui::instance().setGreyBook(false);
			else Gui::instance().setGreyBook(true);
		}
		if (key == 't' || key == 'T') {
			if (Gui::instance().hasChus()) Gui::instance().setChus(false);
			else Gui::instance().setChus(true);
		}
		if (key == 'y' || key == 'Y') {
			if(Gui::instance().hasHelmet()) Gui::instance().setHelmet(false);
			else Gui::instance().setHelmet(true);
		}
		if (key == 'a' || key == 'A') {
			Gui::instance().setFriends(1);
		}


	}
	else if (scene->getEscena() == 3) {
		if (key == 'm' || key == 'M') {
			scene = new Menu();
			scene->init();
		}
	}
	else if (scene->getEscena() == 4) {
		if (key == 'm' || key == 'M') {
			scene = new Menu();
			scene->init();
		}
	}
	else if (scene->getEscena() == 5) {
		if (key == 'm' || key == 'M') {
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

bool Game::getGodMode() 
{
	return godmode;
}

bool Game::getPunch() {
	return punch;
}

void Game::addTotalExp(int exp) {
	totalExp += exp;
}

void Game::addExp(int exp) {
	this->exp += exp;
}

glm::ivec2 Game::getExp() {
	glm::vec2 exps;
	exps.x = totalExp;
	exps.y = exp;
	return exps;
}

void Game::resetExp() {
	this->exp = 0;
}

void Game::resetLives() {
	this->lives = 8;
}

int Game::getLives() {
	return lives;
}

void Game::setLives(int lives) {
	this->lives += lives;
}

bool Game::isCharged(int pos) {
	return charged_scenes[pos-1];
}

void Game::charged_scene(int pos) {
	charged_scenes[pos-1] = true;
}

void Game::setNumEsc(int num) {
	num_esc = num;
}

int Game::getNumEsc() {
	return num_esc;
}

void Game::setEnd() {
	charged_scenes.clear();
	for (int i = 0; i < 15; i++) {
		charged_scenes.push_back(false);
	}
	Gui::instance().setKey(false);
	Gui::instance().setHelmet(false);
	Gui::instance().setChus(false);
	Gui::instance().setShoes(false);
	Gui::instance().setGreenBook(false);
	Gui::instance().setGreyBook(false);
	Gui::instance().setFriends(-6);
	resetLives();
	resetExp();
	scene = new EndScene();
	scene->init();
}
