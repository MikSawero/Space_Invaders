#include "SplashWindow.hpp"



namespace ms
{
	SplashWindow::SplashWindow(GameDataRef data): _data(data)
	{

	}
	void SplashWindow::Init()
	{
		std::cout << "Splash Window Initialization\n";

		std::thread load(&SplashWindow::LoadTextures, this);

		_data->assets.LoadTexture("Game Background",
			GAME_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Splash State Label",
			LABEL_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Game Background"));
		_label.setTexture(this->_data->assets.GetTexture("Splash State Label"));

		_label.setScale(0.15f, 0.15f);
		_label.setPosition(SCREEN_WIDTH / 2 - (_label.getGlobalBounds().width / 2), SCREEN_LENGTH / 2 - (_label.getGlobalBounds().height / 2));

		load.join();
	}

	void SplashWindow::LoadTextures()
	{
		_data->assets.LoadTexture("Enemy",
			YELLOW_ENEMY);
		_data->assets.LoadTexture("Player",
			PLAYER);
		_data->assets.LoadTexture("Projectile",
			PROJECTILE);


		_data->assets.LoadTexture("Shield1", SHIELD1);
		_data->assets.LoadTexture("Shield2", SHIELD2);
		_data->assets.LoadTexture("Shield3", SHIELD3);
		_data->assets.LoadTexture("Shield4", SHIELD4);
		_data->assets.LoadTexture("Shield5", SHIELD5);

		_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);

		_data->assets.LoadFont("Font", FONT);
	}
	void SplashWindow::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event)) 
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}
		}
	}

	void SplashWindow::Update(float dt)
	{
		if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			_data->machine.AddState(StateRef(new MainMenuWindow(_data)), true);
		}
	}
	void SplashWindow::Draw(float dt)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_label);
		_data->window.display();
	}
}