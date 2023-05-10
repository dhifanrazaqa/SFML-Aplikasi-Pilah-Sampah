#include "Game/Enemy.hpp"
#include <iostream>

using namespace std;

Enemy::Enemy(float xpos, float ypos, const sf::Texture &texture, int type) : yvel(5)
{
    Enemy::setPosition(sf::Vector2f(xpos, ypos));
    Enemy::Init(texture);
    m_type = type;
}

Enemy::~Enemy() {

}

void Enemy::Init(const sf::Texture &texture)
{
    m_enemyBody.setTexture(texture);
    m_enemyBody.setScale(3,3);
}

void Enemy::setPosition(const sf::Vector2f pos)
{
    m_enemyBody.setPosition(pos);
}

void Enemy::setOrigin(const sf::Vector2f pos) {
    m_enemyBody.setOrigin(pos);
}

void Enemy::setScale(float x, float y) {
    m_enemyBody.setScale(x, y);
}
const int Enemy::getType() {
    return m_type;
}
const sf::Vector2f& Enemy::getPosition() const {
    return m_enemyBody.getPosition();
}
const sf::FloatRect Enemy::getLocalBounds() const {
    return m_enemyBody.getLocalBounds();
}
const sf::FloatRect Enemy::getGlobalBounds() const {
    return m_enemyBody.getGlobalBounds();
}

void Enemy::Move()
{   
    m_enemyBody.move(0, yvel);
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_enemyBody);
}