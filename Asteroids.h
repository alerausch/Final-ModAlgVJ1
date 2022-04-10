#pragma once
#include "PhisicObject.h"
#include <iostream>
class Asteroids : public PhisicObject
{
public:
	Asteroids(string filename, int x0, int y0, float velRot);
	~Asteroids() { cout << "SE DESTRUYE UN ASTEROIDE" << endl; };
	bool Update(float dt);
	void Reset(int posX, int posY);
	bool GetVisible() { return _visible; }
	void SetVisible() { _visible = !_visible; }
private:
	float _velRot;
	bool _visible;
};

