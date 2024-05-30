#pragma once

#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Game.hpp"

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
		sf::Sprite _label;

	};
}

