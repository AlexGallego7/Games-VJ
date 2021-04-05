#include "shoes.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "shoes.h"
#include "Game.h"
#include "EntState.h"


enum shoesAnims
{
	SHOWN, NOT_SHOWN, CATCH
};


void shoes::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	renderTime = currentTime;
	spritesheet.loadFromFile("images/bag_items.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.5f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(SHOWN, 8);
	sprite->addKeyframe(SHOWN, glm::vec2(0.f, 0.f));


	sprite->setAnimationSpeed(NOT_SHOWN, 8);
	sprite->addKeyframe(NOT_SHOWN, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(CATCH, 8);
	sprite->addKeyframe(CATCH, glm::vec2(0.f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void shoes::update(int deltaTime)
{
	currentTime += deltaTime;

	sprite->update(deltaTime);

	if (cat) {
		sprite->changeAnimation(CATCH);
	}
	else if (sprite->animation() == SHOWN) {
		if (currentTime - renderTime > 250) {
			renderTime = currentTime;
			sprite->changeAnimation(NOT_SHOWN);
		}
	}
	else if (sprite->animation() == NOT_SHOWN) {
		if (currentTime - renderTime > 250) {
			renderTime = currentTime;
			sprite->changeAnimation(SHOWN);
		}
	}


	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void shoes::render()
{
	if (!cat)sprite->render();
}

void shoes::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void shoes::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int shoes::getTypeEntity() {
	return 14;
}

glm::ivec2 shoes::getPos()
{
	return posPlayer;
}

void shoes::open() {}
void shoes::setSpeed(int s) {}

bool shoes::LeftMove() {
	return 0;
}

bool shoes::IsClimbing() {
	return 0;
}


int shoes::getState() {
	return sprite->animation();
}

void shoes::setState(int num) {
	sprite->animation() == num;
}

bool shoes::ObjectCatch() {
	return cat;
}

void shoes::setCatch() {


	cat = true;
}

