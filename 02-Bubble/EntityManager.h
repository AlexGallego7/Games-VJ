#pragma once

#include <glm/glm.hpp>
#include "TileMap.h"

class EntityManager {

public:

	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime) = 0;
	virtual void render() = 0;
	virtual int getTypeEntity() = 0;
	/*
	tipo 0 -> enemigo
	tipo 1 -> jugador
	tipo 2 -> objeto
	tipo 3 -> puerta
	*/
	virtual glm::ivec2 getPos() = 0;


	virtual void setTileMap(TileMap* tileMap) = 0;
	virtual void setPosition(const glm::vec2& pos) = 0;

	enum EntityStates
	{
		SPAWNING, ALIVE, DEAD
	};

	EntityStates state;
};