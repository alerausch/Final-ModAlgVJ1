#include "AnimatedObject.h"

AnimatedObject::AnimatedObject(string spritePath, float fps, int posX, int posY, 
								bool loop, int frameW, int frameH, int framesX, int framesY)
{
	_pTexAnimObj = new Texture();
	if (!_pTexAnimObj->loadFromFile(spritePath)) {
		cout << "No se pudo cargar la imagen: " << spritePath << endl;
	}
	_pSprAnimObj = new Animation(_pTexAnimObj, frameW, frameH, framesX, framesY);
	_pSprAnimObj->setOrigin(_pTexAnimObj->getSize().x / 2, _pTexAnimObj->getSize().y / 2);
	_pSprAnimObj->setPosition(posX, posY);
	_fps = fps;
	_timeLapse = (static_cast<float>(1) / _fps) * 1000;
	_acumTime = 0.0f;
	_isPlaying = false;
	_acumTime = 0;
	_loop = loop;
}

AnimatedObject::~AnimatedObject()
{
	delete _pTexAnimObj;
	delete _pSprAnimObj;
}

void AnimatedObject::Draw(RenderWindow* pWnd)
{
	if (_isPlaying)
		pWnd->draw(*_pSprAnimObj);
}

void AnimatedObject::Update(float dt)
{
	_acumTime += dt * 1000;
	if (_acumTime >= _timeLapse)
		if (_pSprAnimObj->Animate(_acumTime, _timeLapse))
			_acumTime = 0;
		else {
			if (!_loop)
				_isPlaying = false;
		}
			
}
