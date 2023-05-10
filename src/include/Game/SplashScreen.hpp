#pragma once

#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"

class SplashScreen : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_pressEnter;
    sf::Sprite m_splashScreen;
    sf::Time m_elapsedTime;

    bool m_isBlinked;


public:
    SplashScreen(std::shared_ptr<Context> &context);
    ~SplashScreen();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
};