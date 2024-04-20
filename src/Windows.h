# pragma once
#include <iostream>
#include "UserAccount.h"
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"
#include "LoginWindow.h"

// inspired by https://youtu.be/T31MoLJws4U?si=_h8ujkH34nowKIoB

#define WIDTH 900 // window width
#define HEIGHT 900 // window height

void startWindows() {
    // LOGIN WINDOW setup
    bool login_screen = true;
    bool main_screen = false;

    // default info for the windows
    sf::RenderWindow window;
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445,
                              (sf::VideoMode::getDesktopMode().height / 2) - 480);
    window.create(sf::VideoMode(WIDTH,HEIGHT), "QuestClock", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);

    sf::RectangleShape background;
    background.setSize({WIDTH, HEIGHT});
    background.setFillColor(sf::Color(230, 230, 230)); // GREY

    // dif window screens
    sf::Font CNR;
    CNR.loadFromFile("Courier New Regular.ttf"); // inside cmake-build-debug in CLion

    // dif windows
    LoginWindow* loginWindow = new LoginWindow(CNR);

    Button test("QuestClock", 75, sf::Color(64, 156, 120));
    test.setPosition({250, 200});
    test.setFont(CNR);

    // Window loop
    while (window.isOpen()) {
        sf::Event e;

        // Keyboard Presses for each screen
        if (login_screen) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                loginWindow->username_tbox.setSelected(false);
                loginWindow->password_tbox.setSelected(false);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (loginWindow->username_tbox.isSelected()) {
                    loginWindow->username_tbox.setSelected(false);
                    loginWindow->password_tbox.setSelected(true);
                }
            }
        }

        // event loop for each screen
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
            if (login_screen) {
                LoginWindowEvents(window, loginWindow, login_screen, main_screen, e);
            }
            if (main_screen) {
                break;
            }
        }

        // displays for each screen

        if (login_screen) {
            if (loginWindow == nullptr) {
                loginWindow = new LoginWindow(CNR);
            }
            window.clear();
            window.draw(background);
            loginWindow->title.drawTo(window);
            loginWindow->username_txt.drawTo(window);
            loginWindow->password_txt.drawTo(window);
            loginWindow->username_tbox.drawTo(window);
            loginWindow->password_tbox.drawTo(window);
            loginWindow->login_btn.drawTo(window);
            window.display();
        }

        else if (main_screen) {
            if (loginWindow != nullptr) {
                delete loginWindow;
                loginWindow = nullptr;
            }
            window.clear();
            window.draw(background);
            test.drawTo(window);
            window.display();
        }
    }
}
