#include <iostream>
#include "UserAccount.h"
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"

// inspired by https://youtu.be/T31MoLJws4U?si=_h8ujkH34nowKIoB
#define WIDTH 900 // window width
#define HEIGHT 900 // window height

int main() {
    // LOGIN WINDOW setup
    sf::RenderWindow window;
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445,
                              (sf::VideoMode::getDesktopMode().height / 2) - 480);
    window.create(sf::VideoMode(WIDTH,HEIGHT), "QuestClock", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);

    sf::RectangleShape background;
    background.setSize({WIDTH, HEIGHT});
    background.setFillColor(sf::Color(230, 230, 230)); // GREY

    // font
    sf::Font CNR;
    CNR.loadFromFile("Courier New Regular.ttf"); // inside cmake-build-debug in CLion

    // all printed info on screen in the form of a button
    Button title("QuestClock", 75, sf::Color(64, 156, 120));
    title.setPosition({250, 100});
    title.setFont(CNR);
    Button username_txt("Username:", 20, sf::Color(64, 156, 120));
    username_txt.setPosition({50, 300});
    username_txt.setFont(CNR);
    Button password_txt("Password:", 20, sf::Color(64, 156, 120));
    password_txt.setPosition({50, 400});
    password_txt.setFont(CNR);

    // textboxes for login
    Textbox username_tbox(20, {300, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);
    Textbox password_tbox(20, {300, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);

    // Textbox password_tbox(15, sf::Color::White, true);
    username_tbox.setFont(CNR);
    username_tbox.setPosition({200, 300}); // FIXME: limits need fixing when it comes to deletion
    password_tbox.setFont(CNR);
    password_tbox.setPosition({200, 400});

    // login button
    Button login_btn("Login", {200, 50}, 30, sf::Color::Black, sf::Color::White);
    login_btn.setPosition({200, 500});
    login_btn.setFont(CNR);

    // Window loop
    while (window.isOpen()) {
        sf::Event event;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            username_tbox.setSelected(false);
            password_tbox.setSelected(false);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            if (username_tbox.isSelected()) {
                username_tbox.setSelected(false);
                password_tbox.setSelected(true);
            }
        }

        // event loop
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::TextEntered:
                    if (username_tbox.isSelected()) {
                        username_tbox.typeOn(event);
                    }
                    if (password_tbox.isSelected()) {
                        password_tbox.typeOn(event);
                    }
                    break;
                case sf::Event::MouseMoved:
                    if (login_btn.isMouseOver(window)) {
                        login_btn.setBackColor(sf::Color(64, 156, 120));
                        login_btn.setTextColor(sf::Color::White);
                    }
                    else {
                        login_btn.setBackColor(sf::Color::White);
                        login_btn.setTextColor(sf::Color::Black);
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    // click in username box
                    if (username_tbox.isMouseOver(window)) {
                        username_tbox.setSelected(true);
                        password_tbox.setSelected(false);
                    }
                    else {
                        username_tbox.setSelected(false);
                    }

                    // click in password box
                    if (password_tbox.isMouseOver(window)) {
                        password_tbox.setSelected(true);
                        username_tbox.setSelected(false);
                    }
                    else {
                        password_tbox.setSelected(false);
                    }

                    if (login_btn.isMouseOver(window)) {
                        std::cout << username_tbox.getText() << "\n" << password_tbox.getText() << std::endl;
                    }
                    break;
            }
        }
        window.clear();

        //draw to window
        window.draw(background);
        title.drawTo(window);
        username_txt.drawTo(window);
        password_txt.drawTo(window);
        username_tbox.drawTo(window);
        password_tbox.drawTo(window);
        login_btn.drawTo(window);
        window.display();
    }

    return 0;
}