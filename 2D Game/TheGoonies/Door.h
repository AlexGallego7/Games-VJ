#ifndef _DOOR_INCLUDE
#define _DOOR_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "EntityManager.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Door : public EntityManager
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
	Texture spritesheet, spritesheet2;
	Sprite* sprite;
	Sprite* sprite2;
	TileMap* map;

};


#endif // _DOOR_INCLUDE