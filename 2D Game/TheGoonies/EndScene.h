#ifndef _EndScene_INCLUDE
#define _EndScene_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "SceneManager.h"
#include "Texture.h"
#include "TexturedQuad.h"
#include "Menu.h"

class EndScene : public SceneManager
{

public:
	EndScene();
	~EndScene();

	void init();
	void update(int deltaTime);
	void render();
	void guardarEstado();
	SceneManager* changeScene();
	int getEscena();

private:
	void initShaders();

private:
	TexturedQuad* texQuad[2];
	Texture tex[2];
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int esc;

};


#endif // _SCENE_INCLUDE