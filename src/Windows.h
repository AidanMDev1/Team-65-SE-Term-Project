# pragma once
#include <iostream>
#include <vector>
#include "UserAccount.h"
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"
#include "LoginWindow.h"
#include "MainWindow.h"
#include "TimesWindow.h"
#include "ProjectWindow.h"
#include "AchNotWindow.h"
#include "request.h"

// inspired by https://youtu.be/T31MoLJws4U?si=_h8ujkH34nowKIoB

#define WIDTH 900 // window width
#define HEIGHT 900 // window height

void startWindows() {
    request req;
    int proj_sel = -1;
    // WINDOW booleans
    bool signed_in = false;
    bool login_screen = true;
    bool main_screen = false;
    bool time_logs_screen = false;
    bool project_screen = false;
    bool ach_not_screen = false;

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
    CNR.loadFromFile("files/Courier New Regular.ttf"); // inside cmake-build-debug in CLion

    // dif windows
    LoginWindow* loginWindow = new LoginWindow(CNR, req);
    MainWindow* mainWindow = new MainWindow(CNR, req, signed_in, proj_sel);
    TimesWindow* timesWindow = new TimesWindow(CNR, req);
    ProjectWindow* projectWindow = new ProjectWindow(CNR, req, proj_sel);
    AchNotWindow* achNotWindow = new AchNotWindow(CNR, req);

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
                LoginWindowEvents(window, loginWindow, mainWindow, login_screen, main_screen, e, req);
            }
            if (main_screen) {
                if (!signed_in) //update main screen
                {
                    delete mainWindow;
                    signed_in = true;
                    mainWindow = new MainWindow(CNR, req, signed_in, proj_sel);
                }
                MainWindowEvents(window, mainWindow, projectWindow, login_screen, main_screen, time_logs_screen, project_screen, ach_not_screen, e, req, proj_sel);
            }
            if (time_logs_screen) {
                TimesWindowEvents(window, timesWindow, login_screen, main_screen, time_logs_screen, e, req);
            }
            if (project_screen) {
                ProjectWindowEvents(window, projectWindow, login_screen, main_screen, project_screen, e, req, proj_sel);
            }
            if (ach_not_screen) {
                AchNotWindowEvents(window, achNotWindow, login_screen, main_screen, ach_not_screen, e, req);
            }
        }

        // displays for each screen
        // FIXME might need to figure out a way to relieve the pointers and delete stuff
        if (login_screen) {
            if (loginWindow == nullptr) {
                loginWindow = new LoginWindow(CNR, req);
                signed_in = false;
            }
            window.clear();
            window.draw(background);
            loginWindow->drawTo(window);
            window.display();
        }
        else if (main_screen) {
            if (loginWindow != nullptr) { // resetting window information because of user sign out
                delete loginWindow;
                loginWindow = nullptr;
            }
            window.clear();
            window.draw(background);
            mainWindow->drawTo(window);
            window.display();
        }
        else if (time_logs_screen) {
            window.clear();
            window.draw(background);
            timesWindow->drawTo(window);
            window.display();
        }
        else if (project_screen) {
            window.clear();
            window.draw(background);
            projectWindow->drawTo(window);
            window.display();
        }
        else if (ach_not_screen) {
            window.clear();
            window.draw(background);
            achNotWindow->drawTo(window);
            window.display();
        }
    }
}