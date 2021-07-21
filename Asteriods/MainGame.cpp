#include "MainGame.h"
#include "Globals.h"
#include <time.h>


MainGame::MainGame() {
	srand(time(NULL));
};

void MainGame::Init(Game* g) {
	srand(time(NULL));
	ship.posx = g->ScreenWidth() / 2;
	ship.posy = g->ScreenHeight() / 2;
	
	CreateRandomAsteroids(g);
};

void MainGame::Update(Game* g, float elapsedTime) {
	g->WrapCoordinates(ship.posx, ship.posy, ship.posx, ship.posy);
	ship.move(elapsedTime);
	
	CheckAsteroidsCollision();
};

void MainGame::Draw(Game* g, float elapsedTime) {
	g->Clear(olc::BLACK);
	DrawShip(g, elapsedTime);
	DrawBullets(g, elapsedTime);
	DrawAsteriods(g, elapsedTime);
};

void MainGame::HandleEvents(Game* g, float elapsedTime) {
	if (g->GetKey(olc::Key::SPACE).bPressed) {
		auto pos(ship.getHead());
		auto shipVelocity(ship.getVelocityMagnitude());
		Bullet b(
			pos.x, 
			pos.y, 
			(60) * sin(ship.rotation), 
			(60) * cos(ship.rotation)
		);
		bullets.push_back(b);
	}
	if (g->GetKey(olc::Key::LEFT).bHeld) {
		ship.rotation += 70.0f * ship.rotationSpeed * elapsedTime;
	}
	else if (g->GetKey(olc::Key::RIGHT).bHeld) {
		ship.rotation -= 70.0f * ship.rotationSpeed * elapsedTime;
	}
		
	if (g->GetKey(olc::Key::Z).bPressed) {
		CreateRandomAsteroids(g);
	}
				
	if (g->GetKey(olc::Key::UP).bHeld) {
		ship.accelerate(elapsedTime);
	}
};

void MainGame::Cleanup(Game* g) {};

void MainGame::Pause() {

};

void MainGame::Resume() {};

void MainGame::DrawShip(Game* g, float elapsedTime) {
	// Midpoint
	Point head(ship.getHead());
	Point left(ship.getLeft());
	Point right(ship.getRight());

	g->DrawLine(head, left);
	g->DrawLine(left, right);
	g->DrawLine(right, head);
};


void MainGame::CreateRandomAsteroids(Game* g, int num) {
	for (int i = 0; i < num; ++i) {
		float x = rand() % g->ScreenWidth();
		float y = rand() % g->ScreenHeight();

		float vx = rand() % 10 + 20;
		float vy = rand() % 10 + 20;

		float radius = rand() % 20 + 10;

		Asteriod a{ 20, radius, x, y };

		asteriods.push_back(a);
	}
};


void MainGame::DrawBullets(Game* g, float elapsedTime) {
	const auto& r = std::remove_if(bullets.begin(), bullets.end(), 
		[this, g](Bullet& b) {
			return (b.posx > g->ScreenWidth() || b.posx < 0.0f)
				||
				(b.posy > g->ScreenHeight() || b.posy < 0.0f);
		});
		
	bullets.erase(r, bullets.end());

	for (Bullet& b : bullets) {
		g->FillCircle(olc::vi2d(b.posx, b.posy), b.radius);
		b.move(elapsedTime);
	}
}

void MainGame::DrawAsteriods(Game* g, float elapsedTime) {
	for (Asteriod& a : asteriods) {
		a.updatePoints(0, 0, elapsedTime);
		g->WrapCoordinates(a.currentX, a.currentY, a.currentX, a.currentY);
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


void MainGame::CheckAsteroidsCollision() {

}