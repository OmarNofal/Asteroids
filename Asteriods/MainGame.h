

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
	int currentLives = 5;
	int maxLives = 5;

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
	void CreateRandomAsteroids(Game* g, int num = 4);
	void HandleShipCollision(Game* g);
	void CheckAsteroidCollision(size_t index);
	void HandleAsteroidCollision(size_t index);
	void DrawHearts(Game* g);
	void ResetShip(Game* g);
};


#endif