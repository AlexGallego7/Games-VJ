#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "EntityManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "GameOverScene.h"
#include "Skull.h"
#include "Drop.h"
#include "Portal.h"
#include "Skeleton.h"
#include "Gui.h"
#include "Key.h"
#include "FallingRock.h"
#include "Door.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene : public SceneManager
{

public:
	Scene();
	Scene(string levelFile);
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	SceneManager* changeScene();
	int getEscena();
	bool loadEscena(const string& levelFile);

	void guardarEstado();

private:
	void initShaders();

private:
	bool gameover, nextlevel, prevlevel, enterPortal, charge_obj;
	string levelFile, entity, next, prev, portalLevel;
	int sizeEnts, sizeEnms, secHit, secPunch, num_scene;
	glm::ivec2 pos, posDoor;
	TileMap *map;
	vector<EntityManager*> ent;
	vector<EnemyManager*> enemy;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;


};


#endif // _SCENE_INCLUDE

