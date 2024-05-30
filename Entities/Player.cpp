#include "Player.hpp"

namespace ms
{
	int Player::_score = 0;

	Player::Player(GameDataRef& _data)
		: Object(_data),
		_data(_data)
	{
		_player.setTexture(_data->assets.GetTexture("Player"));
		
		position = { (_data->window.getSize().x - _player.getGlobalBounds().width) / 2,
			_data->window.getSize().y - _player_y_level };

		_player.setPosition(position.x, position.y);
		_size.x = _player.getGlobalBounds().width;
		_size.y = _player.getGlobalBounds().height;

	}

	void Player::Draw()
	{
		_data->window.draw(_player);
	}

	void Player::Move(float x, float y)
	{
		if (position.x + x >= 0
			&& position.x + x + _player.getGlobalBounds().width <= SCREEN_WIDTH)
		{
			_player.setPosition(position.x + x, position.y);
			position = _player.getPosition();
		}
	}

	sf::Vector2f Player::GetPosition()
	{
		return _player.getPosition();
	}
	void Player::Restart()
	{
		if (_lives > 0)
		{
			_isAlive = true;
		}
		_lives--;
		if (Player::_score - 1000 < 0)
		{
			Player::_score = 0;
		}
		else _score -= 1000;
		position = { (_data->window.getSize().x - _player.getGlobalBounds().width) / 2,
			_data->window.getSize().y - _player_y_level };
		_player.setPosition(position);
	}

	void Player::OnCollision(Object& other)
	{
		Restart();
	}

	int Player::GetLives()
	{
		return _lives;
	}
	bool Player::IsAlive()
	{
		return _isAlive;
	}
	
	int Player::GetScore()
	{
		return _score;
	}

}