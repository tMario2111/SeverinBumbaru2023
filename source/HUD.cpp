#include "HUD.hpp"

HUD::HUD(sf::RenderWindow& win, mke::AssetManager& assets, Fibonacci& fibonacci) :
    win{ win },
    assets{ assets },
    fibonacci{ fibonacci }
{
    sequence.setFont(assets.getFont("font"));
    sequence.setCharacterSize(30);

    score.setFont(assets.getFont("font"));
    score.setCharacterSize(30);
}

void HUD::setScore(int score)
{
    int a1 = fibonacci.seq[score + 1];
    int a2 = fibonacci.seq[score + 2];
    sequence.setString(std::string{ std::to_string(a1) + ", " + std::to_string(a2) + ", " + "[?]" });

    this->score.setString(std::to_string(score));
}

void HUD::render()
{
    const auto original_view = win.getView();

    win.setView(sf::View{
        sf::FloatRect{ 0.f, 0.f, static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y) }});

    mke::centerTextXY(sequence, 0.f, static_cast<float>(win.getSize().x), 0.f, 100.f);
    win.draw(sequence);

    score.setPosition(15.f, 15.f);
    win.draw(score);

    win.setView(original_view);
}