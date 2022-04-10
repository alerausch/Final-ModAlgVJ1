#include "Explosion.h"

Explosion::Explosion(string spritePath, float fps)
{
	_pTexExp = new Texture();
	if (!_pTexExp->loadFromFile(spritePath)) {
		cout << "No se pudo cargar la imagen: " << spritePath << endl;
	}
	_pSprExp = new Animation(_pTexExp, 192, 192, 7, 1);
	_pSprExp->setPosition(100, 100);
	_fps = fps;
	_timeLapse = (static_cast<float>(1) / _fps) * 1000;
	std::cout << "Cantidad de fps: " << _timeLapse << std::endl;
	_acumTime = 0.0f;
	_isPlaying = false;
	_acumTime = 0;
}

Explosion::~Explosion()
{
	delete _pTexExp;
	delete _pSprExp;
}

void Explosion::Draw(RenderWindow* pWnd)
{
	if (_isPlaying) 
		pWnd->draw(*_pSprExp);
}

void Explosion::Update(float dt)
{
	_acumTime += dt * 1000;
	//std::cout << "Tiempo acumulado de frame: " << _acumTime << std::endl;
	if (_acumTime >= _timeLapse)
		if (_pSprExp->Animate(_acumTime, _timeLapse))
			_acumTime = 0;
		else
			_isPlaying = false;
}