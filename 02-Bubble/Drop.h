#ifndef _DROP_INCLUDE
#define _DROP_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "EnemyManager.h"


class Drop : public EnemyManager
{

public:
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
	float currentTime, dropTime;
	glm::ivec2 tileMapDispl, posPlayer, auxPos;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif // _PLAYER_INCLUDE


