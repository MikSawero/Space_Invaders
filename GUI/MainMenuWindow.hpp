#pragma once

#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Game.hpp"


namespace ms
{
	class MainMenuWindow :public Window
	{
	public:
		MainMenuWindow(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _title;
		sf::Sprite _playButton;
		//sf::Sprite _settingsButton;
		sf::Sprite _exitButton;

	};
}