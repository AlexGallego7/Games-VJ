#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "GameOverSCene.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

int GameOverScene::getEscena() {
	return 3;
}

void GameOverScene::init()
{
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(68.f, 7.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	initShaders();
	texQuad = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	// Load textures
	tex.loadFromFile("images/gameover.png", TEXTURE_PIXEL_FORMAT_RGBA);

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void GameOverScene::update(int deltaTime)
{
	currentTime += deltaTime;

}

SceneManager* GameOverScene::changeScene() {

	if (Game::instance().getKey(' ')) {
		SceneManager* scene = new Menu();
		scene->init();
		return scene;
	}

	return this;

}


void GameOverScene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(380.f, 400.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(4.f, 4.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad->render(tex);


}

void GameOverScene::initShaders()
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



