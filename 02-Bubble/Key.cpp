#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Key.h"
#include "Game.h"

enum KeyAnims
{
	SHOWN, NOT_SHOWN
};


void Key::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{

	renderTime = currentTime;
	spritesheet.loadFromFile("images/key.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.5f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);

	sprite->setAnimationSpeed(SHOWN, 8);
	sprite->addKeyframe(SHOWN, glm::vec2(0.f, 0.f));


	sprite->setAnimationSpeed(NOT_SHOWN, 8);
	sprite->addKeyframe(NOT_SHOWN, glm::vec2(0.f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Key::update(int deltaTime)
{
	currentTime += deltaTime;

	sprite->update(deltaTime);

	if (sprite->animation() == SHOWN) {
		if (currentTime - renderTime > 250) {
			renderTime = currentTime;
			sprite->changeAnimation(NOT_SHOWN);
		}
	}
	else if (sprite->animation() == NOT_SHOWN) {
		if (currentTime - renderTime > 250) {
			renderTime = currentTime;
			sprite->changeAnimation(SHOWN);
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Key::render()
{
	sprite->render();
}

void Key::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Key::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int Key::getTypeEntity() {
	return 2;
}

glm::ivec2 Key::getPos()
{
	return posPlayer;
}

void Key::open() {}


