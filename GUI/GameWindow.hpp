#pragma once

#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Game.hpp"
#include "../Managers/EnemyManager.hpp"
#include "../Entities/Player.hpp"
#include "../Entities/Projectile.hpp"
#include "../include/DEFINITIONS.hpp"
#include "../Managers/ProjectileManager.hpp"
#include "../Managers/ShieldManager.hpp"

#include <sstream>
#include <iostream>
#include <memory>
#include <string>

namespace ms
{
	class GameWindow :public Window
	{
	public:
		GameWindow(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Texture _backgroundTexture;
		sf::Sprite _background;
		sf::Text _textScore;

		sf::Clock _shotDelay;
		sf::Clock _enemyShotDelay;

		EnemyManager* enemyManager;
		Player* player;
		ProjectileManager* projectileManager;
		ShieldManager* shieldManager;
	};
}