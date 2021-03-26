#ifndef _FALLINGROCK_INCLUDE
#define _FALLINGROCK_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "EntityManager.h"


class FallingRock : public EntityManager
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	int getTypeEntity();
	glm::ivec2 getPos();
	void open();

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


#endif // _FALLINGROCK_INCLUDE


