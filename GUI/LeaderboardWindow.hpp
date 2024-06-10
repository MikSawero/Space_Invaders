#pragma once

#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Game.hpp"
#include "MainMenuWindow.hpp"
#include "../Managers/FileManager.hpp"

#include <sstream>
#include <iostream>
#include <memory>
#include <string>
#include <ranges>

namespace ms
{
	class LeaderboardWindow :public Window
	{
	public:
		LeaderboardWindow(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		std::vector<std::string> scores;

		sf::Sprite _background;

		sf::Text _leaderboardLabel;
		sf::Text _backToMenu;

		bool _chosenBackToMenu;
		std::vector<std::vector<sf::Text>> _showingScores;
	};
}