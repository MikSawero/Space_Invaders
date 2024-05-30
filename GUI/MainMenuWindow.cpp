#include <iostream>
#include "MainMenuWindow.hpp"
#include "GameWindow.hpp"
#include "SettingsWindow.hpp"


namespace ms
{
	MainMenuWindow::MainMenuWindow(GameDataRef data): _data(data)
	{

	}

	void MainMenuWindow::Init()
	{
		std::cout << "Main Menu Initialization\n";
		_data->assets.LoadTexture("Main Menu Background",
			MAIN_MENU_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);

		_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);
		//_data->assets.LoadTexture("Settings Button", SETTINGS_BUTTON_FILEPATH);
		_data->assets.LoadTexture("Exit Button", EXIT_BUTTON_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"));
		_title.setTexture(this->_data->assets.GetTexture("Game Title"));
		_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
		//_settingsButton.setTexture(this->_data->assets.GetTexture("Settings Button"));
		_exitButton.setTexture(this->_data->assets.GetTexture("Exit Button"));

		_title.setScale(0.2f, 0.2f);
		_playButton.setScale(0.1f, 0.1f);
		//_settingsButton.setScale(0.15f, 0.15f);
		_exitButton.setScale(0.1f, 0.1f);
		
		_title.setPosition((SCREEN_WIDTH - _title.getGlobalBounds().width) / 2, _title.getGlobalBounds().height*2);
		_playButton.setPosition((SCREEN_WIDTH - _playButton.getGlobalBounds().width) / 2, _playButton.getGlobalBounds().height * 9);
		//_settingsButton.setPosition((SCREEN_WIDTH - _settingsButton.getGlobalBounds().width) / 2, _settingsButton.getGlobalBounds().height * 9);
		_exitButton.setPosition((SCREEN_WIDTH - _exitButton.getGlobalBounds().width) / 2, _exitButton.getGlobalBounds().height * 11);

	}

	void MainMenuWindow::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type || _data->input.IsSpriteClicked(_exitButton, sf::Mouse::Left, _data->window))
			{
				std::cout << "Closing App\n";
				_data->window.close();
			}

			if (_data->input.IsSpriteClicked(_playButton, sf::Mouse::Left, _data->window))
			{
				_data->machine.AddState(StateRef(new GameWindow(_data)), true);
			}

		}
	}

	void MainMenuWindow::Update(float dt)
	{

	}

	void MainMenuWindow::Draw(float dt)
	{
		_data->window.clear();

		_data->window.draw(_background);
		_data->window.draw(_title);
		_data->window.draw(_playButton);
		//_data->window.draw(_settingsButton);
		_data->window.draw(_exitButton);
	
		_data->window.display();
	}
}
