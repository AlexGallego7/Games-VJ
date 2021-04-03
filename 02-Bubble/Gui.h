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

	void setKey(bool key);

private:
	void initShaders();

private:
	TexturedQuad* texQuad[14];
	Texture tex[4];
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int scene, int_exp, old_exp;
	bool key, show_key;

};


#endif // _SCENE_INCLUDE

void setKey(bool key);
