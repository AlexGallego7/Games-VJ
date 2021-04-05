#ifndef _helmet_INCLUDE
#define _helmet_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "EntityManager.h"


class helmet : public EntityManager
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	int getTypeEntity();
	glm::ivec2 getPos();
	void open();

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


#endif // _helmet_INCLUDE


