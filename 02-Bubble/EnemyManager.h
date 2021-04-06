#pragma once

#include <glm/glm.hpp>
#include "TileMap.h"

class EnemyManager {

public:

	enum EnemyStates
	{
		SPAWN, ALIVE, DEAD
	};

	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime) = 0;
	virtual void render() = 0;
	virtual int getTypeEnemy() = 0;
	virtual void dies() = 0;
	/*
	* 0-> skull
	* 1-> skeleton
	*/
	virtual glm::ivec2 getPos() = 0;


	virtual void setTileMap(TileMap* tileMap) = 0;
	virtual void setPosition(const glm::vec2& pos) = 0;
	virtual int hit() = 0;
	virtual EnemyStates getState() = 0; 
	virtual int getAnimation() = 0;
	virtual void trigger() = 0;

	EnemyStates state;
};