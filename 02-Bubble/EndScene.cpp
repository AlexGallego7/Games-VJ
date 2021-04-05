#include "EndScene.h"
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
}

int EndScene::getEscena() {
	return 5;
}

void EndScene::init()
{
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	initShaders();
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	texQuad[1] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	// Load textures
	tex[0].loadFromFile("images/end.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex[1].loadFromFile("images/creditos.png", TEXTURE_PIXEL_FORMAT_RGBA);

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	esc = 1;
}

void EndScene::update(int deltaTime)
{
	currentTime += deltaTime;

}

SceneManager* EndScene::changeScene() {

	
	if (currentTime > 6000) {
		SceneManager* scene = new Menu();
		scene->init();
		return scene;
	}
	else if (currentTime > 3000) {
		esc = 2;
	}
	return this;

}

void EndScene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	if(esc==1) texQuad[0]->render(tex[0]);
	else texQuad[1]->render(tex[1]);



}
void EndScene::guardarEstado() {}

void EndScene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}
