#pragma once

#include "Object.hpp"
#include "Player.hpp"

namespace ms
{
	enum class ShieldState
	{
		State1,
		State2,
		State3,
		State4,
		State5
	};
	class Shield : public Object
	{
	public:
		Shield(sf::Vector2f startingPosition, GameDataRef& data);
		~Shield() {};

		sf::Vector2f GetPosition() override;
		void Draw() override;
		void Move(float x, float y) {};
		
		void ChangeTexture();
		void OnCollision(Object& other) override;

		bool isAlive();
	private:
		sf::Vector2f startingPosition;
		GameDataRef& _data;

		ShieldState currentState;
		sf::Sprite _shieldSprite;
		bool _isAlive;
	};
}