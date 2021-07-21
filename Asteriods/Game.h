
#ifndef GAME
#define GAME

#include "olcPixelGameEngine.h"
#include <vector>
#include "GameState.h"

class Game : public olc::PixelGameEngine {

public:
	
	Game();

	std::vector<GameState*> states; // holds states of the whole game

	void ChangeState(GameState*);
	void PushState(GameState*);
	void PopState();

	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float elapsedTime);
	virtual bool OnUserDestroy();

	virtual bool Draw(int32_t x, int32_t y, olc::Pixel p = olc::WHITE);

	void WrapCoordinates(float ix, float iy, float& ox, float& oy);
};

class GameState;

#endif