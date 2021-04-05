#ifndef _shoes_INCLUDE
#define _shoes_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "EntityManager.h"


class shoes : public EntityManager
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	int getTypeEntity();
	glm::ivec2 getPos();
	void open();

	void setSpeed(int s);

	bool LeftMove();

	bool IsClimbing();

	int getState();

	void setState(int num);

	bool ObjectCatch();

	void setCatch();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

private:
	float currentTime, renderTime;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	bool cat;
};


#endif // _shoes_INCLUDE


