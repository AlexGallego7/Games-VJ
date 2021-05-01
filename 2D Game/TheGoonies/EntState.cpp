#include "EntState.h"

void EntState::setState(int esc, int posx, int posy, int numAnim, bool nextLevel, bool prevLevel, bool p) {
	glm::ivec3 s;
	if (nextLevel && p) {
		s.x = posx - 16;
	}
	else s.x = posx;
	if (prevLevel && !nextLevel && p) {
		s.x = posx + 16;
	}
	else if(!prevLevel && !nextLevel) s.x = posx;
	s.y = posy;
	s.z = numAnim;
	stateEnts[esc-1].push_back(s);
}

glm::ivec3 EntState::getState(int num_scene, int num) {
	return stateEnts[num_scene-1][num];
}

void EntState::resize(int num) {
	stateEnts.resize(num);
}

void EntState::clear(int esc) {
	stateEnts[esc-1].clear();
}