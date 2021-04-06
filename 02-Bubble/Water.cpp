#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Water.h"
#include "Game.h"

enum WaterAnims
{
	NONE, LOW1, LOW2, HIGH1, HIGH2
};

Water::Water(int loc) {
	this->loc = loc;
}

void Water::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	dropTime = currentTime;
	highTime = currentTime;
	spritesheet.loadFromFile("images/water.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);

	sprite->setAnimationSpeed(NONE, 8);
	sprite->addKeyframe(NONE, glm::vec2(0.75f, 0.75f));

	if(loc) {
		sprite->setAnimationSpeed(LOW1, 8);
		sprite->addKeyframe(LOW1, glm::vec2(0.f, 0.f));
		sprite->setAnimationSpeed(LOW2, 8);
		sprite->addKeyframe(LOW2, glm::vec2(0.f, 0.25f));

		sprite->setAnimationSpeed(HIGH1, 8);
		sprite->addKeyframe(HIGH1, glm::vec2(0.5f, 0.f));
		sprite->setAnimationSpeed(HIGH2, 8);
		sprite->addKeyframe(HIGH2, glm::vec2(0.75f, 0.f));
	}
	else {
		sprite->setAnimationSpeed(LOW1, 8);
		sprite->addKeyframe(LOW1, glm::vec2(0.25f, 0.f));
		sprite->setAnimationSpeed(LOW2, 8);
		sprite->addKeyframe(LOW2, glm::vec2(0.25f, 0.25f));

		sprite->setAnimationSpeed(HIGH1, 1);
		sprite->addKeyframe(HIGH1, glm::vec2(0.5f, 0.25f));
		sprite->setAnimationSpeed(HIGH2, 1);
		sprite->addKeyframe(HIGH2, glm::vec2(0.75f, 0.25f));
	}

	sprite->changeAnimation(NONE);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Water::update(int deltaTime)
{
	currentTime += deltaTime;

	sprite->update(deltaTime);

	if (sprite->animation() == NONE) {
		if (currentTime - dropTime > 1000) {
			dropTime = currentTime;
			highTime = currentTime;
			sprite->changeAnimation(LOW1);
		}
	}
	else if (sprite->animation() == LOW1) {
		if (currentTime - dropTime > 1000) {
			dropTime = currentTime;
			sprite->changeAnimation(LOW2);
		}
	}
	else if (sprite->animation() == LOW2) {
		if (currentTime - dropTime > 1000 && currentTime - highTime < 5000) {
			dropTime = currentTime;
			sprite->changeAnimation(LOW1);
		}
		else if (currentTime - dropTime > 5000) {
			dropTime = currentTime;
			highTime = currentTime;
			sprite->changeAnimation(HIGH1);
		}
	}
	else if (sprite->animation() == HIGH1) {
		if (currentTime - dropTime > 1000) {
			dropTime = currentTime;
			sprite->changeAnimation(HIGH2);
		}
	}
	else if (sprite->animation() == HIGH2) {
		if (currentTime - dropTime > 1000 && currentTime - highTime < 5000) {
			dropTime = currentTime;
			sprite->changeAnimation(HIGH1);
		}
		else if (currentTime - dropTime > 5000) {
			dropTime = currentTime;
			sprite->changeAnimation(NONE);
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Water::render()
{
	sprite->render();
}

void Water::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Water::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	auxPos = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int Water::getTypeEnemy() {
	return 4;
}

glm::ivec2 Water::getPos()
{
	return posPlayer;
}

int Water::hit() {
	return 0;
}

void Water::dies() {
	//
}

EnemyManager::EnemyStates Water::getState() {
	return state;
}
int Water::getAnimation() {
	return sprite->animation();
}
