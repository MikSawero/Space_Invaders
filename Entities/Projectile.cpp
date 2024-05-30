#include "Projectile.hpp"

namespace ms
{
	Projectile::Projectile(GameDataRef& _data, sf::Vector2f startingPosition, bool reversed)
		: Object(_data),
		position(startingPosition),
		_data(_data), 
		_gapBetweenSteps(sf::seconds(0.01f))
	{
		_projectile.setTexture(_data->assets.GetTexture("Projectile"));
		if (reversed)
		{
			_projectile.setRotation(180.0f);
			speed = -speed;
		}
		_projectile.setPosition(
			startingPosition.x + _projectile.getGlobalBounds().width/2,
			startingPosition.y);
		_size = { _projectile.getGlobalBounds().width, _projectile.getGlobalBounds().height };
	}

	void Projectile::Draw()
	{
		_data->window.draw(_projectile);
	}

	void Projectile::Move(float x = 0, float y = 0)
	{
		position.y -= speed;
		_projectile.setPosition(position);
		position = _projectile.getPosition();
	}

	void Projectile::OnCollision(Object& other)
	{
		_isAlive = false;
	}

	sf::Vector2f Projectile::GetPosition()
	{
		return _projectile.getPosition();
	}


	bool Projectile::IsAlive()
	{
		return _isAlive;
	}
}