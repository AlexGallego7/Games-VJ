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
	spritesheet.loadFromFile("images/drop.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.5f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(CEILING, 8);
	sprite->addKeyframe(CEILING, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(CEILING, glm::vec2(0.5f, 0.f));


	sprite->setAnimationSpeed(AIR, 8);
	sprite->addKeyframe(AIR, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(GROUND, 8);
	sprite->addKeyframe(GROUND, glm::vec2(0.5f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Drop::update(int deltaTime)
{
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
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int Drop::getTypeEntity() {
	return 2;
}

glm::ivec2 Drop::getPos()
{
	return posPlayer;
}




