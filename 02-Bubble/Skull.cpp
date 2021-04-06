#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Skull.h"
#include "Game.h"

#define FALL_STEP 4

enum SkullAnims
{
	SPAWNING, MOVE_LEFT, MOVE_RIGHT, DYING
};

void Skull::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spawnTime = currentTime;

	spritesheet.loadFromFile("images/skull.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5f, 0.25f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(SPAWNING, 8);
	sprite->addKeyframe(SPAWNING, glm::vec2(0.f, 0.75f));
	sprite->addKeyframe(SPAWNING, glm::vec2(0.5f, 0.75f));

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.f));


	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.25f));

	sprite->setAnimationSpeed(DYING, 8);
	sprite->addKeyframe(DYING, glm::vec2(0.f, 0.5f));

	sprite->changeAnimation(SPAWNING);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

	lives = 1;

}

void Skull::update(int deltaTime)
{
	currentTime += deltaTime;
	sprite->update(deltaTime);
	posPlayer.y += FALL_STEP;

	posPlayer.x -= 32;
	if (!map->collisionMoveDownEnemies(posPlayer, glm::ivec2(16, 16), &posPlayer.y)) {
		if (sprite->animation() == MOVE_LEFT) {
			sprite->changeAnimation(MOVE_RIGHT);
		}
		else {
			sprite->changeAnimation(MOVE_LEFT);
		}
	}
	posPlayer.x += 32;
	posPlayer.y += FALL_STEP;
	posPlayer.x += 32;
	if (!map->collisionMoveDownEnemies(posPlayer, glm::ivec2(16, 16), &posPlayer.y)) {
		if (sprite->animation() == MOVE_LEFT) {
			sprite->changeAnimation(MOVE_RIGHT);
		}
		else {
			sprite->changeAnimation(MOVE_LEFT);
		}
	}
	posPlayer.x -= 32;



	if (sprite->animation() == SPAWNING) {
		state = SPAWN;
		if ((currentTime - spawnTime) > 2000) {
			state = ALIVE;
			sprite->changeAnimation(MOVE_LEFT);
		}
	}	
	else if(sprite->animation() == MOVE_LEFT){
		posPlayer.x -= 2;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(16, 16))) {
			sprite->changeAnimation(MOVE_RIGHT);
		}
	}
	else if (sprite->animation() == MOVE_RIGHT) {
		posPlayer.x += 2;
		if (map->collisionMoveRight(posPlayer, glm::ivec2(16, 16)) ) {
			sprite->changeAnimation(MOVE_LEFT);
		}
	}

	else if (sprite->animation() == DYING) {
		state = DEAD;
		if (currentTime - spawnTime > 1000) {
			posPlayer.x = 10000;
			posPlayer.y = 10000;
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Skull::render()
{
	sprite->render();
}

int Skull::getAnimation() {
	return sprite->animation();
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

int Skull::hit() {
	lives--;
	return lives;
}

void Skull::dies() {
	spawnTime = currentTime;
	sprite->changeAnimation(DYING);
}

EnemyManager::EnemyStates Skull::getState() {
	return state;
}



