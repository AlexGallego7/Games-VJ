#pragma once

#include <glm/glm.hpp>
#include "TileMap.h"

class EntityManager {

public:

	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime) = 0;
	virtual void render() = 0;
	virtual int getTypeEntity() = 0;
	virtual void open() = 0;
	virtual void setState(int num) = 0;
	virtual void setSpeed(int s) = 0;
	/*
	tipo 0 -> enemigo
	tipo 1 -> jugador
	tipo 2 -> objeto
	tipo 3 -> portal
	tipo 4 -> puerta
	*/
	virtual glm::ivec2 getPos() = 0;


	virtual void setTileMap(TileMap* tileMap) = 0;
	virtual void setPosition(const glm::vec2& pos) = 0;
	virtual bool LeftMove() = 0; 
	virtual bool IsClimbing() = 0;
	virtual int getState() = 0;
	virtual bool ObjectCatch() = 0;
	virtual void setCatch() = 0;
	enum EntityStates
	{
		SPAWNING, ALIVE, DEAD
	};
	//10 -> helmet
	EntityStates state;
};