#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Portal.h"
#include "Game.h"

Portal::Portal(string level) {
	goTo_level = level;
}

void Portal::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	tileMapDispl = tileMapPos;
}

void Portal::update(int deltaTime)
{
}

void Portal::render()
{
}

void Portal::setLevel(int level) {
	goTo_level = level;
}

void Portal::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Portal::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
}

int Portal::getTypeEntity() {
	return 3;
}

void Portal::open() { }

glm::ivec2 Portal::getPos()
{
	return posPlayer;
} 

string Portal::getLevel() {
	return goTo_level;
}

bool Portal::LeftMove() {
	return 0;
}

bool Portal::IsClimbing() {
	return 0;
}


int Portal::getState() {
	return 0;
}

void Portal::setState(int num) {
	sprite->animation() == num;
}

bool Portal::ObjectCatch() {
	return false;
}

void Portal::setCatch() {

}
