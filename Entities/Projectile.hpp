#pragma once

#include "Object.hpp"

namespace ms
{
	class Projectile : public Object
	{
	public:

		Projectile(GameDataRef& _data, sf::Vector2f startingPosition, bool reversed);
		~Projectile() {};
		void Draw() override;
		void Move(float x, float y) override;
		void OnCollision(Object& other) override;
		bool IsAlive();

		sf::Vector2f GetPosition() override;

	private:

		bool _isAlive = true;
		GameDataRef _data;
		float speed = 5;

		sf::Vector2f position;
		sf::Sprite _projectile;

		sf::Clock _clock;
		sf::Time _gapBetweenSteps;
	};
}