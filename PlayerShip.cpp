#include "PlayerShip.h"
#include <iostream>

PlayerShip::PlayerShip(string filename, int wHeight):PhisicObject(filename)
{
	_maxVel.x = 300.0f;
	_maxVel.y = 150.0f;
	SetPosition(Vector2f(80.0f, wHeight / 2));
	_contrail = new AnimatedObject("assets/images/combustion.png", 10, 
						_position.x + 15, _position.y + 5, true, 80, 80, 4, 1);
	_contrail->Run();
}


bool PlayerShip::Update(float dt, float mapVelocity)
{
	// CONTROLO VELOCIDADES MAXIMAS DE LA NAVE
	if (abs(_velocity.x) < _maxVel.x)
		_velocity.x += _acceleration.x * dt;
	
	if (abs(_velocity.y) < _maxVel.y)
		_velocity.y += _acceleration.y * dt;

	// SI NO HAY ACELERACION NI VELOCIDAD Y LA NAVE NO ESTA A LA IZQUIERDA DE LA PANTALLA; 
	// SE DESPLAZA HASTA EL BORDE IZQUIERDO A LA VELOCIDAD DEL MAPA (la misma está 
	// dada por la velocidad de los asteroides)
	float temp = mapVelocity * dt;
	if (_velocity.x == 0 && _position.x > 80) {
		_position.x += temp;
	} else {
		_position.x += _velocity.x * dt;
	}

	_position.y += _velocity.y * dt;

	// SETEO POSICION Y ROTACION DE LA NAVE Y SU ESTELA DE COMBUSTION
	_pSpr->setRotation(_rotation);
	_pSpr->setPosition(_position);
	_contrail->_pSprAnimObj->setRotation(_rotation);
	
	// SI HAY ACELERACION Y DESPLAZAMIENTO DE LA NAVE, CAMBIO POSICION DE LA ESTELA DE COMBUSTION
	if (_acceleration.x > 0)
		_contrail->_pSprAnimObj->setPosition(Vector2f(_position.x + 5, _position.y + 5));
	else
		_contrail->_pSprAnimObj->setPosition(Vector2f(_position.x + 15, _position.y + 5));
	
	// APLICO FRENO EN X A LA NAVE
	if (_velocity.x != 0)
		if (_velocity.x < 0)
			_velocity.x += 4;
		else if (_velocity.x > 0)
			_velocity.x -= 4;
	// APLICO FRENO EN Y A LA NAVE
	if (_velocity.y != 0)
		if (_velocity.y < 0)
			_velocity.y += 4;
		else if (_velocity.y > 0)
			_velocity.y -= 4;
	// CORRIJO ROTACIÓN DE LA NAVE Y SU ESTELA DESPUES DE ACCENDER O DESCENDER
	if (_rotation != 0)
		if (_rotation < 0)
			_rotation += 2;
		else if (_rotation > 0)
			_rotation -= 2;
	_contrail->Update(dt);

	cout << "Acc en X: " << _acceleration.x << endl;

	// SETEO ACELERACION EN CERO
	_acceleration.x = 0.0f;
	_acceleration.y = 0.0f;

	// SI LA VELOCIDAD ESTA CERCANA A CERO LA SETEO A 0 PARA PODER MOVER LA NAVE A LA IZQUIERDA DEL MAPA
	if (_velocity.x < 2.0f && _velocity.x > -2.0f)
		_velocity.x = 0.0f;

	cout << "Velocidad en X: " << _velocity.x << endl;
	
	return true;
}

void PlayerShip::Draw(RenderWindow* pWnd)
{
	_contrail->Draw(pWnd);
	pWnd->draw(*_pSpr);
}