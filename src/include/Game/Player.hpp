#pragma once

#include <array>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Player : public sf::Drawable
{
private:
    std::array<sf::Sprite, 3> m_body;

    float xpos;
    float xvel;

public:
    Player();
    ~Player();

    bool moveLeft;
    bool moveRight;

    void Init(const sf::Texture &texturea, const sf::Texture &textureb, const sf::Texture &texturec);

    void setPosition(const sf::Vector2f posa, const sf::Vector2f posb, const sf::Vector2f posc);
    void setOrigin(const sf::Vector2f posa, const sf::Vector2f posb, const sf::Vector2f posc);
    const std::array<sf::Vector2f, 3> getPosition() const;
	const std::array<sf::FloatRect, 3> getLocalBounds() const;

    void Move(const sf::Vector2f &direction);
    void Rotate(bool clockWise);
    std::array<int, 2> IsOn(const sf::Sprite &other) const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};