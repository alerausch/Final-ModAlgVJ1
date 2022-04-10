#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

class Explosion
{
public:
	Explosion(string spritePath, float fps);
	~Explosion();
	void Run() { _isPlaying = true; }
	bool GetStatus() { return _isPlaying; }
	void Draw(RenderWindow* pWnd);
	void Update(float dt);
private:
	Texture* _pTexExp;
	Animation* _pSprExp;
	bool _isPlaying;
	float _acumTime;
	float _timeLapse;
	float _fps;
};

