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
	void setChus(bool h);
	void setShoes(bool h);
	void setGreenBook(bool h);
	void setGreyBook(bool h);
	void setFriends(int num);
	bool hasKey();
	bool has6Friends();

	bool hasHelmet();

	bool hasGreyBook();

	bool hasGreenBook();

	bool hasChus();

	bool hasShoes();


private:
	void initShaders();

private:
	TexturedQuad* texQuad[21];
	Texture tex[6];
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int scene, int_exp, old_exp, friends, numObj;
	bool key, show_key, helmet, greyBook, greenBook, chus, shoes, end;

};


#endif // _SCENE_INCLUDE

void setKey(bool key);
