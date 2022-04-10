#include "Animation.h"
#include <iostream>

Animation::Animation(Texture* texture, int frameWidth,
	int frameHeight, int framesX, int framesY)
{
	_isPlaying = false;
	_frameW = frameWidth;
	_frameH = frameHeight;
	_cantFramesX = framesX;
	_cantFramesY = framesY;
	_pTexture = texture;
	this->setTexture(*_pTexture);
	_actualFrame.x = 0;
	_actualFrame.y = 0;
	this->setScale(0.5f, 0.5f);
	this->SelectFrame();
}

void Animation::SelectFrame() 
{
	IntRect rectangleFrame(_actualFrame.x * _frameW, _actualFrame.y * _frameH, _frameW, _frameH);
	this->setTextureRect(rectangleFrame);
}

bool Animation::Animate(float acumTime, float timeLapse)
{
	if (_actualFrame.x != _cantFramesX)
	{
		//std::cout << "Dibujando frame: " << _actualFrame.x + 1 << std::endl;
		_actualFrame.x += 1;
	}
	else {
		_actualFrame.x = 0;
		SelectFrame();
		return false;
	}
	SelectFrame();
	return true;
}