#ifndef _PORTAL_INCLUDE
#define _PORTAL_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "EntityManager.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Portal : public EntityManager
{

public:
	Portal(string level);
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();
	int getTypeEntity();
	void open();

	glm::ivec2 getPos();


	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void setLevel(int level);
	string getLevel();

	bool LeftMove();

private:
	string goTo_level;
	glm::ivec2 tileMapDispl, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif // _PORTAL_INCLUDE


