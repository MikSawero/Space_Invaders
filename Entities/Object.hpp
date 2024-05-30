#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../GUI/Game.hpp"
#include "../include/DEFINITIONS.hpp"

namespace ms
{
	class Object
	{
	public:

		Object(GameDataRef& data);
		virtual ~Object() {};
		bool CheckCollision(Object& other);
		sf::FloatRect GetBox();

		virtual sf::Vector2f GetPosition() = 0;
		virtual void Draw() = 0;
		virtual void Move(float x, float y) = 0;
		virtual void OnCollision(Object& other) = 0;

	protected:
		sf::Vector2f _size;

	private:
		GameDataRef _data;
	};
}
