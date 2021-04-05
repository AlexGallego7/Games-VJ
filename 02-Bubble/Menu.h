#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Game.h"
#include "TexturedQuad.h"
#include "InstruccionsScene.h"

class Menu : public SceneManager
{

public:
	Menu();
	~Menu();

	void init();
	void update(int deltaTime);
	void render();
	int getEscena();
	SceneManager* changeScene();

	void guardarEstado();

private:
	void initShaders();

private:
	TexturedQuad* texQuad[10];
	Texture tex[2];
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE

