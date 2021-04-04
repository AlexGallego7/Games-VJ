#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Door.h"
#include "Game.h"

enum DoorState {
	CLOSED, OPENED
};

void Door::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/door.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5f, 0.5f), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(CLOSED, 1);
	sprite->addKeyframe(CLOSED, glm::vec2(0.5f, 0.5f));

	sprite->setAnimationSpeed(OPENED, 1);
	sprite->addKeyframe(OPENED, glm::vec2(0.f, 0.f));

	sprite->changeAnimation(CLOSED);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Door::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void Door::render()
{
	sprite->render();
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
}

int Door::getTypeEntity() {
	return 3;
}

void Door::open() {
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