#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "EntityManager.h"
#include "Player.h"
#include "SceneManager.h"
#include "GameOverScene.h"
#include "Skull.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene : public SceneManager
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	SceneManager* changeScene();
	int getEscena();

private:
	void initShaders();

private:
	bool gameover;
	TileMap *map;
	EntityManager* ents[2];
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE

