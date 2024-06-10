#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <regex>
#include <string>

#include "DEFINITIONS.hpp"

#include "../Managers/FileManager.hpp"
#include "../Entities/Player.hpp"
#include "MainMenuWindow.hpp"
#include "GameWindow.hpp"
#include "Window.hpp"
#include "Game.hpp"



namespace ms
{
	class SaveWindow :public Window
	{
	public:
		SaveWindow(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		std::string _text;

		sf::Clock _clock;

		sf::Sprite _background;
		sf::Sprite _title;

		sf::Text _textQuestion;
		sf::Text _textName;

		sf::Text _textEnter;
		sf::Text _inputErrorText;
		bool _inputError;

		std::regex allowed_chars;
	};
}

