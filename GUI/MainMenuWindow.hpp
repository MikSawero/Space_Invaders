#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Window.hpp"
#include "Game.hpp"
#include "GameWindow.hpp"
#include "LeaderboardWindow.hpp"
#include "../Managers/FileManager.hpp"


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

		sf::Text _textPlay;
		sf::Text _textLeaderboard;
		sf::Text _textExit;

		bool _chosenPlay;
		bool _chosenExit;
		bool _chosenLeaderboard;

	};
}