#pragma once

class SceneManager {

public:

	virtual void init();
	virtual void update(int deltaTime);
	virtual void render();

};