#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#define _USE_MATH_DEFINES
#include <cmath>
#define OLC_PGE_APPLICATION

#include "Globals.h"
#include "olcPixelGameEngine.h"
#include "Game.h"
#include "MainGame.h"
#include "GameState.h"


Game::Game() {
	sAppName = "Asteroids";
	MainGame* m = new MainGame();
	PushState(m);
	m->Init(this);
}

bool Game::OnUserCreate() {
	// Create main menu;

	return true;
}

bool Game::OnUserUpdate(float elapsedTime) {
	GameState* s = states.back();
	s->HandleEvents(this, elapsedTime);
	s->Update(this, elapsedTime);
	s->Draw(this, elapsedTime);
	return true;
}

bool Game::OnUserDestroy() {
	return true;
}

void Game::PushState(GameState* s) {
	if (!states.empty()) {
		states.back()->Pause();
	}
	states.push_back(s);
	states.back()->Init(this);
}

void Game::PopState() {
	if (!states.empty()) {
		states.back()->Cleanup(this);
		states.pop_back();
	}

	if (!states.empty()) {
		states.back()->Resume();
		return;
	}
	else {
		OnUserDestroy();
	}
}

void Game::ChangeState(GameState* s) {
	if (!states.empty()) {
		states.back()->Cleanup(this);
		states.pop_back();
	}

	states.push_back(s);
	states.back()->Init(this);
}


//	
//
//	bool OnUserUpdate(float elapsedTime) override {
//		Clear(olc::BLACK);
//		DrawShip();
//		ship.move(elapsedTime);
//		
//		
//
//		return true;
//	}
//
//
//	
	bool Game::Draw(int32_t x, int32_t y, olc::Pixel p) {
		float xf = x;
		float yf = y;
		WrapCoordinates(xf, yf, xf, yf);
		return olc::PixelGameEngine::Draw(xf, yf, p);
	}

	/*
		Wrap a point so it stays in window range
	*/
	void Game::WrapCoordinates(float ix, float iy, float& ox, float& oy) {
		ox = ix;
		oy = iy;
		if (ix < 0.0f) ox = ScreenWidth() + ix;
		if (ix > (float)ScreenWidth()) ox = -(float)ScreenWidth() + ix;
		if (iy < 0.0f) oy = ScreenHeight() + iy;
		if (iy > (float) ScreenHeight()) oy = -(float)ScreenHeight() + iy;
	}

//};

int main() {

	srand((unsigned int) time(0));
	Game g;
	if (g.Construct(480, 240, 3, 3))
		g.Start();

	return 0;
}