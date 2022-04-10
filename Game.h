#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <random>
#include <iomanip>
#include "PlayerShip.h"
#include "Asteroids.h"
#include "AnimatedObject.h"
using namespace sf;

class Game
{
public:

//métodos
	Game();
	~Game();
	void Loop();
	
private:
//constantes
	const float wHeight = 614;
	const float wWidth = 1024;
//métodos
	void _Draw();
	void _Update(float dt);
	void _ProcessEvents();
	void _SetMapVelocity(float mapVel) { _mapVelocity = mapVel; }
//variables
	bool enPausa, sinVidas, finDelJuego;
	float dt;
	string _arrayPathsImg[6] = {"assets/images/asteroide1.png",
								"assets/images/asteroide2.png",
								"assets/images/asteroide3.png",
								"assets/images/asteroide4.png",
								"assets/images/asteroide5.png",
								"assets/images/asteroide6.png"};
	RenderWindow* _pWnd;
	PlayerShip* _pPlayerShip;
	Asteroids* _arrayAsteroides[12];
	//Explosion* _pExplosion;
	AnimatedObject* _pContrail;
	Texture* _pTexFondo;
	Sprite* _pSprFondo;
	float _mapVelocity;
};

