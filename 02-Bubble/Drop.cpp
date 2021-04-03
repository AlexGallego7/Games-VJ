#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Drop.h"
#include "Game.h"

enum DropAnims
{
	CEILING, AIR, GROUND
};


void Drop::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	dropTime = currentTime;
	spritesheet.loadFromFile("images/drop.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.5f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(CEILING, 1);
	sprite->addKeyframe(CEILING, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(CEILING, glm::vec2(0.5f, 0.f));


	sprite->setAnimationSpeed(AIR, 1);
	sprite->addKeyframe(AIR, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(GROUND, 1);
	sprite->addKeyframe(GROUND, glm::vec2(0.5f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Drop::update(int deltaTime)
{
	currentTime += deltaTime;

	sprite->update(deltaTime);

	if (sprite->animation() == CEILING) {
		posPlayer.y += 2;
		sprite->changeAnimation(AIR);
	}
	else if (sprite->animation() == AIR) {
		posPlayer.y += 2;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(8, 8), &posPlayer.y)) {
			sprite->changeAnimation(GROUND);
		}
	}
	else if (sprite->animation() == GROUND) {
		posPlayer.y = 800;
		if (currentTime - dropTime > 2000) {
			dropTime = currentTime;
			posPlayer.x = auxPos.x; posPlayer.y = auxPos.y;
			sprite->changeAnimation(CEILING);
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Drop::render()
{
	sprite->render();
}

void Drop::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Drop::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	auxPos = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int Drop::getTypeEnemy() {
	return 2;
}

glm::ivec2 Drop::getPos()
{
	return posPlayer;
}

int Drop::hit() {
	return 0;
}

void Drop::dies() {
	//
}

EnemyManager::EnemyStates Drop::getState() {
	return state;
}
