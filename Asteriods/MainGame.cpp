#include "MainGame.h"
#include "Globals.h"
#include "Util.h"
#include <iostream>
#include <time.h>
#include <string>

#define __USE_MATH_DEFINES
#include <cmath>

MainGame::MainGame() {
	srand(time(NULL));
};

void MainGame::Init(Game* g) {

	ship.posx = g->ScreenWidth() / 2;
	ship.posy = g->ScreenHeight() / 2;

	// Load sprites
	hearts = new olc::Sprite("./data/HeartSprite.png");
	targetSprite = new olc::Sprite("./data/TargetSprite.png");

	CreateRandomAsteroids(g);
};

void MainGame::Update(Game* g, float elapsedTime) {
	g->WrapCoordinates(ship.posx, ship.posy, ship.posx, ship.posy);
	for (Asteroid& a : asteroids) {
		g->WrapCoordinates(a.currentX, a.currentY, a.currentX, a.currentY);
	}
	ship.move(elapsedTime);
	
	temperature -= 0.2 * elapsedTime;
	if (temperature < 0.0f) {
		overheated = false;
		temperature = 0.0f;
	}

	if (!cooldown) cooldownTime = 0.0f;
	else {
		cooldownTime += elapsedTime;
		if (cooldownTime > 3.0f) {
			cooldown = false;
			cooldownTime = 0.0f;
		}
	}

	score +=  2.0 * (double) elapsedTime;

	CheckAsteroidsCollision(g);
};

void MainGame::Draw(Game* g, float elapsedTime) {
	g->Clear(olc::VERY_DARK_BLUE);
	DrawShip(g, elapsedTime);
	DrawBullets(g, elapsedTime);
	DrawAsteriods(g, elapsedTime);
	DrawTemperature(g, elapsedTime);
	DrawHearts(g);
	DrawScore(g);
	DrawHeatseekerTarget(g);
	DrawHeatseekerMessage(g, elapsedTime);
};

void MainGame::HandleEvents(Game* g, float elapsedTime) {
	if (g->GetKey(olc::Key::SPACE).bPressed && !overheated) {
		
		auto pos(ship.getHead());
		auto shipVelocity(ship.getVelocityMagnitude());
		Bullet b(
			pos.x, 
			pos.y, 
			(140) * sin(ship.rotation), 
			(140) * cos(ship.rotation),
			1.0f,
			targetedAsteroid
		);
		bullets.push_back(b);
		temperature += 0.25;
		if (temperature >= 1.0f) overheated = true;
	}
	if (g->GetKey(olc::Key::LEFT).bHeld) {
		ship.rotation += 140.0f * ship.rotationSpeed * elapsedTime;
		if (ship.rotation > 2 * 3.14159)
			ship.rotation -= 2 * 3.14159;
	}
	else if (g->GetKey(olc::Key::RIGHT).bHeld) {
		ship.rotation -= 140.0f * ship.rotationSpeed * elapsedTime;
		if (ship.rotation < 0)
			ship.rotation += 2 * 3.14159;
	}
	
	if (g->GetKey(olc::Key::H).bPressed)
		ToggleHeatSeeker(g);

	if (g->GetKey(olc::Key::Z).bPressed) {
		CreateRandomAsteroids(g);
	}
				
	if (g->GetKey(olc::Key::UP).bHeld) {
		ship.accelerate(elapsedTime);
	}
	else {
		ship.decelerate(elapsedTime);
	}
};

void MainGame::Cleanup(Game* g) {};

void MainGame::Pause() {

};

void MainGame::Resume() {};

void MainGame::DrawShip(Game* g, float elapsedTime) {

	// cooldown animation
	int cooldownInt = cooldownTime;
	float rangeStart = (float)cooldownInt + 0.5;
	if (cooldown && cooldownTime < rangeStart) return; //don't draw

	Point head(ship.getHead());
	Point left(ship.getLeft());
	Point right(ship.getRight());

	g->DrawLine(head, left);
	g->DrawLine(left, right);
	g->DrawLine(right, head);
};

void MainGame::DrawHeatseekerMessage(Game* g, float elapsedTime) {
	if (heatSeekerMsgTime > 2.0f) {
		return;
	}
	heatSeekerMsgTime += elapsedTime;
	std::string s = heatSeekerEnabled ? "Heatseeker enabled" : "Heatseeker disabled";
	g->DrawString(Point(g->ScreenWidth() / 2 - 70, g->ScreenHeight() / 2 + 80), s);
}

void MainGame::DrawHeatseekerTarget(Game* g) {
	if (!heatSeekerEnabled) return;
	g->SetPixelMode(olc::Pixel::MASK);
	Point head(ship.getHead());
	float hx = head.x;
	float hy = head.y;

	targetedAsteroid = nullptr;
	float distance = 10000000000.0f;

	for (int i = 0; i < asteroids.size(); ++i) {

		Asteroid* a = &asteroids[i];
		float ax = a->currentX;
		float ay = a->currentY;
		float r = a->radius;

		float shortestDistance = std::abs(
			sqrt((hx - ax) * (hx - ax) + (hy - ay) * (hy - ay)) - r
		);

		if (shortestDistance > targetingRadius) continue;

		Point v1 = head - (ship.getLeft() + ship.getRight()) / 2;
		Point v2 = -head + Point(ax, ay);
		double angle = util::Angle2V(v1, v2);

		if (shortestDistance > distance) continue;

		distance = shortestDistance;

		if (angle < targetingAngle / 2.0f && angle > -targetingAngle / 2.0f) { // target locked
			targetedAsteroid = a;
		}
	}
	if (targetedAsteroid != nullptr) {
		g->DrawSprite(Point(targetedAsteroid->currentX - 4, targetedAsteroid->currentY - 4), targetSprite);
	}
	g->SetPixelMode(olc::Pixel::NORMAL);
}

void MainGame::DrawTemperature(Game* g, float elapsedTime) {
	int32_t x_pos = g->ScreenWidth() - 80;
	int32_t y_pos = 25;

	int32_t width = 70 * temperature;
	if (width > 70)
		width = 70;

	auto color = olc::GREEN;
	if (temperature < 0.6f && temperature > 0.3f) {
		color = olc::YELLOW;
	}
	if (temperature >= 0.6f || overheated) {
		color = olc::RED;
	}

	g->FillRect(Point(x_pos, y_pos), Point(width, 10), color);
	g->DrawRect(Point(x_pos, y_pos), Point(70, 10), olc::DARK_RED);
	g->DrawString(Point(x_pos - 40, y_pos), "Temp");
	if (overheated) {
		g->DrawString(Point(x_pos, y_pos + 15), "Overheat");
	}
}

void MainGame::CreateRandomAsteroids(Game* g, int num) {
	srand(time(NULL));
	for (int i = 0; i < num; ++i) {
		float x = rand() % g->ScreenWidth();
		float y = rand() % g->ScreenHeight();

		float vx = util::RandomFloat(-20, 20);
		float vy = util::RandomFloat(-20, 20);

		float radius = util::RandomFloat(10, 30);

		Asteroid a{ 20, radius, x, y };

		asteroids.push_back(a);
	}
};

void MainGame::DrawScore(Game* g) {
	int32_t x_pos = 10;
	int32_t y_pos = 10;
	std::string s = "Score: " + std::to_string((long long) score);
	g->DrawString(Point(x_pos, y_pos), s);
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
		olc::Pixel color = b.target == nullptr ? olc::WHITE : olc::RED;
		g->FillCircle(olc::vi2d(b.posx, b.posy), b.radius, color);
		b.move(elapsedTime);
	}
};

void MainGame::DrawAsteriods(Game* g, float elapsedTime) {
	for (Asteroid& a : asteroids) {
		a.updatePoints(0, 0, elapsedTime);
		g->Draw(a.currentX, a.currentY);
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
};


void MainGame::CheckAsteroidsCollision(Game* g) {
	Point shipHead(ship.getHead());
	Point shipRight(ship.getRight());
	Point shipLeft(ship.getLeft());
	
	float shipHeadX;
	float shipHeadY;

	float shipRightX;
	float shipRightY;

	float shipLeftX;
	float shipLeftY;

	g->WrapCoordinates(shipHead.x, shipHead.y, shipHeadX, shipHeadY);
	g->WrapCoordinates(shipRight.x, shipRight.y, shipRightX, shipRightY);
	g->WrapCoordinates(shipLeft.x, shipLeft.y, shipLeftX, shipLeftY);

	for (size_t i = 0; i < asteroids.size(); i++) {
		Asteroid& a = asteroids[i];
		bool isShipInsideAsteroid =
			util::IsPointInsideCircle(shipHeadX, shipHeadY, a.currentX, a.currentY, a.radius)
			||
			util::IsPointInsideCircle(shipRightX, shipRightY, a.currentX, a.currentY, a.radius)
			||
			util::IsPointInsideCircle(shipLeftX, shipLeftY, a.currentX, a.currentY, a.radius);

		if (isShipInsideAsteroid && !cooldown)
			HandleShipCollision(g);

		CheckAsteroidCollision(i);
	}

};

void MainGame::HandleShipCollision(Game* g) {
	currentLives -= 1;
	ResetShip(g);
};

void MainGame::CheckAsteroidCollision(size_t a_index) {
	for (size_t i = 0; i < bullets.size(); i++) {
		Bullet& b = bullets[i];
		Asteroid& a = asteroids[a_index];
		bool bulletInAsteroid =
			util::IsPointInsideCircle(b.posx, b.posy, a.currentX, a.currentY, a.radius);
		if (bulletInAsteroid) {
			HandleAsteroidCollision(a_index);
			bullets.erase(bullets.begin() + i);
			return;
		}
	}
};

void MainGame::HandleAsteroidCollision(size_t a_index) {
	Asteroid& a = asteroids[a_index];
	float x = a.currentX;
	float y = a.currentY;
	float radius = a.radius;

	if (radius > 15.0f) {
		float minRadius = radius / 3.0f;
		float maxRadius = radius / 2.0f;
		float n1_radius = util::RandomFloat(minRadius, maxRadius);
		float n2_radius = util::RandomFloat(minRadius, maxRadius);
		Asteroid n1{ 20, n1_radius, x, y };
		Asteroid n2{ 20, n2_radius, x, y };
		asteroids.push_back(n1);
		asteroids.push_back(n2);
	}

	score += 400 / radius;
	asteroids.erase(asteroids.begin() + a_index);
};



void MainGame::DrawHearts(Game* g) {

	g->SetPixelMode(olc::Pixel::MASK); // for transparency

	int lostLives = maxLives - currentLives;

	int x_offset = 20; // offset from right of the screen
	int32_t y_pos = 5;

	for (int i = 1; i < maxLives + 1; i++) {
		int32_t x_pos = g->ScreenWidth() - x_offset;
		x_offset += 16;
		if (i <= lostLives) { // drawing dead heart
			g->DrawPartialSprite(Point(x_pos, y_pos), hearts, Point(0, 0), Point(16, 16));
		}
		else { // drawing healthy heart
			g->DrawPartialSprite(Point(x_pos, y_pos), hearts, Point(16, 0), Point(16, 16));
		}
	}

	g->SetPixelMode(olc::Pixel::NORMAL);
};

void MainGame::ResetShip(Game* g) {
	cooldown = true;
	ship.posx = g->ScreenWidth() / 2;
	ship.posy = g->ScreenHeight() / 2;
	ship.vx = 0;
	ship.vy = 0;
	ship.rotation = 0;
	temperature = 0.0f;
};

void MainGame::ToggleHeatSeeker(Game* g) {
	heatSeekerEnabled = !heatSeekerEnabled;
	heatSeekerMsgTime = 0.0f;
}
