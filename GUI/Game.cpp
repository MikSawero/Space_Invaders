#include "Game.hpp"
#include "SplashWindow.hpp"



namespace ms 
{
	Game::Game(int width, int height, std::string title)
	{
		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		_data->window.setIcon(Icon.width,Icon.height,Icon.pixel_data);
		_data->machine.AddState(StateRef(new SplashWindow(this->_data)));
		
		this->Run();
	}

	void Game::Run()
	{
		float newTime, frameTime, interpolation;
		
		float currentTime = this->_clock.getElapsedTime().asSeconds();

		float accumulator = 0.0f;

		while (this->_data->window.isOpen())
		{
			this->_data->machine.ProcessStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();
			
			frameTime = newTime - currentTime;

			if (frameTime > 1.5f)
			{
				frameTime = 1.5f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt)
			{
				this->_data->machine.GetActiveState()->HandleInput();
				this->_data->machine.GetActiveState()->Update(dt);
				if (dt)
				{
					accumulator -= dt;
				}
			}

			interpolation = accumulator / dt;
			this->_data->machine.GetActiveState()->Draw(interpolation);
		}
	}
}