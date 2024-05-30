#pragma once
#include "Object.hpp"
#include "DEFINITIONS.hpp"
#include "Player.hpp"

namespace ms
{
    class Enemy : public Object
    {
    public:
        Enemy(sf::Vector2f startingPosition, GameDataRef data);
        virtual ~Enemy() {};

        sf::Vector2f GetPosition();
        bool IsAlive() const;

        void Draw() override;
        void Move(float x, float y) override;

        void OnCollision(Object& other) override;

        void MakeAlive();

        Enemy& operator=(const Enemy& b);

    private:

        GameDataRef _data;
        sf::Sprite _enemySprite;

        const sf::Vector2f startingPosition;

        bool _isAlive;
    };
}
