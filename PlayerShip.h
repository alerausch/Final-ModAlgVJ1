#pragma once
#include <SFML\Graphics.hpp>
#include "PhisicObject.h"
#include <string>
#include <cmath>
#include "Animation.h"
#include "AnimatedObject.h"

using namespace std;
using namespace sf;

class PlayerShip : public PhisicObject
{
public:
	PlayerShip(string filename, int wHeight);
	~PlayerShip() {};
	bool Update(float dt, float mapVelocity);
	void Draw(RenderWindow* pWnd);

private:
	Vector2f _maxVel;
	AnimatedObject* _contrail;
};

