#include "MainMenuWindow.hpp"


namespace ms
{
	MainMenuWindow::MainMenuWindow(GameDataRef data): _data(data)
	{
		
	}

	void MainMenuWindow::Init()
	{
		std::cout << "Main Menu Initialization\n";
		_background.setTexture(this->_data->assets.GetTexture("Game Background"));
		_title.setTexture(this->_data->assets.GetTexture("Game Title"));

		_title.setScale(0.2f, 0.2f);
		
		_textPlay.setFont(_data->assets.GetFont("Font"));
		_textPlay.setCharacterSize(40);
		_textPlay.setString("Play");
		_textPlay.setPosition(SCREEN_WIDTH / 2 - _textPlay.getGlobalBounds().width / 2,
			SCREEN_LENGTH / 2 - 100);

		_textLeaderboard.setFont(_data->assets.GetFont("Font"));
		_textLeaderboard.setCharacterSize(40);
		_textLeaderboard.setString("Leaderboard");
		_textLeaderboard.setPosition(SCREEN_WIDTH / 2 - _textLeaderboard.getGlobalBounds().width / 2,
			SCREEN_LENGTH / 2 );

		_textExit.setFont(_data->assets.GetFont("Font"));
		_textExit.setCharacterSize(40);
		_textExit.setString("Exit");
		_textExit.setPosition(SCREEN_WIDTH / 2 - _textExit.getGlobalBounds().width / 2,
			SCREEN_LENGTH / 2 + 100);
		
		_title.setPosition((SCREEN_WIDTH - _title.getGlobalBounds().width) / 2, _title.getGlobalBounds().height*2);
	}

	void MainMenuWindow::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type 
				|| (event.type == sf::Event::MouseButtonPressed 
					|| event.type == sf::Keyboard::Scan::Enter)
					&& _chosenExit == true)
			{
				_data->window.close();
			}

			if ((event.type == sf::Event::MouseButtonPressed 
				|| event.key.scancode == sf::Keyboard::Scan::Enter)
				&& _chosenPlay == true)
			{
				_data->machine.RemoveState();
				_data->machine.AddState(StateRef(new GameWindow(_data)), true);
			}

			if ((event.type == sf::Event::MouseButtonPressed
				|| event.key.scancode == sf::Keyboard::Scan::Enter)
				&& _chosenLeaderboard == true)
			{
				_data->machine.RemoveState();
				_data->machine.AddState(StateRef(new LeaderboardWindow(_data)), true);
			}
			if (event.type == sf::Event::MouseMoved)
			{
				if (_textExit.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
				{
					//std::cout << "Mouse in Exit Text" << std::endl;
					_textExit.setFillColor(sf::Color::Yellow);
					_chosenExit = true;
				}
				else
				{
					_textExit.setFillColor(sf::Color::White);
					_chosenExit = false;
				}
				
				if (_textLeaderboard.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
				{
					//std::cout << "Mouse in Exit Text" << std::endl;
					_textLeaderboard.setFillColor(sf::Color::Yellow);
					_chosenLeaderboard = true;
				}
				else
				{
					_textLeaderboard.setFillColor(sf::Color::White);
					_chosenLeaderboard = false;
				}

				if (_textPlay.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
				{
					//std::cout << "Mouse in Play Text" << std::endl;
					_textPlay.setFillColor(sf::Color::Yellow);
					_chosenPlay = true;
				}
				else
				{
					_textPlay.setFillColor(sf::Color::White);
					_chosenPlay = false;
				}
			}

			if (sf::Event::KeyPressed == event.type
				&& event.key.scancode == sf::Keyboard::Scan::Up)
			{
				//std::cout << "Up Arrow Key Pressed" << std::endl;
				_textPlay.setFillColor(sf::Color::Yellow);
				_textExit.setFillColor(sf::Color::White);
				_chosenPlay = true;
				_chosenExit = false;
			}

			if (sf::Event::KeyPressed == event.type
				&& event.key.scancode == sf::Keyboard::Scan::Down)
			{
				//std::cout << "Down Arrow Key Pressed" << std::endl;
				_textPlay.setFillColor(sf::Color::White);
				_textExit.setFillColor(sf::Color::Yellow);
				_chosenPlay = false;
				_chosenExit = true;
			}
		}
	}

	void MainMenuWindow::Update(float dt)
	{
		_data->window.draw(_textPlay);
		_data->window.draw(_textExit);
		_data->window.draw(_textLeaderboard);
	}

	void MainMenuWindow::Draw(float dt)
	{
		_data->window.clear();

		_data->window.draw(_background);
		_data->window.draw(_title);
		_data->window.draw(_textPlay);
		_data->window.draw(_textLeaderboard);
		_data->window.draw(_textExit);
	
		_data->window.display();
	}
}
