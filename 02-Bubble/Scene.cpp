#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp> 
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 60
#define SCREEN_Y 70

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 9


Scene::Scene()
{
	map = NULL;
	gameover = false;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
}

int Scene::getEscena() {
	return 2;
}

void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/lv01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	ents[0] = new Skull();
	ents[0]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	ents[0]->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), 14 * map->getTileSize()));
	ents[0]->setTileMap(map);

	ents[1] = new Player();
	ents[1]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	ents[1]->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	ents[1]->setTileMap(map);

	ents[2] = new Drop();
	ents[2]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	ents[2]->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	ents[2]->setTileMap(map);

	ents[3] = new Door();
	ents[3]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	ents[3]->setPosition(glm::vec2(20 * map->getTileSize(), 10 * map->getTileSize()));
	ents[3]->setTileMap(map);

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	ents[1]->update(deltaTime);
	ents[0]->update(deltaTime);
	ents[2]->update(deltaTime);
	ents[3]->update(deltaTime);

	if (Game::instance().getKey('f')) {
		gameover = true;
	}
}

SceneManager* Scene::changeScene() {
	if (gameover) {
		SceneManager* scene = new GameOverScene();
		scene->init();
		return scene;
	}
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, .0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	ents[3]->render();
	ents[1]->render();
	ents[0]->render();
	ents[2]->render();
}

void Scene::loadEscena() {
	// igual que el loadlevel cargamos un .txt con la info de las entidades y su posicion
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



