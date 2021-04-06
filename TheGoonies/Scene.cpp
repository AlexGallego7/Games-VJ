#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp> 
#include <GL/glew.h>
#include <GL/glut.h>
#include "Scene.h"
#include "Game.h"
#include "EntState.h"
#include "helmet.h"
#include "greyBook.h"
#include "greenBook.h"
#include "Chus.h"
#include "Shoes.h"
#include "MoneyBag.h"

#define SCREEN_X 60
#define SCREEN_Y 60

Scene::Scene()
{
	map = NULL;
	gameover = false;
	nextlevel = false;
	prevlevel = false;
	win = false;
}

Scene::Scene(string _levelFile)
{
	map = NULL;
	gameover = false; nextlevel = false;
	prevlevel = false; enterPortal = false;
	win = false;
	levelFile = _levelFile;
	int size = _levelFile.length();
	string sc = "";
	sc = _levelFile[size - 2];
	int num = stoi(sc) * 10;
	sc = _levelFile[size - 1];
	num += stoi(sc);
	Gui::instance().setScene(num);
	if (!Game::instance().isCharged(num)) charge_obj = true;
	else charge_obj = false;
	num_scene = num;
	Game::instance().setNumEsc(num);
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
	secHit = 30;
	secPunch = 30;
	
	
}

void Scene::update(int deltaTime)
{

	Gui::instance().update(deltaTime);

	glm::ivec2 posPlayer = ent[sizeEnts - 1]->getPos();


	currentTime += deltaTime;
	for (int i = 0; i < ent.size(); ++i)
		ent[i]->update(deltaTime);
	for (int i = 0; i < enemy.size(); ++i)
		enemy[i]->update(deltaTime);

	if (map->nextLevel(ent[sizeEnts - 1]->getPos(), glm::ivec2(16, 16), Gui::instance().hasShoes())) {
		nextlevel = true;
	}
		
	else if (map->prevLevel(ent[sizeEnts - 1]->getPos(), glm::ivec2(16, 16))) {
		prevlevel = true;
	}
		
	if (Gui::instance().hasShoes()) {
		ent[sizeEnts - 1]->setSpeed(3);
	}
	else ent[sizeEnts - 1]->setSpeed(2);

	// entrar en portal
	if (Game::instance().getSpecialKey(GLUT_KEY_UP) && map->isOnPortal(posPlayer, glm::ivec2(32, 32))) {
		enterPortal = true;
	}

	// acabar partida
	if (Gui::instance().has6Friends()) {
		for (int i = 0; i < ent.size(); i++) {
			if (ent[i]->getTypeEntity() == 10)
				ent[i]->open();
		}
		if (abs(posPlayer.x - (posEnd.x * 16)) < 32) {
			if (abs(posPlayer.y - (posEnd.y * 16)) < 32) {
				if (Game::instance().getSpecialKey(GLUT_KEY_UP))
					win = true;
			}
		}
	}
	

	//abrir puerta
	//glm::ivec2 posPlayer = ent[sizeEnts - 1]->getPos();
	glm::ivec2 posDoor = ent[0]->getPos();

	if (abs(posPlayer.x - posDoor.x) < 32 && Gui::instance().hasKey()) {
		if (abs(posPlayer.y - posDoor.y) < 32) {
			ent[0]->open();
			Gui::instance().setKey(false);
		}
	}

	//coger objeto
	for (int i = 0; i < ent.size(); i++) {
		glm::ivec2 posEnt= ent[i]->getPos();
		//es llave y no tiene llave encima
		if (ent[i]->getTypeEntity() == 2 && !Gui::instance().hasKey() && !ent[i]->ObjectCatch()) {
			if (((posEnt.x - posPlayer.x) < 8 && (posEnt.x - posPlayer.x) >= 0) || (((posPlayer.x - posEnt.x) < 12 && (posPlayer.x - posEnt.x) >= 0))) {
				if (posEnt.y - posPlayer.y < 16 && posEnt.y - posPlayer.y >0) {
					Gui::instance().setKey(true);
					ent[i]->setCatch();
					Game::instance().addTotalExp(200);
					Game::instance().addExp(200);
				}
			}
		}
		//coger helmet 
		if (ent[i]->getTypeEntity() == 10 && !Gui::instance().hasHelmet() && !ent[i]->ObjectCatch()) {
			if (((posEnt.x - posPlayer.x) < 8 && (posEnt.x - posPlayer.x) >= 0) || (((posPlayer.x - posEnt.x) < 12 && (posPlayer.x - posEnt.x) >= 0))) {
				if (posEnt.y - posPlayer.y < 16 && posEnt.y - posPlayer.y >0) {
					Gui::instance().setHelmet(true);
					ent[i]->setCatch();
					Game::instance().addTotalExp(1000);
					Game::instance().addExp(1000);
				}
			}
		}
		//coger libro gris 
		if (ent[i]->getTypeEntity() == 11 && !Gui::instance().hasGreyBook() && !ent[i]->ObjectCatch()) {
			if (((posEnt.x - posPlayer.x) < 8 && (posEnt.x - posPlayer.x) >= 0) || (((posPlayer.x - posEnt.x) < 12 && (posPlayer.x - posEnt.x) >= 0))) {
				if (posEnt.y - posPlayer.y < 16 && posEnt.y - posPlayer.y >0) {
					Gui::instance().setGreyBook(true);
					ent[i]->setCatch();
					Game::instance().addTotalExp(1000);
					Game::instance().addExp(1000);
				}
			}
		}
		if (ent[i]->getTypeEntity() == 12 && !Gui::instance().hasGreenBook() && !ent[i]->ObjectCatch()) {
			if (((posEnt.x - posPlayer.x) < 8 && (posEnt.x - posPlayer.x) >= 0) || (((posPlayer.x - posEnt.x) < 12 && (posPlayer.x - posEnt.x) >= 0))) {
				if (posEnt.y - posPlayer.y < 16 && posEnt.y - posPlayer.y >0) {
					Gui::instance().setGreenBook(true);
					ent[i]->setCatch();
					Game::instance().addTotalExp(1000);
					Game::instance().addExp(1000);
				}
			}
		}
		//coge chus
		if (ent[i]->getTypeEntity() == 13 && !Gui::instance().hasChus() && !ent[i]->ObjectCatch()) {
			if (((posEnt.x - posPlayer.x) < 8 && (posEnt.x - posPlayer.x) >= 0) || (((posPlayer.x - posEnt.x) < 12 && (posPlayer.x - posEnt.x) >= 0))) {
				if (posEnt.y - posPlayer.y < 16 && posEnt.y - posPlayer.y >0) {
					Gui::instance().setChus(true);
					ent[i]->setCatch();
					Game::instance().addTotalExp(1000);
					Game::instance().addExp(1000);
				}
			}
		}
		//coger shoes
		if (ent[i]->getTypeEntity() == 14 && !Gui::instance().hasShoes() && !ent[i]->ObjectCatch()) {
			if (((posEnt.x - posPlayer.x) < 8 && (posEnt.x - posPlayer.x) >= 0) || (((posPlayer.x - posEnt.x) < 12 && (posPlayer.x - posEnt.x) >= 0))) {
				if (posEnt.y - posPlayer.y < 16 && posEnt.y - posPlayer.y >0) {
					Gui::instance().setShoes(true);
					ent[i]->setCatch();
					Game::instance().addTotalExp(1000);
					Game::instance().addExp(1000);
				}
			}
		}
		//coger dinero 
		if (ent[i]->getTypeEntity() == 15 && !ent[i]->ObjectCatch()) {
			if (((posEnt.x - posPlayer.x) < 8 && (posEnt.x - posPlayer.x) >= 0) || (((posPlayer.x - posEnt.x) < 12 && (posPlayer.x - posEnt.x) >= 0))) {
				if (posEnt.y - posPlayer.y < 16 && posEnt.y - posPlayer.y >0) {
					ent[i]->setCatch();
					Game::instance().addTotalExp(1000);
					Game::instance().addExp(1000);
				}
			}
		}
		//abre la puerta y coge friend
		else if (ent[i]->getTypeEntity() == 4 && ent[i]->getState() == 1) {
			if (((posPlayer.x - posEnt.x) < 48 && (posPlayer.x - posEnt.x) >= 16)) {
				if (posPlayer.y - posEnt.y <= 32 && posPlayer.y - posEnt.y >= 0) {
			/*if (abs(posPlayer.x - posEnt.x) < 8) {
				if(abs(posPlayer.y - posEnt.y) < 8) {*/
					Gui::instance().setFriends(1);
					ent[0]->setState(2);
					Game::instance().addTotalExp(2000);
					Game::instance().addExp(2000);
				}
			}
		}
	}

	// cae falling rock
	for (int i = 0; i < enemy.size(); ++i) {
		if (enemy[i]->getTypeEnemy() == 3) {
			glm::ivec2 posRock = enemy[i]->getPos();
			if (posPlayer.x == posRock.x) {
				if(posPlayer.y > posRock.y && posPlayer.y - posRock.y < 64)
					enemy[i]->trigger();
			}
		}
	}

	//ser golpeado por enemigo -> habria que personalizar las hitbox para cada enemigo.
	if (!Game::instance().getGodMode() && secHit == 30) {
		for (int i = 0; i < enemy.size(); i++) {
			glm::ivec2 posEnemy = enemy[i]->getPos();
			if (enemy[i]->getTypeEnemy() == 2 && !Gui::instance().hasChus()) {
				if (((posEnemy.x - posPlayer.x) < 8 && (posEnemy.x - posPlayer.x) >= 0) || (((posPlayer.x - posEnemy.x) < 12 && (posPlayer.x - posEnemy.x) >= 0))) {
					if (posPlayer.y-10 == posEnemy.y) {
						secHit = 0;
						Game::instance().setLives(-1);
						if (Game::instance().getLives() <= 0) {
							gameover = true;
						}
					}
				}
			}
			if (enemy[i]->getTypeEnemy() == 3 && !Gui::instance().hasHelmet()) {
				if (((posEnemy.x - posPlayer.x) < 8 && (posEnemy.x - posPlayer.x) >= 0) || (((posPlayer.x - posEnemy.x) < 12 && (posPlayer.x - posEnemy.x) >= 0))) {
					if (posPlayer.y - 10 == posEnemy.y) {
						secHit = 0;
						Game::instance().setLives(-1);
						if (Game::instance().getLives() <= 0) {
							gameover = true;
						}
					}
				}
			}
			else if (enemy[i]->getTypeEnemy() == 10 && enemy[i]->getAnimation() == 3) {
				if (((posEnemy.x - posPlayer.x) < 8 && (posEnemy.x - posPlayer.x) >= 0) || (((posPlayer.x - posEnemy.x) < 12 && (posPlayer.x - posEnemy.x) >= 0))) {
					if (abs(posPlayer.y - posEnemy.y) < 16) {
						secHit = 0;
						Game::instance().setLives(-1);
						if (Game::instance().getLives() <= 0) {
							gameover = true;
						}
					}
				}
			}
			else if (enemy[i]->getTypeEnemy() == 0) {
				if (ent[sizeEnts - 1]->LeftMove()) {
					if ((posEnemy.x + 16 == posPlayer.x) || (posEnemy.x + 16 == posPlayer.x + 2) || (posEnemy.x == posPlayer.x + 8)) {
						if ((posEnemy.y - posPlayer.y) < 16 && 0 <= (posEnemy.y - posPlayer.y)) {
							if (enemy[i]->getState() == EnemyManager::ALIVE) {
								if (Gui::instance().hasGreenBook()) {
									int lives_enemy = enemy[i]->hit();
									secPunch = 0;
									if (lives_enemy <= 0) enemy[i]->dies();//hay que añadir algo para que el golpe solo dure pocos frames.
									Game::instance().addTotalExp(50);
									Game::instance().addExp(50);
								}
								else {
									secHit = 0;
									Game::instance().setLives(-1);
									if (Game::instance().getLives() <= 0) {
										gameover = true;
									}
								}
							}
						}
					}
				}
				else {
					if ((posEnemy.x + 16 == posPlayer.x) || (posEnemy.x == posPlayer.x + 10) || (posEnemy.x + 2 == posPlayer.x + 10)) {
						if ((posEnemy.y - posPlayer.y) < 16 && 0 <= (posEnemy.y - posPlayer.y)) {
							if (enemy[i]->getState() == EnemyManager::ALIVE) {
								if (Gui::instance().hasGreenBook()) {
									int lives_enemy = enemy[i]->hit();
									secPunch = 0;
									if (lives_enemy <= 0) enemy[i]->dies();//hay que añadir algo para que el golpe solo dure pocos frames.
									Game::instance().addTotalExp(50);
									Game::instance().addExp(50);
								}
								else {
									secHit = 0;
									Game::instance().setLives(-1);
									if (Game::instance().getLives() <= 0) {
										gameover = true;
									}
								}
							}
						}
					}
				}
			}
			else if (enemy[i]->getTypeEnemy() == 4) {
				if (ent[sizeEnts - 1]->LeftMove()) {
					if ((posEnemy.x + 16 == posPlayer.x) || (posEnemy.x + 16 == posPlayer.x + 2) || (posEnemy.x == posPlayer.x + 8)) {
						if ((posPlayer.y - posEnemy.y) < 16 && 0 <= (posPlayer.y - posEnemy.y)) {
							if ( enemy[i]->getAnimation() == 3 || enemy[i]->getAnimation() == 4) {
								secHit = 0;
								Game::instance().setLives(-1);
								if (Game::instance().getLives() <= 0) {
									gameover = true;
								}
							}
						}
					}
				}
				else {
					if ((posEnemy.x + 16 == posPlayer.x) || (posEnemy.x == posPlayer.x + 10) || (posEnemy.x + 2 == posPlayer.x + 10)) {
						if ((posPlayer.y - posEnemy.y) < 16 && 0 <= (posPlayer.y - posEnemy.y)) {
							if (enemy[i]->getAnimation() == 3 || enemy[i]->getAnimation() == 4) {
								secHit = 0;
								Game::instance().setLives(-1);
								if (Game::instance().getLives() <= 0) {
									gameover = true;
								}
							}
						}
					}
				}
			}
			else if (enemy[i]->getTypeEnemy() == 1) {
				if (ent[sizeEnts - 1]->LeftMove()) {
					if ((posEnemy.x + 26 == posPlayer.x) || (posEnemy.x + 26 == posPlayer.x + 2) || (posEnemy.x-6 == posPlayer.x)) {
						if ((posEnemy.y - posPlayer.y) < 32 && 0 <= (posEnemy.y - posPlayer.y)) {
							if (enemy[i]->getState() == EnemyManager::ALIVE) {
								if (Gui::instance().hasGreyBook()) {
									int lives_enemy = enemy[i]->hit();
									secPunch = 0;
									if (lives_enemy <= 0) enemy[i]->dies();//hay que añadir algo para que el golpe solo dure pocos frames.
									Game::instance().addTotalExp(100);
									Game::instance().addExp(100);
								}
								else{
									secHit = 0;
									Game::instance().setLives(-1);
									if (Game::instance().getLives() <= 0) {
										gameover = true;
									}
								}
							}
						}
					}
				}
				else {
					if ((posEnemy.x + 24 == posPlayer.x) || (posEnemy.x == posPlayer.x + 8) || (posEnemy.x + 2 == posPlayer.x + 8)) {
						if ((posEnemy.y - posPlayer.y) < 32 && 0 <= (posEnemy.y - posPlayer.y)) {
							if (enemy[i]->getState() == EnemyManager::ALIVE) {
								if (Gui::instance().hasGreyBook()) {
									int lives_enemy = enemy[i]->hit();
									secPunch = 0;
									if (lives_enemy <= 0) enemy[i]->dies();//hay que añadir algo para que el golpe solo dure pocos frames.
									Game::instance().addTotalExp(100);
									Game::instance().addExp(100);
								}
								else {
									secHit = 0;
									Game::instance().setLives(-1);
									if (Game::instance().getLives() <= 0) {
										gameover = true;
									}
								}
							}
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
		}
	}
	if (secPunch != 30) secPunch++;
	

}

SceneManager* Scene::changeScene() {
	if (gameover) {
		Gui::instance().reset();
		Game::instance().reset();
		SceneManager* scene = new GameOverScene();
		scene->init();
		Game::instance().setGameOverMusic();
		return scene;
	}
	else if (nextlevel) {
		guardarEstado();
		SceneManager* scene = new Scene("levels/lv0" + next);
		scene->init();
		return scene;
	}
	else if (prevlevel) {
		guardarEstado();
		SceneManager* scene = new Scene("levels/lv0" + prev);
		scene->init();
		return scene;
	}
	else if (enterPortal) {
		guardarEstado();
		SceneManager* scene = new Scene("levels/lv0" + portalLevel);
		scene->init();
		return scene;
	}
	else if (win) {
		Gui::instance().reset();
		Game::instance().reset();
		SceneManager* scene = new EndScene();
		scene->init();
		Game::instance().setMenuMusic();
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
	int loc;

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
	if(charge_obj){
		Game::instance().charged_scene(num_scene);
		for (int i = 0; i < sizeEnts; ++i) {
			getline(fin, line);
			sstream.str(line);
			sstream >> entity >> pos.x >> pos.y;
			if (entity == "PLAYER") {
				ent.push_back(new Player());
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
				posIni.x = pos.x * map->getTileSize();
				posIni.y = pos.y * map->getTileSize();
				ent[i]->setTileMap(map);
			}
			else if (entity == "PORTAL") {
				sstream >> portalLevel;
				ent.push_back(new Portal(portalLevel));
			}
			else if (entity == "KEY") {
				ent.push_back(new Key());
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
				ent[i]->setTileMap(map);
			}
			else if (entity == "DOOR") {
				ent.push_back(new Door());
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
				ent[i]->setTileMap(map);
				posDoor = glm::ivec2(pos.x, pos.y);
			}
			else if (entity == "ENDDOOR") {
				ent.push_back(new EndDoor());
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
				ent[i]->setTileMap(map);
				posEnd = glm::ivec2(pos.x, pos.y);
			}
			else if (entity == "HELMET") {
				ent.push_back(new helmet());
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
				ent[i]->setTileMap(map);
			}
			else if (entity == "GREYBOOK") {
				ent.push_back(new greyBook());
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
				ent[i]->setTileMap(map);
			}
			else if (entity == "GREENBOOK") {
				ent.push_back(new greenBook());
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
				ent[i]->setTileMap(map);
			}
			else if (entity == "CHUS") {
				ent.push_back(new chus());
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
				ent[i]->setTileMap(map);
			}
			else if (entity == "SHOES") {
				ent.push_back(new shoes());
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
				ent[i]->setTileMap(map);
			}
			else if (entity == "MONEY") {
				ent.push_back(new moneyBag());
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
				ent[i]->setTileMap(map);
			}
		}
	}
	else{
		for (int i = 0; i < sizeEnts; ++i) {
			getline(fin, line);
			sstream.str(line);
			sstream >> entity >> pos.x >> pos.y;
			if (entity == "PLAYER") {
				ent.push_back(new Player());
				glm::ivec3 s = EntState::instance().getState(num_scene,i);
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(s.x , s.y ));
				ent[i]->setTileMap(map);
				ent[i]->setState(s.z);
			}
			else if (entity == "ENDDOOR") {
				ent.push_back(new EndDoor());
				glm::ivec3 s = EntState::instance().getState(num_scene, i);
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(s.x, s.y));
				ent[i]->setTileMap(map);
				ent[i]->setState(s.z);
			}
			else if (entity == "PORTAL") {
				sstream >> portalLevel;
				ent.push_back(new Portal(portalLevel));
			}
			else if (entity == "KEY") {
				ent.push_back(new Key());
				glm::ivec3 s = EntState::instance().getState(num_scene, i);
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(s.x, s.y));
				ent[i]->setTileMap(map);
				ent[i]->setState(s.z);
				if (s.z == 2) ent[i]->setCatch();
			}
			else if (entity == "HELMET") {
				ent.push_back(new helmet());
				glm::ivec3 s = EntState::instance().getState(num_scene, i);
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(s.x, s.y));
				ent[i]->setTileMap(map);
				ent[i]->setState(s.z);
				if (s.z == 2) ent[i]->setCatch();
			}
			else if (entity == "GREYBOOK") {
				ent.push_back(new greyBook());
				glm::ivec3 s = EntState::instance().getState(num_scene, i);
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(s.x, s.y));
				ent[i]->setTileMap(map);
				ent[i]->setState(s.z);
				if (s.z == 2) ent[i]->setCatch();
			}
			else if (entity == "GREENBOOK") {
				ent.push_back(new greenBook());
				glm::ivec3 s = EntState::instance().getState(num_scene, i);
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(s.x, s.y));
				ent[i]->setTileMap(map);
				ent[i]->setState(s.z);
				if (s.z == 2) ent[i]->setCatch();
			}
			else if (entity == "CHUS") {
				ent.push_back(new chus());
				glm::ivec3 s = EntState::instance().getState(num_scene, i);
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(s.x, s.y));
				ent[i]->setTileMap(map);
				ent[i]->setState(s.z);
				if (s.z == 2) ent[i]->setCatch();
			}
			else if (entity == "SHOES") {
				ent.push_back(new shoes());
				glm::ivec3 s = EntState::instance().getState(num_scene, i);
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(s.x, s.y));
				ent[i]->setTileMap(map);
				ent[i]->setState(s.z);
				if (s.z == 2) ent[i]->setCatch();
			}
			else if (entity == "MONEY") {
				ent.push_back(new moneyBag());
				glm::ivec3 s = EntState::instance().getState(num_scene, i);
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(s.x, s.y));
				ent[i]->setTileMap(map);
				ent[i]->setState(s.z);
				if (s.z == 2) ent[i]->setCatch();
			}
			else if (entity == "DOOR") {
				ent.push_back(new Door());
				glm::ivec3 s = EntState::instance().getState(num_scene, i);
				ent[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				ent[i]->setPosition(glm::vec2(s.x, s.y));
				ent[i]->setTileMap(map);
				ent[i]->setState(s.z);
			}

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
			else if (entity == "DROP") {
				enemy[i] = new Drop();
				enemy[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				enemy[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
				enemy[i]->setTileMap(map);
			}
			else if (entity == "ROCK") {
				enemy[i] = new FallingRock();
				enemy[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				enemy[i]->setPosition(glm::vec2(pos.x * map->getTileSize(), pos.y * map->getTileSize()));
				enemy[i]->setTileMap(map);
			}
			else if (entity == "WATER") {
				sstream >> loc;
				enemy[i] = new Water(loc);
				enemy[i]->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				enemy[i]->setPosition(glm::vec2(pos.x* map->getTileSize(), pos.y* map->getTileSize()));
				enemy[i]->setTileMap(map);
			}
		}
}

void Scene::guardarEstado() {
	EntState::instance().clear(num_scene);
	for (int i = 0; i < ent.size(); i++) {
		glm::ivec2 pos = ent[i]->getPos();
		bool p = false;;
		if (ent[i]->getTypeEntity() == 1) {
			if (ent[i]->IsClimbing()) {
				pos.x = posIni.x;
				pos.y = posIni.y;
			}
			p = true;
		}
		EntState::instance().setState(num_scene, pos.x, pos.y, ent[i]->getState(), nextlevel, prevlevel, p);
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



