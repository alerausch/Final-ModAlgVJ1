#include "Asteroids.h"
Asteroids::Asteroids(string filename, int x0, int y0, float velRot) : PhisicObject(filename)
{
	cout << "SE CONTRUYE UN ASTEROIDE" << endl;
	_position.x = x0;
	_position.y = y0;
	_velRot = velRot;
	_pSpr->setPosition(Vector2f(x0, y0));
	_velocity.x += 0.0f;
	_visible = true;
}

void Asteroids::Reset(int posX, int posY)
{
	_position.x = posX;
	_position.y = posY;
}

bool Asteroids::Update(float dt)
{
	_position.x += _velocity.x * dt;
	_rotation += _velRot;

	_pSpr->setRotation(_rotation);
	_pSpr->setPosition(_position);

	if (_pSpr->getPosition().x < -100) {
		Reset(rand() % 500 + 1030, rand() % 554 + 50);
	}


	return true;
}