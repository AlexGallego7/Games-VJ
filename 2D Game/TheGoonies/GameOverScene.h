#ifndef _GAMEOVERSCENE_INCLUDE
#define _GAMEOVERSCENE_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "SceneManager.h"
#include "Texture.h"
#include "TexturedQuad.h"
#include "Menu.h"

class GameOverScene : public SceneManager {

public:

	GameOverScene();
	~GameOverScene();

	void guardarEstado();

	void init();
	void update(int deltaTime);
	void render();
	SceneManager* changeScene();
	int getEscena();

private:
	
	void initShaders();

private:
	TexturedQuad* texQuad;
	Texture tex;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
};

#endif // _SCENE_INCLUDE
