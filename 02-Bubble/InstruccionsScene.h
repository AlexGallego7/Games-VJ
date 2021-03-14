#ifndef _INSTRUCCIONSSCENE_INCLUDE
#define _INSTRUCCIONSSCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "SceneManager.h"
#include "Texture.h"
#include "TexturedQuad.h"
#include "Menu.h"

class InstruccionsScene : public SceneManager
{

public:
	InstruccionsScene();
	~InstruccionsScene();

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