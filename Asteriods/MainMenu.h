#ifndef MAIN_MENU
#define MAIN_MENU

#include "GameState.h"
#include "Game.h"
#include "MainGame.h"
#include "Asteriod.h"

#include <string>
#include <fstream>
#include <vector>

enum class Options {
	START, EXIT
};

class MainMenu : public GameState {

private:
	olc::Sprite* arrowSprite;

	std::vector<Asteroid> asteroids;

	long long highScore = 0L;
	
	Point startPos;
	Point exitPos;
	Options selected = Options::START;


public:
	MainMenu();

	void Init(Game* g);
	void Cleanup(Game* g);

	void HandleEvents(Game* g, float elapsedTime);
	void Update(Game* g, float elapsedTime);
	void Draw(Game* g, float elapsedTime);

	void Pause();
	void Resume();

private:
	void LoadHighScore();
	void DrawTitle(Game* g);
	void DrawHighScore(Game* g);
	void DrawOptionsMenu(Game* g);
	void HandleEnterCommand(Game* g);
	void GenerateAsteroids(Game* g);
	void DrawAsteroids(Game* g);
};





#endif // !MAIN_MENU