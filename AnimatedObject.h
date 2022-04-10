#pragma once
#include <SFML\Graphics.hpp>
#include "PhisicObject.h"
#include <string>
#include <iostream>
#include "Animation.h"

using namespace std;
using namespace sf;


class AnimatedObject
{
public:
	AnimatedObject(string spritePath, float fps, int posX, int posY,
				bool loop, int frameW, int frameH, int framesX, int framesY);
	~AnimatedObject();
	void Update(float dt);
	void Run() { _isPlaying = true; }
	bool GetStatus() { return _isPlaying; }
	void Draw(RenderWindow* pWnd);
	Animation* _pSprAnimObj;
private:
	Texture* _pTexAnimObj;
	//Animation* _pSprAnimObj;
	bool _isPlaying;
	float _acumTime;
	float _timeLapse;
	float _fps;
	bool _loop;
};

