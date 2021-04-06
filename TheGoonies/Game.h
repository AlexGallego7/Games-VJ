#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "SceneManager.h"
#include "Scene.h"
#include "Menu.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

	bool getGodMode();

	bool getPunch();

	void addTotalExp(int exp);

	void addExp(int exp);

	glm::ivec2 getExp();

	void resetExp();

	void resetLives();

	int getLives();

	void setLives(int lives);

	bool isCharged(int pos);

	void charged_scene(int pos);

	void setNumEsc(int num);

	void setSceneMusic();

	void setMenuMusic();

	void setGameOverMusic();

	int getNumEsc
		void setHit(bool h);
	bool isHit();
	();
	
	void setEnd();

	void reset();

private:
	bool bPlay, godmode, punch;                       // Continue to play game?
	SceneManager *scene;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time
	int totalExp, exp, lives, num_esc;
	vector<bool> charged_scenes;
	
};



#endif // _GAME_INCLUDE


