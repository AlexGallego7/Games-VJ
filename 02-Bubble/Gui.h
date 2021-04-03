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

	void setScene(int scene);

private:
	void initShaders();

private:
	TexturedQuad* texQuad[13];
	Texture tex[3];
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int scene, int_exp, old_exp;

};


#endif // _SCENE_INCLUDE

