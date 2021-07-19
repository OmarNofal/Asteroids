#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#define _USE_MATH_DEFINES
#include <cmath>
#define OLC_PGE_APPLICATION

#include "Globals.h"
#include "olcPixelGameEngine.h"
#include "Ship.h"
#include "MatrixOps.h"
#include "Bullet.h"
#include "Asteriod.h"

class Game : public olc::PixelGameEngine {

private:
	Ship ship;
	std::vector<Bullet> bullets;
	std::vector<Asteriod> asteriods;

public:
	Game(): ship() {
		sAppName = "Asteriods";
	}

private:
	
	void DrawShip() {
		// Midpoint
		Point head(ship.getHead());
		Point left(ship.getLeft());
		Point right(ship.getRight());

		DrawLine(head, left);
		DrawLine(left, right);
		DrawLine(right, head);
	}


	bool OnUserCreate() override {
		srand(time(NULL));
		ship.posx = ScreenWidth() / 2;
		ship.posy = ScreenHeight() / 2;

		CreateRandomAsteriods();

 		return true;
	}

	bool OnUserUpdate(float elapsedTime) override {
		Clear(olc::BLACK);
		DrawShip();

		if (GetKey(olc::Key::SPACE).bPressed) {
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
		if (GetKey(olc::Key::LEFT).bHeld) {
			ship.rotation += 70.0f * ship.rotationSpeed * elapsedTime;
		}
		else if (GetKey(olc::Key::RIGHT).bHeld) {
			ship.rotation -= 70.0f * ship.rotationSpeed * elapsedTime;
		}

		if (GetKey(olc::Key::Z).bPressed) {
			CreateRandomAsteriods();
		}
		
		if (GetKey(olc::Key::UP).bHeld) {
			ship.accelerate(elapsedTime);
		}

		WrapCoordinates(ship.posx, ship.posy, ship.posx, ship.posy);
		ship.move(elapsedTime);
		
		DrawBullets(elapsedTime);
		DrawAsteriods(elapsedTime);

		return true;
	}

	void DrawBullets(float elapsedTime) {
		const auto& r = std::remove_if(bullets.begin(), bullets.end(), 
			[this](Bullet& b) {
				return (b.posx > this->ScreenWidth() || b.posx < 0.0f)
					||
					(b.posy > this->ScreenHeight() || b.posy < 0.0f);
			});
		
		bullets.erase(r, bullets.end());

		for (Bullet& b : bullets) {
			FillCircle(olc::vi2d(b.posx, b.posy), b.radius);
			b.move(elapsedTime);
		}
	}

	void DrawAsteriods(float elapsedTime) {
		for (Asteriod& a : asteriods) {
			float newX = a.currentX + a.vx * elapsedTime;
			float newY = a.currentY + a.vy * elapsedTime;

			a.updatePoints(newX, newY, elapsedTime);
			for (int i = 0; i < a.points.size(); ++i) {
				if (i == a.points.size() - 1) {
					DrawLine(a.points[0], a.points[i]);
					break;
				}
				DrawLine(a.points[i], a.points[i + 1]);
			}
		}
	}
	
	bool Draw(int32_t x, int32_t y, olc::Pixel p = olc::WHITE) {
		float xf = x;
		float yf = y;
		WrapCoordinates(xf, yf, xf, yf);
		return olc::PixelGameEngine::Draw(xf, yf, p);
	}

	/*
		Wrap a point so it stays in window range
	*/
	void WrapCoordinates(float ix, float iy, float& ox, float& oy) {
		ox = ix;
		oy = iy;
		if (ix < 0.0f) ox = ScreenWidth() + ix;
		if (ix > (float)ScreenWidth()) ox = -(float)ScreenWidth() + ix;
		if (iy < 0.0f) oy = ScreenHeight() + iy;
		if (iy > (float) ScreenHeight()) oy = -(float)ScreenHeight() + iy;
	}

	void CreateRandomAsteriods() {
		for (int i = 0; i < 4; ++i) {
			float x = rand() % ScreenWidth();
			float y = rand() % ScreenHeight();

			float vx = rand() % 10 + 20;
			float vy = rand() % 10 + 20;

			float radius = rand() % 20 + 10;

			Asteriod a{ 20, radius, x, y };
			a.vx = vx;
			a.vy = vy;
			asteriods.push_back(a);
		}
	}

};

int main() {

	srand((unsigned int) time(0));
	Game g;
	if (g.Construct(480, 240, 3, 3))
		g.Start();

	return 0;
}