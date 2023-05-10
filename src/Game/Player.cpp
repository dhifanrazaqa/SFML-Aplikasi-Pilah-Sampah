#include "Game/Player.hpp"
#include <iostream>

#include <array>
using namespace std;

Player::Player() : xvel(240)
{
}

Player::~Player() {

}

void Player::Init(const sf::Texture &texturea, const sf::Texture &textureb, const sf::Texture &texturec)
{
    m_body[0].setTexture(texturea);
    m_body[0].setScale(3,3);

    m_body[1].setTexture(textureb);
    m_body[1].setScale(3,3);

    m_body[2].setTexture(texturec);
    m_body[2].setScale(3,3);
}

void Player::setPosition(const sf::Vector2f posa, const sf::Vector2f posb, const sf::Vector2f posc)
{
    m_body[0].setPosition(posa);
    m_body[1].setPosition(posb);
    m_body[2].setPosition(posc);
}

void Player::setOrigin(const sf::Vector2f posa, const sf::Vector2f posb, const sf::Vector2f posc) {
    m_body[0].setOrigin(posa);
    m_body[1].setOrigin(posb);
    m_body[2].setOrigin(posc);
}

const std::array<sf::Vector2f, 3> Player::getPosition() const {
    return {m_body[0].getPosition(), m_body[1].getPosition(), m_body[2].getPosition()};
}
const std::array<sf::FloatRect, 3> Player::getLocalBounds() const {
    return {m_body[0].getLocalBounds(), m_body[1].getLocalBounds(), m_body[2].getLocalBounds()};
}

void Player::Move(const sf::Vector2f &direction)
{   
    m_body[0].setPosition(m_body[0].getPosition() + direction);
    m_body[1].setPosition(m_body[1].getPosition() + direction);
    m_body[2].setPosition(m_body[2].getPosition() + direction);
}

void Player::Rotate(bool clockWise)
{   
    cout << m_body[0].getPosition().x << endl;
    cout << m_body[1].getPosition().x << endl;
    cout << m_body[2].getPosition().x << endl;
    sf::Vector2f temp;
    if(clockWise) {
        temp = m_body[0].getPosition();
        m_body[0].setPosition(m_body[1].getPosition());
        m_body[1].setPosition(m_body[2].getPosition());
        m_body[2].setPosition(temp);
    } 
    else {
        temp = m_body[0].getPosition();
        m_body[0].setPosition(m_body[2].getPosition());
        m_body[2].setPosition(m_body[1].getPosition());
        m_body[1].setPosition(temp);
    }
}

std::array<int, 2> Player::IsOn(const sf::Sprite &other) const
{   
    unsigned counter = 6;
    for (auto &body : m_body)
    {
        bool on = other.getGlobalBounds().intersects(body.getGlobalBounds());
        if(on) return {on, counter};
        ++counter;
    }
    return {false, 0};
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{   
    for (auto &body : m_body)
    {
        target.draw(body);
    }
}