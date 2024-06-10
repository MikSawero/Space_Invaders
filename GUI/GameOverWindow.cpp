#include "GameOverWindow.hpp"

namespace ms
{
	GameOverWindow::GameOverWindow(GameDataRef data) : _data(data)
	{

	}
	void GameOverWindow::Init()
	{
		_background.setTexture(this->_data->assets.GetTexture("Game Background"));

		_title.setTexture(this->_data->assets.GetTexture("Game Title"));
		_title.setScale(0.2f, 0.2f);
		_title.setPosition((SCREEN_WIDTH - _title.getGlobalBounds().width) / 2,
		_title.getGlobalBounds().height * 2);

		_textScore.setFont(_data->assets.GetFont("Font"));
		_textScore.setCharacterSize(32);
		_textScore.setString("Score: " + std::to_string(Player::_score));
		_textScore.setPosition(SCREEN_WIDTH/2 - _textScore.getGlobalBounds().width/2,
			SCREEN_LENGTH/2 - 100);
		
		_textTryAgain.setFont(_data->assets.GetFont("Font"));
		_textTryAgain.setCharacterSize(32);
		_textTryAgain.setString("Do you want to save your score?");
		_textTryAgain.setPosition(SCREEN_WIDTH/2 - _textTryAgain.getGlobalBounds().width / 2,
			SCREEN_LENGTH / 2 );

		_textYes.setFont(_data->assets.GetFont("Font"));
		_textYes.setCharacterSize(32);
		_textYes.setString("YES");
		_textYes.setPosition(SCREEN_WIDTH * 4/10 - _textYes.getGlobalBounds().width / 2,
			SCREEN_LENGTH / 2 + 100);

		_textNo.setFont(_data->assets.GetFont("Font"));
		_textNo.setCharacterSize(32);
		_textNo.setString("NO");
		_textNo.setPosition(SCREEN_WIDTH * 6/10 - _textNo.getGlobalBounds().width / 2 ,
			SCREEN_LENGTH / 2 + 100);
	}

	void GameOverWindow::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}

			if (event.key.scancode == sf::Keyboard::Scan::Right)
			{
				std::cout << "Right Key Pressed" << std::endl;
				_textYes.setFillColor(sf::Color::White);
				_textNo.setFillColor(sf::Color::Yellow);
				_chosenNo = true;
				_chosenYes = false;
			}

			if (sf::Event::KeyPressed == event.type
				&& event.key.scancode == sf::Keyboard::Scan::Left)
			{
				std::cout << "Left Key Pressed" << std::endl;
				_textNo.setFillColor(sf::Color::White);
				_textYes.setFillColor(sf::Color::Yellow);
				_chosenNo = false;
				_chosenYes = true;
			}

			if (event.type == sf::Event::MouseButtonPressed
				|| event.key.scancode == sf::Keyboard::Scan::Enter)
			{
				if (_chosenNo)
				{
					_data->machine.RemoveState();
					_data->machine.AddState(StateRef(new MainMenuWindow(_data)), true);
				}
				if(_chosenYes)
				{
					_data->machine.RemoveState();
					_data->machine.AddState(StateRef(new SaveWindow(_data)), true);
				}
			}

			if (event.type == sf::Event::MouseMoved)
			{
				if (_textYes.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
				{
					//std::cout << "Mouse in Yes Text" << std::endl;
					_textYes.setFillColor(sf::Color::Yellow);
					_chosenYes = true;
				}
				else
				{
					_textYes.setFillColor(sf::Color::White);
					_chosenYes = false;
				}

				if (_textNo.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
				{
					//std::cout << "Mouse in No Text" << std::endl;
					_textNo.setFillColor(sf::Color::Yellow);
					_chosenNo = true;
				}
				else
				{
					_textNo.setFillColor(sf::Color::White);
					_chosenNo = false;
				}
			}
		}
	}

	void GameOverWindow::Update(float dt)
	{
		_data->window.draw(_textNo);
		_data->window.draw(_textYes);
	}
	void GameOverWindow::Draw(float dt)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_title);
		_data->window.draw(_textScore);
		_data->window.draw(_textTryAgain);
		_data->window.draw(_textNo);
		_data->window.draw(_textYes);
		_data->window.display();
	}
}