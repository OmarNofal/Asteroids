#ifndef GAME_STATE
#define GAME_STATE


class GameState {

public:

	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void HandleEvents(Game) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

};



#endif