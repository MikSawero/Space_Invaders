#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include "../GUI/Game.hpp"
#include "ProjectileManager.hpp"
#include "../Entities/Enemy.hpp"

namespace ms
{
	class EnemyManager
	{
	public:
		friend class Enemy;

		EnemyManager(GameDataRef& _data);

		void MoveEnemies();

		void DrawEnemyRow();

		void Update();

		Enemy* GetRandomBottomEnemy();

		int GetRandomColumn();

		void Shot(ProjectileManager* _projectileManager);
	
		int GetEnemiesLeft();

		void RemoveDeadEnemies();

		void CheckForCollisions(Object& other);

		std::vector<std::vector<Enemy*>> GetEnemies(); 

	private:

		sf::Sprite template_enemy;

		int enemy_row = 4;
		int enemy_col = 10;

		std::vector<std::vector<Enemy*>> _enemies;
		float _speed = 10;
		GameDataRef _data;

		sf::Clock _clock;
		sf::Time _gapBetweenSteps;

		bool _movingRight;
		bool _justMovedDown;

		void InitEnemies();

		void DrawEnemyColumn(std::vector<Enemy*>& enemy_row);
	};
}