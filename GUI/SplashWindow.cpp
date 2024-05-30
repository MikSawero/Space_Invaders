#include <sstream>
#include <iostream>
#include "SplashWindow.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuWindow.hpp"


namespace ms
{
	SplashWindow::SplashWindow(GameDataRef data): _data(data)
	{

	}
	void SplashWindow::Init()
	{
		_data->assets.LoadTexture("Splash State Background",
			MAIN_MENU_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Splash State Label",
			LABEL_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));
		_label.setTexture(this->_data->assets.GetTexture("Splash State Label"));

		_label.setScale(0.15f, 0.15f);
		_label.setPosition(SCREEN_WIDTH / 2 - (_label.getGlobalBounds().width / 2), SCREEN_LENGTH / 2 - (_label.getGlobalBounds().height / 2));
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