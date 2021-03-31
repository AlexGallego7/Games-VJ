#ifndef _DROP_INCLUDE
#define _DROP_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "EntityManager.h"


class Drop : public EntityManager
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	int getTypeEntity();
	glm::ivec2 getPos();
	void open();

	bool LeftMove();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	float currentTime, dropTime;
	glm::ivec2 tileMapDispl, posPlayer, auxPos;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif // _PLAYER_INCLUDE


