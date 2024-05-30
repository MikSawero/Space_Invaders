#include "Shield.hpp"

namespace ms
{
	Shield::Shield(sf::Vector2f startingPosition, GameDataRef& data)
		: Object(data), _data(data),
		startingPosition(startingPosition),
		currentState(ShieldState::State1),
		_isAlive(true)
	{
		if (!_data)
		{
			throw std::runtime_error("GameDataRef _data is null in Shield constructor");
		}
		ChangeTexture();
		_shieldSprite.setPosition(startingPosition);
		_size.x = _shieldSprite.getGlobalBounds().width;
		_size.y = _shieldSprite.getGlobalBounds().height;
	}

	sf::Vector2f Shield::GetPosition()
	{
		return _shieldSprite.getPosition();
	}

	void Shield::Draw()
	{
		_data->window.draw(_shieldSprite);
	}

	void Shield::ChangeTexture()
	{
		switch (currentState)
		{
		case ShieldState::State1:
			_shieldSprite.setTexture(_data->assets.GetTexture("Shield1"));
			break;
		case ShieldState::State2:
			_shieldSprite.setTexture(_data->assets.GetTexture("Shield2"));
			break;
		case ShieldState::State3:
			_shieldSprite.setTexture(_data->assets.GetTexture("Shield3"));
			break;
		case ShieldState::State4:
			_shieldSprite.setTexture(_data->assets.GetTexture("Shield4"));
			break;
		case ShieldState::State5:
			_shieldSprite.setTexture(_data->assets.GetTexture("Shield5"));
			break;
		default:
			break;
		}
	}

	void Shield::OnCollision(Object& other)
	{
		switch (currentState)
		{
		case ShieldState::State1:
			currentState = ShieldState::State2;
			break;
		case ShieldState::State2:
			currentState = ShieldState::State3;
			break;
		case ShieldState::State3:
			currentState = ShieldState::State4;
			break;
		case ShieldState::State4:
			currentState = ShieldState::State5;
			break;
		case ShieldState::State5:
			if (Player::_score - 100 < 0)
			{
				Player::_score = 0;
			}
			else Player::_score -= 100;
			_isAlive = false;
			break;
		default:
			break;
		}

		ChangeTexture();
	}
	bool Shield::isAlive()
	{
		return _isAlive;
	}
}