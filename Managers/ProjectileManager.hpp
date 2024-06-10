#pragma once

#include "../Entities/Projectile.hpp"
#include "../GUI/Game.hpp"
#include "DEFINITIONS.hpp"


namespace ms
{
	class ProjectileManager
	{
	public:
		ProjectileManager(GameDataRef& _data);

		void MoveProjectiles();

		void DrawProjectiles();

		void Update();

		void Add(Projectile* projectile);

		void RemoveDeadProjectiles();

		void CheckForCollisions(Object& other);

		std::vector<Projectile*> getProjectiles();

	private:
		GameDataRef _data;

		std::vector<Projectile*> _projectiles;
		float _speed = 10;

		sf::Clock _clock;
		sf::Time _gapBetweenSteps;

	};
}