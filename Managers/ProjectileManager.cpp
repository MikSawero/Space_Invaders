#include "ProjectileManager.hpp"

namespace ms
{
	ProjectileManager::ProjectileManager(GameDataRef& _data)
		: _gapBetweenSteps(sf::seconds(0.01f)),
		_data(_data)
	{

	}

	void ProjectileManager::MoveProjectiles()
	{
		float moveDistance = _speed;

		for (auto& projectile : _projectiles)
		{
			projectile->Move(moveDistance, 0);
		}

	}

	void ProjectileManager::DrawProjectiles()
	{
		for (auto& projectile : _projectiles)
		{
			if (projectile->IsAlive())
			{
				try {
					projectile->Draw();
				}
				catch (const std::runtime_error& e) {
					std::cerr << "Failed to draw Projectile: " << e.what() << std::endl;
					throw;
				}
			}
		}
	}

	void ProjectileManager::Update()
	{
		if (_clock.getElapsedTime() >= _gapBetweenSteps)
		{
			MoveProjectiles();
			_clock.restart();
		}

		//std::cout << _enemies[0].GetPosition().x << std::endl;
	}

	void ProjectileManager::Add(Projectile* projectile)
	{
		_projectiles.push_back(projectile);
	}

	void ProjectileManager::CheckForCollisions(Object& other)
	{
		for (auto& projectile : _projectiles)
		{
			projectile->CheckCollision(other);
		}
	}

	std::vector<Projectile*> ProjectileManager::getProjectiles()
	{
		return _projectiles;
	}

	void ProjectileManager::RemoveDeadProjectiles()
	{
		_projectiles.erase(std::remove_if(_projectiles.begin(), _projectiles.end(),
			[](Projectile* projectile) { return !projectile->IsAlive(); }),
			_projectiles.end());
	}
}