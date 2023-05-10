#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Enemy : public sf::Drawable
{
private:

    float yvel;

public:
    Enemy(float xpos, float ypos, const sf::Texture &texture, int type);
    ~Enemy();

    sf::Sprite m_enemyBody;

    int m_type;
    
    void Init(const sf::Texture &texture);

    void setPosition(const sf::Vector2f pos);
    void setOrigin(const sf::Vector2f pos);
    void setScale(float x, float y);

    const int getType();
    const sf::Vector2f& getPosition() const;
    const sf::FloatRect getLocalBounds() const;
    const sf::FloatRect getGlobalBounds() const;

    void Move();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};