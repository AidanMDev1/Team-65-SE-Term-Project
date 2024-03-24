#include <iostream>
#include "UserAccount.h"
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"

// inspired by https://youtu.be/T31MoLJws4U?si=_h8ujkH34nowKIoB


int main() {
    // set up window
    sf::RenderWindow window;
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445,
                              (sf::VideoMode::getDesktopMode().height / 2) - 480);
    window.create(sf::VideoMode(900,900), "QuestClock", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);

    // font
    sf::Font cnr;
    cnr.loadFromFile("Courier New Regular.ttf"); // inside cmake-build-debug in CLion

    // textboxes for login
    Textbox username_tbox(15, sf::Color::White, true);
    // Textbox password_tbox(15, sf::Color::White, true);
    username_tbox.setFont(cnr);
    username_tbox.setPosition({100, 100}); // FIXME: limits need fixing when it comes to deletion

    // login button
    Button login_btn("Login", {200, 50}, 30, sf::Color::White, sf::Color::Black);
    login_btn.setPosition({100, 300});
    login_btn.setFont(cnr);

    // Window loop
    while (window.isOpen()) {
        sf::Event event;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            username_tbox.setSelected(true);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            username_tbox.setSelected(false);
        }

        // event loop
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::TextEntered:
                    username_tbox.typeOn(event);
                    break;
                case sf::Event::MouseMoved:
                    if (login_btn.isMouseOver(window)) {
                        login_btn.setBackColor(sf::Color::Green);
                        login_btn.setTextColor(sf::Color::White);
                    }
                    else {
                        login_btn.setBackColor(sf::Color::White);
                        login_btn.setTextColor(sf::Color::Black);
                    }
            }
        }
        window.clear();

        //draw to window
        username_tbox.drawTo(window);
        login_btn.drawTo(window);
        window.display();
    }

    return 0;
}