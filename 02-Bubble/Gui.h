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
	void setHelmet(bool h);
	void setFriends(int num);
	bool hasKey();

	bool hasHelmet();


private:
	void initShaders();

private:
	TexturedQuad* texQuad[20];
	Texture tex[5];
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int scene, int_exp, old_exp, friends;
	bool key, show_key, helmet;

};


#endif // _SCENE_INCLUDE

void setKey(bool key);
