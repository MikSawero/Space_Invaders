#include "Enemy.hpp"


namespace ms
{
    Enemy::Enemy(sf::Vector2f startingPosition, GameDataRef data)
        : Object(data), _data(data),
        startingPosition(startingPosition)
    {
        if (!_data) {
            throw std::runtime_error("GameDataRef _data is null in Enemy constructor");
        }

        _enemySprite.setTexture(_data->assets.GetTexture("Enemy"));
        _enemySprite.setPosition(startingPosition);
        _size.x = _enemySprite.getGlobalBounds().width;
        _size.y = _enemySprite.getGlobalBounds().height;
        _isAlive = true;
    }

    sf::Vector2f Enemy::GetPosition() {
        return _enemySprite.getPosition();
    }

    bool Enemy::IsAlive() const {
        return _isAlive;
    }

    void Enemy::Draw() {
        if (!_data) {
            throw std::runtime_error("GameDataRef _data is null in Enemy::draw");
        }

        _data->window.draw(_enemySprite);
    }

    void Enemy::Move(float x, float y) {
        _enemySprite.move(x, y);
    }

    void Enemy::OnCollision(Object& other)
    {
        _isAlive = false;
        Player::_score += 100;
    }

    void Enemy::MakeAlive() {
        _isAlive = true;
    }

    Enemy& Enemy::operator=(const Enemy& b)
    {
        return *this;
    }
}
