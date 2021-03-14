#pragma once

class SceneManager {

public:

	virtual void init() = 0;
	virtual void update(int deltaTime) = 0;
	virtual void render() = 0;
	virtual SceneManager* changeScene() = 0;
	virtual int getEscena() = 0;
	/*
	menu -> 0
	instrucciones -> 1
	Scene (jugar) -> 2
	gameOver -> 3
	*/

};