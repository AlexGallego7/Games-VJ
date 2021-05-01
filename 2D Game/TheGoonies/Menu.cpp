#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

int Menu::getEscena() {
	return 0;
}

void Menu::init()
{
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)) };
	glm::vec2 geomChars[2] = { glm::vec2(0.f, 0.f), glm::vec2(20.f, 20.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	initShaders();
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	texCoords[0] = glm::vec2(0.53f, 0.5f); texCoords[1] = glm::vec2(0.565f, 1.f); // P
	texQuad[1] = TexturedQuad::createTexturedQuad(geomChars, texCoords, texProgram);

	texCoords[0] = glm::vec2(0.4f, 0.5f); texCoords[1] = glm::vec2(0.435f, 1.f); // L 
	texQuad[2] = TexturedQuad::createTexturedQuad(geomChars, texCoords, texProgram);

	texCoords[0] = glm::vec2(0.034f, 0.5f); texCoords[1] = glm::vec2(0.068f, 1.f); // A 
	texQuad[3] = TexturedQuad::createTexturedQuad(geomChars, texCoords, texProgram);

	texCoords[0] = glm::vec2(0.83f, 0.5f); texCoords[1] = glm::vec2(0.863f, 1.f); // Y
	texQuad[4] = TexturedQuad::createTexturedQuad(geomChars, texCoords, texProgram);

	texCoords[0] = glm::vec2(0.63f, 0.5f); texCoords[1] = glm::vec2(0.66f, 1.f); // S
	texQuad[5] = TexturedQuad::createTexturedQuad(geomChars, texCoords, texProgram);

	texCoords[0] = glm::vec2(0.66f, 0.5f); texCoords[1] = glm::vec2(0.69f, 1.f); // T
	texQuad[6] = TexturedQuad::createTexturedQuad(geomChars, texCoords, texProgram);

	texCoords[0] = glm::vec2(0.034f, 0.5f); texCoords[1] = glm::vec2(0.068f, 1.f); // A 
	texQuad[7] = TexturedQuad::createTexturedQuad(geomChars, texCoords, texProgram);

	texCoords[0] = glm::vec2(0.6f, 0.5f); texCoords[1] = glm::vec2(0.63f, 1.f); // R 
	texQuad[8] = TexturedQuad::createTexturedQuad(geomChars, texCoords, texProgram);

	texCoords[0] = glm::vec2(0.66f, 0.5f); texCoords[1] = glm::vec2(0.69f, 1.f); // T
	texQuad[9] = TexturedQuad::createTexturedQuad(geomChars, texCoords, texProgram);

	// Load textures
	tex[0].loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tex[1].loadFromFile("images/font.png", TEXTURE_PIXEL_FORMAT_RGBA);


	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Menu::update(int deltaTime)
{
	currentTime += deltaTime;	
}

SceneManager* Menu::changeScene() {

	if (Game::instance().getKey(' ')) {
		SceneManager* scene = new Scene("levels/lv01");
		scene->init();
		Game::instance().setSceneMusic();
		return scene;
	}
	return this;

}

void Menu::guardarEstado() {}

void Menu::render()
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
	texQuad[0]->render(tex[0]);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(245.f, 270.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[1]->render(tex[1]);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(265.f, 270.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[2]->render(tex[1]);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(280.f, 270.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[3]->render(tex[1]);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(300.f, 270.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[4]->render(tex[1]);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(340.f, 270.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[5]->render(tex[1]);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(360.f, 270.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[6]->render(tex[1]);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(380.f, 270.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[7]->render(tex[1]);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(400.f, 270.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[8]->render(tex[1]);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(415.f, 270.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[9]->render(tex[1]);

}


void Menu::initShaders()
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



