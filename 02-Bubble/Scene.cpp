#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp> 
#include <GL/glew.h>
#include <GL/glut.h>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 60
#define SCREEN_Y 60

Scene::Scene()
{
	map = NULL;
	gameover = false;
	nextlevel = false;
	prevlevel = false;
}

Scene::Scene(string _levelFile)
{
	map = NULL;
	gameover = false; nextlevel = false;
	prevlevel = false; enterPortal = false;
	levelFile = _levelFile;
	int size = _levelFile.length();
	string sc = "";
	sc = _levelFile[size - 2];
	int num = stoi(sc) * 10;
	sc = _levelFile[size - 1];
	num += stoi(sc);
	Gui::instance().setScene(num);
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
	lives = 2;
	secHit = 30;
	secPunch = 30;

	Gui::instance().init();
	Game::instance().resetExp();
}

void Scene::update(int deltaTime)
{

	glm::ivec2 posPlayer = ent[sizeEnts - 1]->getPos();


	currentTime += deltaTime;
	for (int i = 0; i < ent.size(); ++i)
		ent[i]->update(deltaTime);
	for (int i = 0; i < enemy.size(); ++i)
		enemy[i]->update(deltaTime);

	if (map->nextLevel(ent[sizeEnts - 1]->getPos(), glm::ivec2(16, 16))) {
		nextlevel = true;
	}
		
	else if (map->prevLevel(ent[sizeEnts - 1]->getPos(), glm::ivec2(16, 16))) {
		prevlevel = true;
	}
		

	// entrar en portal
	if (Game::instance().getSpecialKey(GLUT_KEY_UP) && map->isOnPortal(posPlayer, glm::ivec2(32, 32))) {
		enterPortal = true;
	}
	

	//abrir puerta

	glm::ivec2 posDoor = ent[0]->getPos();

	//ser golpeado por enemigo -> habria que personalizar las hitbox para cada enemigo.
	if (!Game::instance().getGodMode() && secHit == 30) {
		for (int i = 0; i < enemy.size(); i++) {
			glm::ivec2 posPlayer = ent[sizeEnts - 1]->getPos();
			glm::ivec2 posEnemy = enemy[i]->getPos();
			if (ent[sizeEnts - 1]->LeftMove()) {
				if ((posEnemy.x+16 == posPlayer.x ) || (posEnemy.x + 16 == posPlayer.x +2) || (posEnemy.x == posPlayer.x+8 )) {
					if ((posEnemy.y - posPlayer.y) < 16 && 0 <= (posEnemy.y - posPlayer.y)) {
						if (enemy[i]->getState() == EnemyManager::ALIVE) {
							secHit = 0;
							lives--;
							if (lives <= 0) {
								gameover = true;
							}
						}
					}
				}
			}
			else {
				if ((posEnemy.x + 16 == posPlayer.x) || (posEnemy.x == posPlayer.x + 10) || (posEnemy.x +2 == posPlayer.x + 10)) {
 					if ((posEnemy.y - posPlayer.y) < 16 && 0 <= (posEnemy.y - posPlayer.y)) { 
						secHit = 0;
 						lives--;
 						if (lives <= 0) {
							gameover = true;
						}
					}
				}
			}
		}
	}
	if (secHit != 30) secHit++;
	if (Game::instance().getPunch() && secPunch == 30 && !ent[sizeEnts - 1]->IsClimbing()) {
		for (int i = 0; i < enemy.size(); i++) {
			glm::ivec2 posPlayer = ent[sizeEnts-1]->getPos();
 			glm::ivec2 posEnemy = enemy[i]->getPos();
			if (ent[sizeEnts - 1]->LeftMove()) {
				if ((0 < (posPlayer.x - posEnemy.x)) && ((posPlayer.x - posEnemy.x) <= 32)) {
					if ((posEnemy.y - posPlayer.y) < 16 && 0 <= (posEnemy.y - posPlayer.y)) {
						int lives_enemy = enemy[i]->hit();
						secPunch = 0;
						if (lives_enemy <= 0) enemy[i]->dies();//hay que añadir algo para que el golpe solo dure pocos frames.
						Game::instance().addTotalExp(10);
						Game::instance().addExp(10);
					}
				}
			}
			else {
				if ((0 < (posEnemy.x - posPlayer.x)) && ((posEnemy.x - posPlayer.x) <= 32)) {
					if ((posEnemy.y - posPlayer.y) < 16 && 0 <= (posEnemy.y - posPlayer.y)) {
						int lives_enemy = enemy[i]->hit();
						secPunch = 0;
 						if (lives_enemy <= 0) enemy[i]->dies();
						Game::instance().addTotalExp(10);
						Game::instance().addExp(10);
					}
				}
			}
			/*
			if (enemy[i]->getTypeEnemy() == 0) {
				if ((0 < (posPlayer.x - posEnemy.x) && (posPlayer.x - posEnemy.x) < 32) || (0 < (posEnemy.x - posPlayer.x) && (posEnemy.x - posPlayer.x) < 32)) {
					if ((posEnemy.y - posPlayer.y) < 32 && 0 < (posEnemy.y - posPlayer.y)) {
						int lives_enemy = enemy[i]->hit();
						if (lives_enemy <= 0) enemy[i]->dies();
						exp += 10;
					}
				}
			}
			else if (enemy[i]->getTypeEnemy() == 1) {
				if ((0 < (posPlayer.x - posEnemy.x) && (posPlayer.x - posEnemy.x) < 32) || (0 < (posEnemy.x - posPlayer.x) && (posEnemy.x - posPlayer.x) < 32)) {
					if ((posPlayer.y - posEnemy.y) < 32 && 0 < (posPlayer.y - posEnemy.y)) {
						int lives_enemy = enemy[i]->hit();
						if (lives_enemy <= 0) enemy.erase(enemy.begin() + i);
						exp += 20;
					}
				}
			}
			*/
		}
	}
	if (secPunch != 30) secPunch++;
	

}

SceneManager* Scene::changeScene() {
	if (gameover) {
		SceneManager* scene = new GameOverScene();
		scene->init();
		return scene;
	}
	else if (nextlevel) {
		SceneManager* scene = new Scene("levels/lv0" + next);
		scene->init();
		return scene;
	}
	else if (prevlevel) {
		SceneManager* scene = new Scene("levels/lv0" + prev);
		scene->init();
		return scene;
	}
	else if (enterPortal) {
		SceneManager* scene = new Scene("levels/lv0" + portalLevel);
		scene->init();
		return scene;
	}
	return this;
}

void Scene::render()
{
	Gui::instance().render();
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
	for (int i = 0; i < enemy.size(); ++i)
		enemy[i]->render();
	
}

bool Scene::loadEscena(const string& levelFile) {
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "ITEMS") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> sizeEnts >> prev >> next;
	//ent.resize(sizeEnts);
	for (int i = 0; i < sizeEnts; ++i) {
		getline(fin, line);
		sstream.str(line);
		sstream >> entity >> pos.x >> pos.y;
		if (entity == "PLAYER") {
			ent.push_back(new Player());
			ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
			ent[i]->setTileMap(map);
		}
		else if (entity == "PORTAL") {
			sstream >> portalLevel;
			ent.push_back(new Portal(portalLevel));
		}
		else if (entity == "DROP") {
			ent.push_back(new Drop());
			ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
			ent[i]->setTileMap(map);
		}
		else if (entity == "ROCK") {
			ent.push_back(new FallingRock());
			ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
			ent[i]->setTileMap(map);
		}
		else if (entity == "KEY") {
			ent.push_back(new Key());
			ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
			ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
			ent[i]->setTileMap(map);
		}
		
	}
	getline(fin, line);
		sstream.str(line);
		sstream >> sizeEnms;
		enemy.resize(sizeEnms);
		for (int i = 0; i < sizeEnms; ++i) {
			getline(fin, line);
			sstream.str(line);
			sstream >> entity >> pos.x >> pos.y;
			if (entity == "SKULL") {
				enemy[i] = new Skull();
				enemy[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				enemy[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
				enemy[i]->setTileMap(map);
			}
			else if (entity == "SKELETON") {
				enemy[i] = new Skeleton();
				enemy[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				enemy[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
				enemy[i]->setTileMap(map);
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



