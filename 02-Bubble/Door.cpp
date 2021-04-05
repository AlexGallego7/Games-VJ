#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Door.h"
#include "Game.h"
#include "EntState.h"

enum DoorState {
	CLOSED, OPENED, OPENED_2 
};

enum ElemState {
	A1
};

void Door::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/door.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet2.loadFromFile("images/friend.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5f, 0.5f), &spritesheet, &shaderProgram);
	sprite2 = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(0.5f, 0.5f), &spritesheet2, &shaderProgram);

	sprite->setNumberAnimations(3);
	sprite2->setNumberAnimations(2);

	sprite->setAnimationSpeed(CLOSED, 1);
	sprite->addKeyframe(CLOSED, glm::vec2(0.5f, 0.5f));

	sprite2->setAnimationSpeed(A1, 8);
	sprite2->addKeyframe(A1, glm::vec2(0.5f, 0.5f));
	sprite2->addKeyframe(A1, glm::vec2(0.f, 0.f));


	sprite->setAnimationSpeed(OPENED, 1);
	sprite->addKeyframe(OPENED, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(OPENED_2, 1);
	sprite->addKeyframe(OPENED_2, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(CLOSED);
	sprite->changeAnimation(A1);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite2->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Door::update(int deltaTime)
{
	currentTime += deltaTime;
	renderTime += deltaTime;
	sprite->update(deltaTime);
	if (sprite->animation() == OPENED) {
		sprite2->update(deltaTime);
	}

}

void Door::render()
{
	sprite->render();
	if (sprite->animation() == OPENED) {
		if (currentTime - renderTime < 200)
			sprite2->render();
	}
}

void Door::setLevel(int level) {
	goTo_level = level;
}

void Door::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Door::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	sprite2->setPosition(glm::vec2(float(tileMapDispl.x + (posPlayer.x + 32)), float(tileMapDispl.y + (posPlayer.y + 32))));
}

int Door::getTypeEntity() {
	return 4;
}

void Door::open() {
	renderTime = currentTime;
	sprite->changeAnimation(OPENED);
}

glm::ivec2 Door::getPos()
{
	return posPlayer;
}

bool Door::LeftMove() {
	return 0;
}

bool Door::IsClimbing() {
	return 0;
}


int Door::getState() {
	return sprite->animation();
}

void Door::setState(int num) {
	sprite->changeAnimation(num);
}

bool Door::ObjectCatch(){
	return false;
}

void Door::setCatch() {

}