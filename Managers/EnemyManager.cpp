#include "EnemyManager.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <random>

namespace ms
{
    EnemyManager::EnemyManager(GameDataRef& data)
        : _gapBetweenSteps(sf::seconds(0.5f)),
        _data(data)
    {
        if (!_data)
        {
            throw std::runtime_error("GameDataRef _data is null in EnemyManager constructor");
        }

        InitEnemies();
    }

    void EnemyManager::InitEnemies()
    {
        sf::Vector2f EnemyPos;
        template_enemy.setTexture(_data->assets.GetTexture("Enemy"));
        int GAP = 25;

        for (int x = 0; x < enemy_col; ++x)
        {
            std::vector<Enemy*> temp;

            for (int y = 0; y < enemy_row; ++y)
            {
                EnemyPos.x = x * template_enemy.getGlobalBounds().width + (GAP * x * 2) + template_enemy.getGlobalBounds().width;
                EnemyPos.y = y * template_enemy.getGlobalBounds().height + (GAP * y) + template_enemy.getGlobalBounds().height * 2;

                temp.push_back(new Enemy(EnemyPos, _data));
                //std::cout << "Enemy Added at (" << EnemyPos.x << ", " << EnemyPos.y << ")" << std::endl;
            }

            _enemies.push_back(temp);
        }

    }

    void EnemyManager::MoveEnemies()
    {
        float moveDistance = _speed;

        if (_justMovedDown)
        {
            // Reset the flag for moving down
            _justMovedDown = false;

            // Determine horizontal move direction
            if (!_movingRight)
            {
                moveDistance = -moveDistance;
            }

            // Move all enemies horizontally
            for (auto& enemy_row : _enemies)
            {
                for (auto& enemy : enemy_row)
                {
                    if (enemy != nullptr)
                    {
                        enemy->Move(moveDistance, 0);
                    }
                }
            }
        }
        else
        {
            bool needToMoveDown = false;

            // Check if any enemy hits the edge of the screen
            for (auto& enemy_row : _enemies)
            {
                for (auto& enemy : enemy_row)
                {
                    if (enemy != nullptr)
                    {
                        if (enemy->GetPosition().x <= _speed * 2 ||
                            enemy->GetPosition().x + enemy->GetBox().width >= _data->window.getSize().x - _speed * 2)
                        {
                            needToMoveDown = true;
                            _movingRight = !_movingRight;
                            break;
                        }
                    }
                }
                if (needToMoveDown)
                {
                    break;
                }
            }

            if (needToMoveDown)
            {
                // Move all enemies downwards
                for (auto& enemy_row : _enemies)
                {
                    for (auto& enemy : enemy_row)
                    {
                        if (enemy != nullptr)
                        {
                            enemy->Move(0, enemy->GetBox().height);
                        }
                    }
                }
                _justMovedDown = true;
            }
            else
            {
                // Move all enemies horizontally
                if (!_movingRight)
                {
                    moveDistance = -moveDistance;
                }

                for (auto& enemy_row : _enemies)
                {
                    for (auto& enemy : enemy_row)
                    {
                        if (enemy != nullptr)
                        {
                            enemy->Move(moveDistance, 0);
                        }
                    }
                }
            }
        }
    }

    void EnemyManager::DrawEnemyRow()
    {
        if (_enemies.empty())
        {
            std::cout << "_enemies is empty." << std::endl;
            return;
        }

        for (size_t i = 0; i < _enemies.size(); ++i)
        {
            auto& enemy_col = _enemies[i];


            DrawEnemyColumn(enemy_col);
        }
    }

    void EnemyManager::DrawEnemyColumn(std::vector<Enemy*>& enemy_rows)
    {
        if (enemy_rows.empty()) {
            std::cerr << "enemy_row is empty." << std::endl;
            return;
        }

        for (auto& enemy : enemy_rows)
        {
            if (enemy != nullptr && enemy->IsAlive())
            {
                try {
                    enemy->Draw();
                }
                catch (const std::runtime_error& e) {
                    std::cerr << "Failed to draw Enemy: " << e.what() << std::endl;
                    throw;
                }
            }
        }
    }

    void EnemyManager::Update()
    {
        if (_clock.getElapsedTime() >= _gapBetweenSteps)
        {
            MoveEnemies();
            _clock.restart();
        }
    }

    Enemy* EnemyManager::GetRandomBottomEnemy()
    {
        int randcol = GetRandomColumn();
        std::cout << _enemies.at(randcol).back();
        return _enemies.at(GetRandomColumn()).back();
    }

    int EnemyManager::GetRandomColumn()
    {
        unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed1);
        std::uniform_int_distribution<int> distribution(0, enemy_col - 1);
        int randcol = distribution(generator);
        while (_enemies.at(randcol).empty())
        {
           randcol =  distribution(generator);
        }
        
        return randcol;
    }

    void EnemyManager::Shot(ProjectileManager* _projectileManager)
    {
        Enemy* randomBottomEnemy = GetRandomBottomEnemy();

        if (randomBottomEnemy)
        {
            _projectileManager->Add(new Projectile(_data,
                {
                    randomBottomEnemy->GetPosition().x + template_enemy.getGlobalBounds().width/2,
                    randomBottomEnemy->GetPosition().y + 35
                }, 1));
        }
    }

    int EnemyManager::GetEnemiesLeft()
    {
        int total = 0;
        for (auto& enemies_col : _enemies)
        {
            total += enemies_col.size();
        }
        return total;
    }

    void EnemyManager::CheckForCollisions(Object& other)
    {
        for (auto& enemy_row : _enemies)
        {
            for (auto& enemy : enemy_row)
            {
                enemy->CheckCollision(other);
            }
        }
    }

    std::vector<std::vector<Enemy*>> EnemyManager::GetEnemies()
    {
        return _enemies;
    }

    void EnemyManager::RemoveDeadEnemies()
    {
        auto isEnemyDead = [](Enemy* enemy) { return enemy == nullptr || !enemy->IsAlive(); };

        for (auto& row : _enemies)
        {
            row.erase(std::remove_if(row.begin(), row.end(), isEnemyDead), row.end());
        }
    }
}
