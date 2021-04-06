#ifndef _ENDDOOR_INCLUDE
#define _ENDDOOR_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "EntityManager.h"


class EndDoor : public EntityManager
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();
	int getTypeEntity();
	void open();

	glm::ivec2 getPos();


	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void setLevel(int level);
	bool LeftMove();
	bool IsClimbing();

	int getState();

	void setState(int num);

	bool ObjectCatch();

	void setSpeed(int s);

	void setCatch();


private:
	float currentTime, renderTime;
	int goTo_level;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif // _DOOR_INCLUDE