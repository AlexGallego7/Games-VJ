#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Game.h"
#include "TexturedQuad.h"

class Menu : public SceneManager
{

public:
	Menu();
	~Menu();

	void init();
	void update(int deltaTime);
	void render();
	SceneManager* changeScene();

private:
	void initShaders();

private:
	bool begin;
	TexturedQuad* texQuad;
	Texture tex;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE

