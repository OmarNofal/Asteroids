

#ifndef MAIN_GAME
#define MAIN_GAME

#include "Globals.h"
#include "GameState.h"
#include "Ship.h"
#include "MatrixOps.h"
#include "Bullet.h"
#include "Asteriod.h"


class MainGame : public GameState {

private: // members
	Ship ship;	
	std::vector<Bullet> bullets;
	std::vector<Asteroid> asteroids;

	olc::Sprite* hearts = nullptr;
	
	int maxLives = 3;
	int currentLives = maxLives;

	bool cooldown = true;
	double cooldownTime = 0.0f; // time since cooldown

	double temperature = 0.0f; // 0-1
	bool overheated = false;

	double score = 0;

	olc::Sprite* targetSprite = nullptr;
	bool heatSeekerEnabled = false;
	double heatSeekerMsgTime = 0.0f;
	Asteroid* targetedAsteroid = nullptr; // asteroid marked by heatseeker missile
	double targetingAngle = 3.14159265358979323846 / 4.0f;
	double targetingRadius = 250.0f;

	double gameOverTime = 0.0f;

public:
	MainGame();

	void Init(Game* g);
	void Cleanup(Game* g);

	void HandleEvents(Game* g, float elapsedTime);
	void Update(Game* g, float elapsedTime);
	void Draw(Game* g, float elapsedTime);

	void Pause();
	void Resume();

private: // methods
	void CheckAsteroidsCollision(Game* g);
	void DrawShip(Game* g, float elapsedTime);
	void DrawBullets(Game* g, float elpasedTime);
	void DrawAsteriods(Game* g, float elapsedTime);
	void CreateRandomAsteroids(Game* g, int num = 6);
	void HandleShipCollision(Game* g);
	void CheckAsteroidCollision(size_t index);
	void HandleAsteroidCollision(size_t index);
	void DrawHearts(Game* g);
	void ResetShip(Game* g);
	void DrawTemperature(Game* g, float elaspedTime);
	void DrawScore(Game* g);
	void DrawHeatseekerTarget(Game* g);
	void ToggleHeatSeeker(Game* g);
	void DrawHeatseekerMessage(Game* g, float elapsedTime);
	void CheckGameOver(Game* g, float elapsedTime);
	void SaveNewScore();
};


#endif