#include "PhisicObject.h"
#include <iostream>

PhisicObject::PhisicObject(string filename)
{
	_pTex = new Texture();
	if (!_pTex->loadFromFile(filename)) {
		cout << "No se pudo cargar la imagen: " << filename << endl;
	}

	_pSpr = new Sprite();
	_pSpr->setTexture(*_pTex);
	_pSpr->setOrigin(_pTex->getSize().x / 2, _pTex->getSize().y / 2);
	_position.x = 0.0f;
	_position.y = 0.0f;
	_acceleration.x = 0.0f;
	_acceleration.y = 0.0f;
	_velocity.x = 0.0f;
	_velocity.y = 0.0f;
	_rotation = 0.0f;
}


PhisicObject::~PhisicObject()
{
	delete _pSpr;
	delete _pTex;
}

void PhisicObject::Draw(RenderWindow* pWnd) {
	
	pWnd->draw(*_pSpr);

}
