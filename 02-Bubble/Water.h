#ifndef _WATER_INCLUDE
#define _WATER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "EnemyManager.h"


class Water : public EnemyManager
{

public:
	Water(int loc);
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();
	int getTypeEnemy();

	glm::ivec2 getPos();

	int hit();
	void dies();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	EnemyManager::EnemyStates getState();

private:
	int loc;
	float currentTime, dropTime, highTime;
	glm::ivec2 tileMapDispl, posPlayer, auxPos;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif // _PLAYER_INCLUDE


