//
// Created by xenon on 21.04.23.
//

#include "Window.h"
#include <cmath>

Window::Window(const Config &cfg) : background(cfg.backgroundColor), cellSize(cfg.cellSize),
axesColor(cfg.axesColor), trigonometry(cfg.trigonometry), chartsColor(cfg.chartsColor) {

    this->renderWindow = std::make_shared<sf::RenderWindow>(
            cfg.videoMode,
            cfg.title,
            sf::Style::Default,
            cfg.settings
            );

    this->renderWindow->setFramerateLimit(60);
    this->renderWindow->setVerticalSyncEnabled(true);

    this->camera = std::make_shared<Camera>(sf::Vector2f(0, 0), 1);
    this->camera->setScale(30.f);

    this->loadFont();

}

void Window::loadFont() {

    bool success = this->font.loadFromFile("NotoSansMath-Regular.ttf");

    if(!success)
    {
        Log::errl("[Error] Font load fail");
        exit(EXIT_FAILURE);
    }

}

void Window::init(const std::shared_ptr<Equation>& _equation) {

    this->equaiton = _equation;

    while(renderWindow->isOpen()) {

        sf::Event event{};
        while(renderWindow->pollEvent(event)) {

            this->eventListener(event);
        }

        renderWindow->clear(this->background);

        this->camera->tick();
        this->tick();


        renderWindow->display();

    }

}

void Window::tick() {



/*
 *  Grid
 * */

    sf::Vector2f camPosition = this->camera->getPosition();
    sf::Vector2<unsigned int> windowSize = this->renderWindow->getSize();

    for(int i = -(int) std::ceil(windowSize.x / getCellSize()); i < (int) std::ceil(windowSize.x / getCellSize()); i++)
    {
        sf::Vertex line[] = {
        sf::Vertex(
                sf::Vector2f(i * getCellSize() + fmod(camPosition.x, getCellSize()) + windowSize.x / 2, 0),
                this->axesColor
                ),
        sf::Vertex(
                sf::Vector2f(i * getCellSize() + fmod(camPosition.x, getCellSize()) + windowSize.x / 2, windowSize.y),
                this->axesColor
                )
        };

        this->renderWindow->draw(line, 2, sf::Lines);
    }

    for(int i = -(int) std::ceil( (float) windowSize.y / getCellSize()); i < (int) std::ceil( (float) windowSize.y / getCellSize()); i++ )
    {
        sf::Vertex line[] = {
                sf::Vertex(
                        sf::Vector2f(
                                    0,
                                    i * getCellSize() + windowSize.y / 2  + fmod(camPosition.y, getCellSize())
                                ),
                        this->axesColor
                        ),
                sf::Vertex(
                        sf::Vector2f(
                                    windowSize.x,
                                    i * getCellSize() + windowSize.y / 2  + fmod(camPosition.y, getCellSize())
                                ),
                        this->axesColor
                        )
        };

        this->renderWindow->draw(line, 2, sf::Lines);
    }

    /*
 *  Numbers
 * */

    for(
            int i = -(int) ((float) windowSize.x - this->camera->getRawPosition().x);
            i <= (int) ((float) windowSize.x - this->camera->getRawPosition().x);
            i++
            )
    {
        sf::Text number{"", this->font, (unsigned int) this->camera->getScale() / 4};

        if(this->trigonometry) {
            number.setString(std::to_wstring(i) + L"π");
        }else{
            number.setString(std::to_string((int) (i * this->cellSize)));
        }

        const float x = (float) windowSize.x / 2 + camPosition.x + i * getCellSize() - number.getGlobalBounds().width / 2;
        const float y = (float) windowSize.y / 2 + camPosition.y;

        number.setPosition(sf::Vector2f(x, y));
        number.setFillColor(sf::Color::Black);

        this->renderWindow->draw(number);
    }

    for(
            int i = -(int) ((float) windowSize.y - this->camera->getRawPosition().y);
            i <= (int) ((float) windowSize.y - this->camera->getRawPosition().y);
            i++
            )
    {
        sf::Text number{"", this->font, (unsigned int) this->camera->getScale() / 4};

        if(this->trigonometry) {
            number.setString(std::to_wstring(-i) + L"π");
        }else{
            number.setString(std::to_string((int) (-i * this->cellSize)));
        }

        const float x = (float) windowSize.x / 2 + camPosition.x - number.getGlobalBounds().width * 1.3f;
        const float y = (float) windowSize.y / 2 + camPosition.y + i * getCellSize() - number.getGlobalBounds().height;

        number.setPosition(sf::Vector2f(x, y));
        number.setFillColor(sf::Color::Black);

        if(i != 0) this->renderWindow->draw(number);
    }


/*
 *  Charts
 * */

    this->renderCharts();






/*
 * Axes
 * */

    {
        const auto x = (float) windowSize.x;
        const float y = (float) windowSize.y / 2 + camPosition.y;

        sf::Vertex line[] = {
                sf::Vertex(
                        sf::Vector2f(
                                0,
                                y
                                ),
                                sf::Color::Black
                        ),
                sf::Vertex(
                        sf::Vector2f(
                                x,
                                y
                                ),
                                sf::Color::Black
                        ),

        };

        this->renderWindow->draw(line, 2, sf::Lines);
    }
    {
        const float x = (float) windowSize.x / 2 + camPosition.x;
        const auto y = (float) windowSize.y;

        sf::Vertex line[] = {
                sf::Vertex(
                        sf::Vector2f(
                                x,
                                0
                                ),
                                sf::Color::Black
                        ),
                        sf::Vertex(
                        sf::Vector2f(
                                x,
                                y
                                ),
                                sf::Color::Black
                        )
        };

        this->renderWindow->draw(line, 2, sf::Lines);
    }



/*
 *  Log info
 * */

    sf::RectangleShape logBackground{sf::Vector2f(150, 70)};
    logBackground.setFillColor(sf::Color::White);
    sf::Text log;
    log.setFont(this->font);
    log.setString("x: " + std::to_string(this->camera->getRawPosition().x) + "\ny: " + std::to_string(this->camera->getRawPosition().y)
    + "\n" + this->equaiton->getRaw());
    log.setCharacterSize(18);
    log.setFillColor(sf::Color::Black);

    this->renderWindow->draw(logBackground);
    this->renderWindow->draw(log);



}

void Window::renderCharts() {

//    y = x^2

    const sf::Vector2<unsigned int> windowSize = this->renderWindow->getSize();

    float lastX = -(float) windowSize.x / this->camera->getScale() / 2 - this->camera->getRawPosition().x;
    float lastY = -lastX * lastX;

    for(
            float x = -((float) windowSize.x / this->camera->getScale() / 2) - this->camera->getRawPosition().x;
            x <= (float) windowSize.x / this->camera->getScale() / 2 - this->camera->getRawPosition().x;
    )
    {
        x += 0.002;
        float y = -x * x;


        sf::Vertex line[] = {
                sf::Vertex(
                        sf::Vector2f(
                                (float) lastX * this->camera->getScale() + this->camera->getPosition().x + windowSize.x / 2,
                                (float) lastY * this->camera->getScale() + this->camera->getPosition().y + windowSize.y / 2
                                ),
                                this->chartsColor
                        ),
                sf::Vertex(
                        sf::Vector2f(
                                (float) x * this->camera->getScale() + this->camera->getPosition().x + windowSize.x / 2,
                                (float) y * this->camera->getScale() + this->camera->getPosition().y + windowSize.y / 2
                                ),
                                this->chartsColor
                        )

        };

        if(abs(y - lastY) >= 10) {
            lastX = x;
            lastY = y;
            continue;
        }

        lastX = x;
        lastY = y;

        this->renderWindow->draw(line, 2, sf::Lines);

    }


}


void Window::eventListener(const sf::Event &event) {

    if(event.type == sf::Event::Closed) {
        renderWindow->close();
    }

    if(event.type == sf::Event::KeyPressed) {
        if( event.key.code == sf::Keyboard::Escape) {
            this->renderWindow->close();
        }
    }

    if(event.type == sf::Event::MouseButtonPressed) {
        this->camera->setDragged(true);
    }else
    if(event.type == sf::Event::MouseButtonReleased) {
        this->camera->setDragged(false);
    }

    if(event.type == sf::Event::MouseMoved) {

        if(this->camera->isDragged()) {

            sf::Vector2f delta = {
                (float) event.mouseMove.x - this->lastMousePos.x,
                (float) event.mouseMove.y - this->lastMousePos.y
            };

            this->camera->addImpulse(delta.x * 0.002f, delta.y * 0.002f);

            this->camera->setPosition(
                    this->camera->getRawPosition().x + delta.x / this->camera->getScale(),
                    this->camera->getRawPosition().y + delta.y / this->camera->getScale()
                    );
        }

        this->lastMousePos = sf::Vector2f (
                (float) event.mouseMove.x, (float) event.mouseMove.y
                );
    }

    if(event.type == sf::Event::MouseWheelScrolled) {
        if(event.mouseWheelScroll.delta == 1) {
            if(this->camera->getScale() < 500) {
                this->camera->addScaleImpulse(event.mouseWheelScroll.delta);
            }
        }else {
            if(this->camera->getScale() > 5) {
                this->camera->addScaleImpulse(event.mouseWheelScroll.delta);
            }
        }
    }

}

float Window::getCellSize() {
    return this->camera->getScale() * (float) cellSize;
}

std::string Window::input() {

    sf::String playerInput;
    sf::Text playerText;
    playerText.setFont(this->font);
    playerText.setFillColor(sf::Color::Black);

    sf::Text enterText {"Enter equation below", this->font};
    enterText.setFillColor(sf::Color::Black);
    enterText.setPosition(
            (float) this->renderWindow->getSize().x / 2 - enterText.getGlobalBounds().width / 2,
            (float) this->renderWindow->getSize().y / 2 - enterText.getGlobalBounds().height * 2
            );

    sf::RectangleShape caret {sf::Vector2f (2, enterText.getGlobalBounds().height)};
    caret.setFillColor(sf::Color::Black);

    while(this->renderWindow->isOpen()) {

        sf::Event event{};
        bool entered = false;

        while(this->renderWindow->pollEvent(event)) {

            if(event.type == sf::Event::TextEntered) {
                if(event.key.code == 13) {
                    entered = true; break;
                }else if (event.key.code == 8) {
                    if(playerInput.getSize() >= 1)
                        playerInput.erase(playerInput.getSize() - 1, playerInput.getSize());
                }else {
                    playerInput += event.text.unicode;
                }

                playerText.setString(playerInput);
            }else if(event.type == sf::Event::Closed)
                this->renderWindow->close();

        }
        if(entered) break;

        playerText.setPosition(
                (float) this->renderWindow->getSize().x / 2 - playerText.getGlobalBounds().width / 2,
                (float) this->renderWindow->getSize().y / 2 - playerText.getGlobalBounds().height / 2
                );

        caret.setPosition(
                (float) this->renderWindow->getSize().x / 2 + playerText.getGlobalBounds().width / 2,
                (float) this->renderWindow->getSize().y / 2 - playerText.getGlobalBounds().height / 2
                );
        caret.setSize(sf::Vector2f(2, playerText.getGlobalBounds().height));

        this->renderWindow->clear(sf::Color::White);
        this->renderWindow->draw(enterText);
        this->renderWindow->draw(playerText);
        this->renderWindow->draw(caret);
        this->renderWindow->display();

    }

    return std::string(playerInput);
}
