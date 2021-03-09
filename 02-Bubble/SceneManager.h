#pragma once

class SceneManager {

public:

	virtual void init() = 0;
	virtual void update(int deltaTime) = 0;
	virtual void render() = 0;
	virtual SceneManager* changeScene() = 0;

};