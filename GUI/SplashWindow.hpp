#pragma once

#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Game.hpp"


namespace ms
{
	class SplashWindow :public Window
	{
	public:
		SplashWindow(GameDataRef data);
		
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