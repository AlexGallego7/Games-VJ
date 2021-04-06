#ifndef _WINSCENE_INCLUDE
#define _WINSCENE_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "SceneManager.h"
#include "Texture.h"
#include "TexturedQuad.h"
#include "Menu.h"

class WinScene : public SceneManager {

public:

	WinScene();
	~WinScene();

	void init();
	void update(int deltaTime);
	void render();
	SceneManager* changeScene();
	int getEscena();

	bool loadEscena(const string& levelFile);

	void guardarEstado();
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
