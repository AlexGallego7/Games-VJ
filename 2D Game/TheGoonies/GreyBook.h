#ifndef _greyBook_INCLUDE
#define _greyBook_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "EntityManager.h"


class greyBook : public EntityManager
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	int getTypeEntity();
	void setSpeed(int s);
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


#endif // _greyBook_INCLUDE


