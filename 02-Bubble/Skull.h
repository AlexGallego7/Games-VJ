#ifndef _SKULL_INCLUDE
#define _SKULL_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "EnemyManager.h"

class Skull: public EnemyManager
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();
	int getTypeEnemy();

	glm::ivec2 getPos();

	int hit();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY, lives;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif // _Skull_INCLUDE


