#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "FallingRock.h"
#include "Game.h"

enum RockAnims
{
	CEILING, AIR, GROUND
};


void FallingRock::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	dropTime = currentTime;
	spritesheet.loadFromFile("images/falling_rock.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.5f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(CEILING, 8);
	sprite->addKeyframe(CEILING, glm::vec2(0.f, 0.f));


	sprite->setAnimationSpeed(AIR, 1);
	sprite->addKeyframe(AIR, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(GROUND, 1);
	sprite->addKeyframe(GROUND, glm::vec2(0.5f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void FallingRock::update(int deltaTime)
{
	currentTime += deltaTime;

	sprite->update(deltaTime);

	if (sprite->animation() == CEILING) {
		if (currentTime - dropTime > 1000) {
			posPlayer.y += 2;
			sprite->changeAnimation(AIR);
		}

	}

	else if (sprite->animation() == AIR) {
		posPlayer.y += 2;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(8, 8), &posPlayer.y)) {
			sprite->changeAnimation(GROUND);
		}
	}
	else if (sprite->animation() == GROUND) {
		dropTime = currentTime;
		if (currentTime - dropTime > 1000) {
			posPlayer.y = 800;
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void FallingRock::render()
{
	sprite->render();
}

void FallingRock::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void FallingRock::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	auxPos = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int FallingRock::getTypeEntity() {
	return 2;
}

glm::ivec2 FallingRock::getPos()
{
	return posPlayer;
}

void FallingRock::open() {}

bool FallingRock::LeftMove() {
	return 0;
}

