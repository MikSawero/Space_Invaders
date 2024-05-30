#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../GUI/Game.hpp"
#include "DEFINITIONS.hpp"
#include "Object.hpp"

namespace ms
{
	class Player: public Object
	{
	public:
		Player(GameDataRef& data);
		virtual ~Player() {};

		void Draw() override;
		void Move(float x, float y) override;

		sf::Vector2f GetPosition() override;
		void Restart();

		void OnCollision(Object& other);
		int GetLives();
		bool IsAlive();
		int GetScore();

		static int _score;

	private:
		GameDataRef _data;
		sf::Vector2f position;
		sf::Sprite _player;

		bool _isAlive = true;
		int _lives = 3;

		float _player_y_level = 80.f;
	};
}