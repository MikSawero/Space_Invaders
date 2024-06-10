#include "LeaderboardWindow.hpp"

namespace ms
{
	LeaderboardWindow::LeaderboardWindow(GameDataRef data) : _data(data)
	{

	}

	void LeaderboardWindow::Init()
	{
		std::cout << "Leaderboard State Initialization\n";

		_background.setTexture(this->_data->assets.GetTexture("Game Background"));

		_backToMenu.setFont(_data->assets.GetFont("Font"));
		_backToMenu.setCharacterSize(26);
		_backToMenu.setString("Back To Menu");
		_backToMenu.setPosition( 10, 10);

		_leaderboardLabel.setFont(_data->assets.GetFont("Font"));
		_leaderboardLabel.setCharacterSize(40);
		_leaderboardLabel.setString("Top 5 Scores");
		_leaderboardLabel.setPosition(SCREEN_WIDTH/2 - _leaderboardLabel.getGlobalBounds().width/2,
			100);

		FileManager::FileManager();

		std::ranges::sort(FileManager::scores, [](const info& a, const info& b)
			{
				if (a.score != b.score)
					return a.score > b.score;
				if (a.date != b.date)
					return a.date > b.date;
			}
		);

		auto top5 = FileManager::scores | std::views::take(5);

		float pos = 200.0f;
		std::vector<sf::Text> _oneScore;
		for (auto _text : top5)
		{
			_oneScore.clear();
			sf::Text text1, text2, text3;
			text1.setFont(_data->assets.GetFont("Font"));
			text2.setFont(_data->assets.GetFont("Font"));
			text3.setFont(_data->assets.GetFont("Font"));
			text1.setCharacterSize(26);
			text2.setCharacterSize(26);
			text3.setCharacterSize(26);
			
			text1.setString(_text.name);
			text2.setString(std::to_string(_text.score));
			text3.setString(_text.date);

			text1.setPosition(SCREEN_WIDTH / 2 - 350.0f,
				pos);
			text2.setPosition(SCREEN_WIDTH / 2 - 100.0f,
				pos);
			text3.setPosition(SCREEN_WIDTH / 2 + 150.0f,
				pos);
			
			_oneScore.push_back(text1);
			_oneScore.push_back(text2);
			_oneScore.push_back(text3);
			_showingScores.push_back(_oneScore);
			pos += 100;
		}


	}

	void LeaderboardWindow::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}

			if ((event.type == sf::Event::MouseButtonPressed
				|| event.key.scancode == sf::Keyboard::Scan::Enter)
				&& _chosenBackToMenu == true)
			{
				_data->machine.RemoveState();
				_data->machine.AddState(StateRef(new MainMenuWindow(_data)), true);
				FileManager::scores.clear();
			}
			if (event.type == sf::Event::MouseMoved)
			{
				if (_backToMenu.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
				{
					_backToMenu.setFillColor(sf::Color::Yellow);
					_chosenBackToMenu = true;
				}
				else
				{
					_backToMenu.setFillColor(sf::Color::White);
					_chosenBackToMenu = false;
				}
			}
			if (sf::Event::KeyPressed == event.type
				&& event.key.scancode == sf::Keyboard::Scan::Left)
			{
				//std::cout << "Up Arrow Key Pressed" << std::endl;
				_backToMenu.setFillColor(sf::Color::Yellow);
				_chosenBackToMenu = true;
			}
		}
	}

	void LeaderboardWindow::Update(float dt)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_backToMenu);
		_data->window.draw(_leaderboardLabel);
		for (const auto score : _showingScores)
		{
			for (const auto text : score)
			{
				_data->window.draw(text);
			}
		}
		_data->window.display();
	}

	void LeaderboardWindow::Draw(float dt)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_backToMenu);
		_data->window.draw(_leaderboardLabel);
		for (const auto score : _showingScores)
		{
			for (const auto text : score)
			{
				_data->window.draw(text);
			}
		}
		_data->window.display();
	}
}