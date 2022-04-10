#include "Game.h"

//	CONSTRUCTOR
Game::Game()
{
	cout << "SE CONTRUYE EL JUEGO" << endl;
	srand(time(NULL));
	constexpr int FLOAT_MIN = -1.5;
	constexpr int FLOAT_MAX = 1.5;

	random_device rd;
	default_random_engine eng(rd());
	uniform_real_distribution<> distr(FLOAT_MIN, FLOAT_MAX);

	_mapVelocity = -100.0f;
	_pWnd = new RenderWindow(VideoMode(wWidth,wHeight,32), "TP FINAL ModAlgVJ_I", Style::Close);
	_pWnd->setFramerateLimit(60);
	_pTexFondo = new Texture();
	_pSprFondo = new Sprite();

	_pTexFondo->loadFromFile("assets/images/espacio.png");
	_pSprFondo->setTexture(*_pTexFondo);

	_pPlayerShip = new PlayerShip("assets/images/naveJugador.png", wHeight);
	_pPlayerShip->SetScale(0.3f);

	//_pExplosion = new Explosion("assets/images/explosion.png", 10);
	_pContrail = new AnimatedObject("assets/images/misil.png", 1, 200, 300, 
									true, 150, 60, 6, 1);

	//_pPlayerShip->SetPosition(Vector2f(50.0f, wHeight/2));

	for (int i = 0; i < 12; i++) {
		float rotacion = distr(eng);
		float escala = (rand() % 30 + static_cast<float>(10)) / 100;
		int indice = rand() % + 6;
		int posX = 1030 + ((i + 1) * 200);
		_arrayAsteroides[i] = new Asteroids(_arrayPathsImg[indice],
											posX,
											rand() % 554 + 50, 
											rotacion);
		_arrayAsteroides[i]->SetScale(escala);
		_arrayAsteroides[i]->SetVelocity(Vector2f(_mapVelocity, 0));
		/*cout << _arrayAsteroides[i]->GetPosition().x << "-" << _arrayAsteroides[i]->GetPosition().y<<endl;*/
	}

	dt = 0.0f;
	sinVidas = false;
	finDelJuego = false;
	enPausa = false;
}

//	DESTRUCTOR
Game::~Game()
{
	cout << "SE DESTRUYE EL JUEGO" << endl;
	delete _pPlayerShip;
	for (int i = 0; i < 12; i++) {
		delete _arrayAsteroides[i];
	}
	delete _pWnd;
	delete _pTexFondo;
	delete _pSprFondo;
}

void Game::Loop(){

	Clock clock;
	clock.restart();

	while (_pWnd->isOpen()){
		dt = clock.restart().asSeconds();
		_ProcessEvents();
		if (!enPausa && !finDelJuego) {
			_Update(dt);
		}
		_Draw();
	}
}

void Game::_Draw(){

	_pWnd->clear(Color::Black);
	_pWnd->draw(*_pSprFondo);
	for (int i = 0; i < 12; i++) {
		if (_arrayAsteroides[i]->GetVisible())
			_arrayAsteroides[i]->Draw(_pWnd);
	}
	//_pExplosion->Draw(_pWnd);
	_pContrail->Draw(_pWnd);
	_pPlayerShip->Draw(_pWnd);
	_pWnd->display();

}
void Game::_Update(float dt){

	// PROCESA TECLAS DE MANDO DE LA NAVE DEL JUGADOR (A - D - W - S)
	if ((_pPlayerShip->GetPosition().x >= 50 && _pPlayerShip->GetPosition().x <= 930)
		&& (_pPlayerShip->GetPosition().y >= 20 && _pPlayerShip->GetPosition().y <= 594)) {

		if (Keyboard::isKeyPressed(Keyboard::A))
			_pPlayerShip->AddAcceleration(Vector2f(-200.0f, 0.0f));

		if (Keyboard::isKeyPressed(Keyboard::D))
			_pPlayerShip->AddAcceleration(Vector2f(500.0f, 0.0f));

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			_pPlayerShip->AddAcceleration(Vector2f(0.0f, -500.0f));
			_pPlayerShip->SetRotation(-10.0f);
		}

		if (Keyboard::isKeyPressed(Keyboard::S)) {
			_pPlayerShip->AddAcceleration(Vector2f(0.0f, 500.0f));
			_pPlayerShip->SetRotation(10.0f);
		}

	}
	// CORRIJO POSICION DE LA NAVE EN LOS BORDES DE PANTALLA SETEANDO 
	// UNA PEQUEÑA VELOCIDAD INVERSA
	else {
		if (_pPlayerShip->GetPosition().x < 50) {
			_pPlayerShip->SetPosition(Vector2f(50, _pPlayerShip->GetPosition().y));
			_pPlayerShip->SetVelocity(Vector2f(100, _pPlayerShip->GetVelocity().y));
		}
		if (_pPlayerShip->GetPosition().x > 930) {
			_pPlayerShip->SetPosition(Vector2f(930, _pPlayerShip->GetPosition().y));
			_pPlayerShip->SetVelocity(Vector2f(-100, _pPlayerShip->GetVelocity().y));
		}
		if (_pPlayerShip->GetPosition().y < 20){
			_pPlayerShip->SetPosition(Vector2f(_pPlayerShip->GetPosition().x, 20));
			_pPlayerShip->SetVelocity(Vector2f(_pPlayerShip->GetVelocity().x, 100));
		}
			
		if (_pPlayerShip->GetPosition().y > 594) {
			_pPlayerShip->SetPosition(Vector2f(_pPlayerShip->GetPosition().x, 594));
			_pPlayerShip->SetVelocity(Vector2f(_pPlayerShip->GetVelocity().x, -100));
		}

	}
	// ACTUALIZACION DE TODOS LOS SPRITES EN PANTALLA
	
	for (int i = 0; i < 12; i++) {
		_arrayAsteroides[i]->Update(dt);
	}
	_pPlayerShip->Update(dt, _arrayAsteroides[0]->GetVelocity().x);
	//if (_pExplosion->GetStatus())
	//	_pExplosion->Update(dt);
	if (_pContrail->GetStatus())
		_pContrail->Update(dt);
	
}

void Game::_ProcessEvents(){

	Event evt;
	while (_pWnd->pollEvent(evt)){

		switch (evt.type) {
			case Event::Closed:
				_pWnd->close();
			case Event::KeyPressed:
				if (evt.key.code == sf::Keyboard::P) { //para pausar o reanudar el juego
					if (enPausa) {
						enPausa = false;
						/*musica.play();
						sonidoReloj.play();*/
					}
					else {
						enPausa = true;
						/*musica.pause();
						sonidoReloj.pause();*/
					}
				}
				if (evt.key.code == sf::Keyboard::R) { //para reiniciar el juego
					if (finDelJuego || sinVidas) {
						//Reiniciar();
					}
				}
				if (evt.key.code == sf::Keyboard::Space) {
					//_pExplosion->Run();
					_pContrail->Run();
				}
		}
	}

}
