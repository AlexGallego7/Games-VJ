#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Skull.h"
#include "Game.h"

enum SkullAnims
{
	MOVE_LEFT, MOVE_RIGHT
};


void Skull::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/en1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.5f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.f));


	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Skull::update(int deltaTime)
{
	sprite->update(deltaTime);

	if(sprite->animation() == MOVE_LEFT){
		posPlayer.x -= 2;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(16, 16))) {
			sprite->changeAnimation(MOVE_RIGHT);
		}
	}
	else if (sprite->animation() == MOVE_RIGHT) {
		posPlayer.x += 2;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(16, 16))) {
			sprite->changeAnimation(MOVE_LEFT);
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Skull::render()
{
	sprite->render();
}

void Skull::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Skull::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int Skull::getTypeEnemy() {
	return 0;
}

glm::ivec2 Skull::getPos()
{
	return posPlayer;
}



