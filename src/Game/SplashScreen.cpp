#include "Game/SplashScreen.hpp"
#include "Game/MainMenu.hpp"

#include <SFML/Window/Event.hpp>

SplashScreen::SplashScreen(std::shared_ptr<Context> &context)
    : m_context(context),
    m_isBlinked(false),
    m_elapsedTime(sf::Time::Zero)
{
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::Init()
{
    m_context->m_assets->AddFont(SPLASH_FONT, "../../assets/fonts/Best Wishes.ttf");
    m_context->m_assets->AddTexture(SPLASH_SCREEN, "../../assets/textures/splashScreen.png");

    // Enter Button
    m_pressEnter.setFont(m_context->m_assets->GetFont(SPLASH_FONT));
    m_pressEnter.setString("Press Enter");
    m_pressEnter.setOrigin(m_pressEnter.getLocalBounds().width / 2,
                            m_pressEnter.getLocalBounds().height / 2);
    m_pressEnter.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2 + 50.f);

    // Splash Screen
    m_splashScreen.setTexture(m_context->m_assets->GetTexture(SPLASH_SCREEN));
    m_splashScreen.setPosition(0, 0);
    m_splashScreen.setOrigin(m_splashScreen.getLocalBounds().width / 2,
                            m_splashScreen.getLocalBounds().height / 2);
    m_splashScreen.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2);
    m_splashScreen.setScale(2,2);
      
}

void SplashScreen::ProcessInput()
{
    sf::Event event;
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
            case sf::Keyboard::Return:
            {
              m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
              break;
            }
            default:
            {
              break;
            }
            }
        }
    }
}

void SplashScreen::Update(sf::Time deltaTime)
{
  m_elapsedTime += deltaTime;

  if(m_elapsedTime.asSeconds() > 0.5) {
    if(!m_isBlinked) {
      m_pressEnter.setFillColor(sf::Color::Black);
      m_isBlinked = true;
    } else {
      m_pressEnter.setFillColor(sf::Color::White);
      m_isBlinked = false;
    }
    m_elapsedTime = sf::Time::Zero;
  }
}

void SplashScreen::Draw()
{
    m_context->m_window->clear(sf::Color::Blue);
    m_context->m_window->draw(m_splashScreen);
    m_context->m_window->draw(m_pressEnter);
    m_context->m_window->display();
}