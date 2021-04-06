#pragma once
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
class EntState
{
public:
	EntState() {}

	static EntState& instance() {
		static EntState g;
		return g;
	}



	void setState(int esc, int posx, int posy, int numAnim, bool nextLevel, bool prevLevel, bool player);

	glm::ivec3 getState(int num_scene, int num);

	void resize(int num);

	void clear(int esc);



private:
	vector<vector<glm::ivec3>> stateEnts;
};

