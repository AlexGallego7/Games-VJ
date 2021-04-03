#ifndef _GUI_INCLUDE
#define _GUI_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Game.h"
#include "TexturedQuad.h"

class Gui 
{

public:
	Gui() {}

	static Gui& instance() {
		static Gui g;
		return g;
	}

	void init();
	void update(int deltaTime);
	void render();

	void setScene(string scene);

private:
	void initShaders();

private:
	TexturedQuad* texQuad[11];
	Texture tex[2];
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int scene;

};


#endif // _SCENE_INCLUDE

