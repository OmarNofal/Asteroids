#include "MainMenu.h"
#include "Globals.h"
#include "Util.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

MainMenu::MainMenu() {

	LoadHighScore();
	arrowSprite = new olc::Sprite("./data/ArrowSprite.png");
}


void MainMenu::LoadHighScore() {
	std::fstream file("./scores.txt", std::ios_base::in);

	if (file.bad())
		return; // score already zero
	
	std::string line;
	while (file.peek() != EOF) {
		std::getline(file, line);
		long long sc = std::stoll(line);
		highScore = highScore > sc ? highScore : sc;
	}
	file.close();
}

void MainMenu::Init(Game* g) {
	startPos = Point(g->ScreenWidth() / 2 - 10, g->ScreenHeight() / 2);
	exitPos = Point(g->ScreenWidth() / 2 - 10, g->ScreenHeight() / 2 + 20);
	GenerateAsteroids(g);
}

void MainMenu::GenerateAsteroids(Game* g) {
	for (int i = 0; i < 7; i++) {
		float radius = util::RandomFloat(10, 50);
		float v = util::RandomFloat(10, 100);
		float angle = util::RandomFloat(-2*3.14159, 2 * 3.14159);
		float vx = v * cos(angle);
		float vy = v * sin(angle);
		float posX = util::RandomFloat(0, g->ScreenWidth());
		float posY = util::RandomFloat(0, g->ScreenHeight());
		Asteroid a(20, radius, posX, posY);
		a.vx = vx;
		a.vy = vy;
		asteroids.push_back(a);
	}
}

void MainMenu::Cleanup(Game* g) {

}

void MainMenu::Pause() {

}

void MainMenu::Resume() {
	LoadHighScore();
}

void MainMenu::HandleEvents(Game* g, float elapsedTime) {
	
	if (g->GetKey(olc::Key::DOWN).bPressed) {
		selected = Options::EXIT;
	}
	else if (g->GetKey(olc::Key::UP).bPressed) {
		selected = Options::START;
	}

	if (g->GetKey(olc::Key::ENTER).bPressed) {
		HandleEnterCommand(g);
	}
};
void MainMenu::Update(Game* g, float elapsedTime) {
	for (auto& a : asteroids) {
		g->WrapCoordinates(a.currentX, a.currentY, a.currentX, a.currentY);
		a.updatePoints(0, 0, elapsedTime);
	}
};
void MainMenu::Draw(Game* g, float elapsedTime) {
	g->Clear(olc::VERY_DARK_BLUE);
	DrawTitle(g);
	DrawHighScore(g);
	DrawOptionsMenu(g);
	DrawAsteroids(g);
};

void MainMenu::DrawAsteroids(Game* g) {
	for (Asteroid& a : asteroids) {
		//g->WrapCoordinates(a.currentX, a.currentY, a.currentX, a.currentY);
		for (size_t i = 0; i < a.points.size(); ++i) {
			float x1 = a.currentX + a.points[i].first; // get absolute position
			float y1 = a.currentY + a.points[i].second;

			Point p1(x1, y1);
			if (i == a.points.size() - 1) {
				float x2 = a.currentX + a.points[0].first;
				float y2 = a.currentY + a.points[0].second;
				Point p2(x2, y2);
				g->DrawLine(p1, p2, olc::RED);
				break;
			}

			float x2 = a.currentX + a.points[i + 1].first;
			float y2 = a.currentY + a.points[i + 1].second;

			Point p2(x2, y2);
			g->DrawLine(p1, p2, olc::RED);
		}
	}
}

void MainMenu::DrawTitle(Game* g) {
	g->Draw(g->ScreenWidth() / 2 - 70, g->ScreenHeight() / 2 - 60);
	g->DrawString(Point(g->ScreenWidth() / 2 - 70, g->ScreenHeight() / 2 - 60), "Asteroids", olc::WHITE, 2);
};


void MainMenu::DrawHighScore(Game* g) {
	g->DrawString(Point(10, g->ScreenHeight() - 15), "High Score: " + std::to_string(highScore));
}

void MainMenu::DrawOptionsMenu(Game* g) {
	g->DrawString(startPos, "Start");
	g->DrawString(exitPos, "Exit");
	Point pos;
	if (selected == Options::START)
		pos = startPos - Point(12, 0);
	else if (selected == Options::EXIT)
		pos = exitPos - Point(12, 0);
	g->SetPixelMode(olc::Pixel::MASK);
	g->DrawSprite(pos, arrowSprite);
	g->SetPixelMode(olc::Pixel::NORMAL);
}

void MainMenu::HandleEnterCommand(Game* g) {
	if (selected == Options::EXIT){
		g->PopState();
		return;
	}
	g->PushState(new MainGame());
}