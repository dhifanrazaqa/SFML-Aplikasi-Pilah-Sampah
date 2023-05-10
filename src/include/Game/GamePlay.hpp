#pragma once

#include <memory>
#include <vector>
#include <array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Game.hpp"
#include "State.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class GamePlay : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    Player m_player;

    std::array<int, 3> m_path = {80, 240, 400};
    std::vector<Enemy> m_sampah;
    sf::Sprite m_bg;

    sf::Text m_scoreText;
    int m_score;
    sf::Text m_hpText;
    int m_hp;
    
    float spawnTime = 0;

    sf::Vector2f m_playerDirection;
    sf::Time m_elapsedTime;

    bool m_isPaused;
public:
    GamePlay(std::shared_ptr<Context> &context);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;
};