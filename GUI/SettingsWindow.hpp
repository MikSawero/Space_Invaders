#pragma once

#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Game.hpp"

namespace ms
{
	class SettingsState :public Window
	{
	public:
		SettingsState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Clock _clock;

		sf::Texture _backgroundTexture;
		sf::Sprite _background;
		sf::Sprite _label;

	};
}