
#include "Game.h"

#ifndef GAME_STATE
#define GAME_STATE

class Game;

class GameState {

public:

	virtual void Init(Game* g) = 0;
	virtual void Cleanup(Game* g) = 0;

	virtual void HandleEvents(Game* g, float elapsedTime) = 0;
	virtual void Update(Game* g, float elapsedTime) = 0;
	virtual void Draw(Game* g, float elapsedTime) = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

};



#endif