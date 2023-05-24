#include "Game/GamePlay.hpp"
#include "Game/GameOver.hpp"
#include "Game/PauseGame.hpp"

#include <iostream>

using namespace std;

#include <SFML/Window/Event.hpp>

GamePlay::GamePlay(std::shared_ptr<Context> &context)
    : m_context(context),
    m_playerDirection({0.f, 0.f}),
    m_elapsedTime(sf::Time::Zero),
    m_score(0),
    m_isPaused(false),
    m_hp(100)
{
    srand(time(nullptr));
}

GamePlay::~GamePlay() {

}

void GamePlay::Init()
{
    m_context->m_assets->AddTexture(PLAYER_ORGANIK, "../../assets/textures/Organik.png");
    m_context->m_assets->AddTexture(PLAYER_ANORGANIK, "../../assets/textures/Anorganik.png");
    m_context->m_assets->AddTexture(PLAYER_B3, "../../assets/textures/B3.png");
    m_context->m_assets->AddTexture(GAME_BG, "../../assets/textures/game-bg.jpg");
    m_context->m_assets->AddTexture(FOOD, "../../assets/textures/food.png");

    m_player.Init(
        m_context->m_assets->GetTexture(PLAYER_ORGANIK),
        m_context->m_assets->GetTexture(PLAYER_ANORGANIK),
        m_context->m_assets->GetTexture(PLAYER_B3));
    m_player.setPosition(
        sf::Vector2f(m_context->width / 2, m_context->height - 100.0f),
        sf::Vector2f(m_context->width / 2 + 50.f, m_context->height - 60.0f),
        sf::Vector2f(m_context->width / 2 - 50.f, m_context->height - 60.0f));
    m_player.setOrigin(
        sf::Vector2f(m_player.getLocalBounds()[0].width / 2, m_player.getLocalBounds()[0].height / 2),
        sf::Vector2f(m_player.getLocalBounds()[1].width / 2, m_player.getLocalBounds()[1].height / 2),
        sf::Vector2f(m_player.getLocalBounds()[2].width / 2, m_player.getLocalBounds()[2].height / 2));

    m_bg.setTexture(m_context->m_assets->GetTexture(GAME_BG));
    m_bg.setOrigin(
        m_bg.getLocalBounds().width / 2,
        m_bg.getLocalBounds().height / 2);
    m_bg.setPosition(
        m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2);
    m_bg.setScale(0.25,0.25);

    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreText.setString("Score : " + std::to_string(m_score));
    m_scoreText.setCharacterSize(25);

    m_hpText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_hpText.setString("HP : " + std::to_string(m_hp));
    m_hpText.setCharacterSize(25);
    m_hpText.setPosition(0, 50);

    m_context->m_window->setFramerateLimit(60);
}
void GamePlay::ProcessInput()
{
    sf::Event event;
    float x = m_player.getPosition()[0].x;
    cout << x << endl;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Q:
                m_player.Rotate(false);
                break;
            case sf::Keyboard::E:
                m_player.Rotate(true);
                break;
            case sf::Keyboard::A:
                if(x == 240 || x == 190 || x == 290 
                || x == 400 || x == 350 || x == 450)
                {
                    m_playerDirection = {-160.f, 0.f};
                }
                break;
            case sf::Keyboard::D:
                if(x == 240 || x == 190 || x == 290 
                || x == 80 || x == 30 || x == 130)
                {
                    m_playerDirection = {160.f, 0.f};
                }
                break;
            default:
                break;
            }
        }
    }
}
void GamePlay::Update(sf::Time deltaTime)
{
    m_player.Move(m_playerDirection);
    m_playerDirection = {0.f, 0.f};

    if(m_hp <= 0) {
        m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
    }

    unsigned counter = 0;
    
    for(auto& sampah : m_sampah)
    {
        if(m_player.IsOn(sampah.m_enemyBody)[0]) {
            cout << m_player.IsOn(sampah.m_enemyBody)[1] << " " << sampah.getType() << endl;
            if(sampah.getType() == m_player.IsOn(sampah.m_enemyBody)[1]) {
                m_score += 5;
                m_scoreText.setString("Score : " + std::to_string(m_score));
            } else {
                m_score -= 1;
                m_scoreText.setString("Score : " + std::to_string(m_score));
            }
            m_sampah.erase(m_sampah.begin() + counter);
        }
        if(sampah.getPosition().y > 750) {
            m_sampah.erase(m_sampah.begin() + counter);
            m_hp -= 5;
            m_hpText.setString("HP : " + std::to_string(m_hp));
        }
        ++counter;
        sampah.Move();
    }
    
    m_elapsedTime += deltaTime;
    if(m_elapsedTime.asSeconds() > 2 - spawnTime) {
        if(spawnTime < 1.25) {
            spawnTime += 0.1;
        }
        int food = 6 + (rand() % ( 8 - 6 + 1 ) );
        m_sampah.push_back(Enemy(m_path[0 + (rand() % 3)], -10.f, m_context->m_assets->GetTexture(food), food));
        for(auto& sampah : m_sampah)
        {
            sampah.setOrigin(sf::Vector2f(sampah.getLocalBounds().width / 2,
                    sampah.getLocalBounds().height / 2));
            sampah.setScale(2,2);
        }

        m_elapsedTime = sf::Time::Zero;
    }
}
void GamePlay::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_bg);
    m_context->m_window->draw(m_player);
    for(auto &sampah : m_sampah)
    {
        m_context->m_window->draw(sampah);
    }
    m_context->m_window->draw(m_scoreText);
    m_context->m_window->draw(m_hpText);
    
    m_context->m_window->display();
}
void GamePlay::Pause()
{
    m_isPaused = true;
}
void GamePlay::Start()
{
    m_isPaused = false;
}