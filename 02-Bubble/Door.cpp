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
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
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

glm::ivec2 Door::getPos()
{
	return posPlayer;
} 





