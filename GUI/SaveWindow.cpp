#include "SaveWindow.hpp"

namespace ms
{
	SaveWindow::SaveWindow(GameDataRef data) : _data(data)
	{

	}
	void SaveWindow::Init()
	{
		std::cout << "Save Window Initialization\n";

		_background.setTexture(this->_data->assets.GetTexture("Game Background"));

		_textQuestion.setFont(_data->assets.GetFont("Font"));
		_textQuestion.setCharacterSize(32);
		_textQuestion.setString("What`s your name?");
		_textQuestion.setPosition(SCREEN_WIDTH / 2 - _textQuestion.getGlobalBounds().width / 2,
			SCREEN_LENGTH / 2 - 200);

		_textName.setFont(_data->assets.GetFont("Font"));
		_textName.setCharacterSize(32);
		_textName.setPosition(SCREEN_WIDTH / 2 - _textName.getGlobalBounds().width / 2,
			SCREEN_LENGTH / 2 - 100 );


		_textEnter.setFont(_data->assets.GetFont("Font"));
		_textEnter.setCharacterSize(32);
		_textEnter.setString("(Press Enter to Save)");
		_textEnter.setPosition((SCREEN_WIDTH - _textEnter.getGlobalBounds().width) / 2,
			SCREEN_LENGTH / 2 + 100);

		FileManager::FileManager();

		_text = _textName.getString();

		allowed_chars = "[A-Za-z0-9]+";
	}

	void SaveWindow::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}

			if (event.type == sf::Event::TextEntered && event.key.code != sf::Keyboard::Space) {
				if (event.text.unicode < 128) {
					char enteredChar = static_cast<char>(event.text.unicode);
					if (enteredChar == '\b')
					{
						_inputError = 0;
						if (!_text.empty())
						{
							_text.pop_back();
							_textName.setString(_text);
							_textName.setPosition(SCREEN_WIDTH / 2 - _textName.getGlobalBounds().width / 2,
								SCREEN_LENGTH / 2 - 100);
							std::cout << _text << std::endl;
						}
					}
					else if (_text.size() <= 10) {
						_text.push_back(enteredChar);
						_textName.setString(_text);
						_textName.setPosition(SCREEN_WIDTH / 2 - _textName.getGlobalBounds().width / 2,
							SCREEN_LENGTH / 2 - 100);
					}
				}
			}

			if (event.key.code == sf::Keyboard::Enter && _text.size() > 0) {
				if (std::regex_match(_text, allowed_chars))
				{
					int score = Player::_score;
					std::string text = _textName.getString();

					std::cout << text << " : " << score << std::endl;

					FileManager::SaveScore(text, score);

					_data->machine.RemoveState();
					_data->machine.AddState(StateRef(new MainMenuWindow(_data)), true);
					FileManager::scores.clear();
				}
				else
				{
					_inputErrorText.setFont(_data->assets.GetFont("Font"));
					_inputErrorText.setFillColor(sf::Color::Red);
					_inputErrorText.setCharacterSize(24);
					_inputErrorText.setString("You can only input letters A-Z and numbers 0-9!");
					_inputErrorText.setPosition(SCREEN_WIDTH / 2 - _inputErrorText.getGlobalBounds().width / 2,
						SCREEN_LENGTH / 2);
					_inputError = 1;
					_text.clear();
				}
			}
		}
	}

	void SaveWindow::Update(float dt)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_title);
		_data->window.draw(_textQuestion);
		_data->window.draw(_textName);
		_data->window.draw(_textEnter);
		if (_inputError)
		{
			_data->window.draw(_inputErrorText);
		}
		_data->window.display();
	}
	void SaveWindow::Draw(float dt)
	{
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.draw(_title);
		_data->window.draw(_textQuestion);
		_data->window.draw(_textName);
		_data->window.draw(_textEnter);
		if (_inputError)
		{
			_data->window.draw(_inputErrorText);
		}
		_data->window.display();
	}
}