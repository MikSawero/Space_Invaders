#pragma once

#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Game.hpp"
#include "MainMenuWindow.hpp"
#include "DEFINITIONS.hpp"
#include <sstream>
#include <iostream>
#include "../Entities/Player.hpp"
#include "SaveWindow.hpp"

namespace ms
{
	class GameOverWindow :public Window
	{
	public:
		GameOverWindow(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Clock _clock;

		sf::Sprite _background;
		sf::Sprite _title;

		sf::Text _textScore;
		sf::Text _textTryAgain;

		sf::Text _textYes;
		sf::Text _textNo;
		bool _chosenNo;
		bool _chosenYes;
	};
}

