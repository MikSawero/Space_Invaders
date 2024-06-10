#include "EnemyManager.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <random>

namespace ms
{
    EnemyManager::EnemyManager(GameDataRef& data)
        : _gapBetweenSteps(sf::seconds(1.0f)),
        _speed(10),
        _shotDelay(sf::seconds(0.8f)),
        _data(data)
    {
        InitEnemies();
    }

    void EnemyManager::InitEnemies()
    {
        _enemies.clear();
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
            }

            _enemies.push_back(temp);
        }
    }

    void EnemyManager::MoveEnemies()
    {
        float moveDistance = _speed;

        if (_justMovedDown)
        {
            _justMovedDown = false;
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
        else
        {
            bool needToMoveDown = false;

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
        for (size_t i = 0; i < _enemies.size(); ++i)
        {
            auto& enemy_col = _enemies[i];


            DrawEnemyColumn(enemy_col);
        }
    }

    void EnemyManager::DrawEnemyColumn(std::vector<Enemy*>& enemy_rows)
    {
        for (auto& enemy : enemy_rows)
        {
            if (enemy != nullptr && enemy->IsAlive())
            {
                enemy->Draw();
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

    sf::Time EnemyManager::GetShotDelay()
    {
        return _shotDelay;
    }

    void EnemyManager::RemoveDeadEnemies()
    {
        auto isEnemyDead = [this](Enemy* enemy) { 
            if (!enemy->IsAlive() || enemy == nullptr)
            {
                _gapBetweenSteps -= sf::seconds(0.01f);
                _shotDelay -= sf::seconds(0.01f);
                return true;
            }
            return false;
            };

        for (auto& row : _enemies)
        {
            row.erase(std::remove_if(row.begin(), row.end(), isEnemyDead), row.end());
        }
    }
}
