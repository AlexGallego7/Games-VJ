#ifndef _SKELETON_INCLUDE
#define _SKELETON_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "EnemyManager.h"

class Skeleton : public EnemyManager
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();
	int getTypeEnemy();

	int getAnimation();

	glm::ivec2 getPos();

	int hit();
	void dies();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	EnemyManager::EnemyStates getState();


private:
	glm::ivec2 tileMapDispl, posPlayer;
	float currentTime, spawnTime;
	int jumpAngle, startY, lives;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif // _SKELETON_INCLUDE


