#include "ShieldManager.hpp"

namespace ms
{
	ShieldManager::ShieldManager(GameDataRef& _data)
		: _data(_data)
	{
		Init();
	}

	void ShieldManager::Init()
	{
		sf::Vector2f tempPosition;
		sf::Sprite shield;
		shield.setTexture(_data->assets.GetTexture("Shield1"));

		for (int i = 0; i < 4; i++)
		{
			tempPosition =
			{
				shield.getGlobalBounds().width + 250.0f*i + shield.getGlobalBounds().height,
				_data->window.getSize().y - 150.0f
			};

			_shields.emplace_back(new Shield(tempPosition, _data));
		}
	}

	void ShieldManager::DrawShields()
	{
		for (auto& shield : _shields)
		{
			if(shield->isAlive())
				shield->Draw();
		}
	}

	void ShieldManager::CheckForCollisions(Object& other)
	{
		for (auto& shield : _shields)
		{
			shield->CheckCollision(other);
		}
	}

	std::vector<Shield*> ShieldManager::getShields()
	{
		return _shields;
	}
	void ShieldManager::RemoveDeadShields()
	{
		_shields.erase(std::remove_if(_shields.begin(), _shields.end(),
			[](Shield* shield) { return !shield->isAlive(); }),
			_shields.end());
	}
}