#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "EndDoor.h"
#include "Game.h"
#include "EntState.h"

enum DoorState {
	CLOSED, OPENED
};

enum ElemState {
	A1
};

void EndDoor::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/enddoor.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(48, 56), glm::vec2(0.5f, 0.5f), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(CLOSED, 1);
	sprite->addKeyframe(CLOSED, glm::vec2(0.f, 0.f));


	sprite->setAnimationSpeed(OPENED, 1);
	sprite->addKeyframe(OPENED, glm::vec2(0.5f, 0.5f));

	sprite->changeAnimation(CLOSED);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void EndDoor::update(int deltaTime)
{
	currentTime += deltaTime;
	renderTime += deltaTime;
	sprite->update(deltaTime);
}

void EndDoor::render()
{
	sprite->render();
}

void EndDoor::setLevel(int level) {
	goTo_level = level;
}

void EndDoor::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void EndDoor::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int EndDoor::getTypeEntity() {
	return 10;
}

void EndDoor::open() {
	renderTime = currentTime;
	sprite->changeAnimation(OPENED);
}

glm::ivec2 EndDoor::getPos()
{
	return posPlayer;
}

bool EndDoor::LeftMove() {
	return 0;
}

bool EndDoor::IsClimbing() {
	return 0;
}


int EndDoor::getState() {
	return sprite->animation();
}

void EndDoor::setState(int num) {
	sprite->changeAnimation(num);
}

bool EndDoor::ObjectCatch() {
	return false;
}

void EndDoor::setSpeed(int s) {}

void EndDoor::setCatch() {

}