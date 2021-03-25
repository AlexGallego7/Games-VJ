#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp> 
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 60
#define SCREEN_Y 60

Scene::Scene()
{
	map = NULL;
	gameover = false;
}

Scene::Scene(string _levelFile)
{
	map = NULL;
	gameover = false;
	levelFile = _levelFile;
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
	map = TileMap::createTileMap(levelFile + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	loadEscena(levelFile + "_items.txt");

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	lives = 999;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	for (int i = 0; i < ent.size(); ++i)
		ent[i]->update(deltaTime);

	if (Game::instance().getKey('f')) {
		gameover = true;
	}

	for (int i = 0; i < ent.size(); i++) {
		if (ent[i]->getTypeEntity() == 0 && !Game::instance().getGodMode()) {
			glm::ivec2 posPlayer = ent[0]->getPos();
			glm::ivec2 posEnemy = ent[i]->getPos();
			if (posPlayer.x == posEnemy.x) {
				if ((posPlayer.y - posEnemy.y) < 16) {
					lives--;
				}
			}
		}
	}

	if (lives == 0) {
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
	for (int i = 0; i < ent.size(); ++i)
		ent[i]->render();
}

bool Scene::loadEscena(const string& levelFile) {
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	int size;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "ITEMS") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> size;
	ent.resize(size);
	for (int i = 0; i < size; ++i) {
		getline(fin, line);
		sstream.str(line);
		sstream >> entity >> pos.x >> pos.y;
		if (entity == "PLAYER") {
			ent[i] = new Player();
			ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
			ent[i]->setTileMap(map);
		}
		else if (entity == "SKULL") {
			ent[i] = new Skull();
			ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
			ent[i]->setTileMap(map);
		}
		else if (entity == "SKELETON") {
			ent[i] = new Skeleton();
			ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
			ent[i]->setTileMap(map);
		}
		else if (entity == "DOOR") {
			ent[i] = new Door();
			ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
			ent[i]->setTileMap(map);
		}
		else if (entity == "DROP") {
			ent[i] = new Drop();
			ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
			ent[i]->setTileMap(map);
		}
	}
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



