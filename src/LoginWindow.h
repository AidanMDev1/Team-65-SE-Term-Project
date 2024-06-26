#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"
#include "request.h"
#include "MainWindow.h"


class LoginWindow {
public:
    sf::Font f;
    Button title;
    Button username_txt;
    Button password_txt;
    Textbox username_tbox = Textbox(20, {300, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);
    Textbox password_tbox = Textbox(20, {300, 30}, sf::Color::Black, sf::Color(146, 176, 164), false);
    Button login_btn;

    LoginWindow() { }
    LoginWindow(sf::Font& font, request& req) {
        f = font;
        title = Button("QuestClock", 75, sf::Color(64, 156, 120));
        title.setPosition({250, 100});
        title.setFont(font);
        username_txt = Button("Username:", 20, sf::Color(64, 156, 120));
        username_txt.setPosition({50, 300});
        username_txt.setFont(font);
        password_txt = Button("Password:", 20, sf::Color(64, 156, 120));
        password_txt.setPosition({50, 400});
        password_txt.setFont(font);
        username_tbox.setFont(font);
        username_tbox.setPosition({200, 300}); // FIXME: limits need fixing when it comes to deletion
        password_tbox.setFont(font);
        password_tbox.setPosition({200, 400});
        login_btn = Button("Login", {200, 50}, 30, sf::Color::White, sf::Color::Black);
        login_btn.setPosition({200, 500});
        login_btn.setFont(font);
    }
    ~LoginWindow() { }

    void drawTo(sf::RenderWindow& window) {
        title.drawTo(window);
        username_txt.drawTo(window);
        password_txt.drawTo(window);
        username_tbox.drawTo(window);
        password_tbox.drawTo(window);
        login_btn.drawTo(window);
    }
};

//MainWindow*
void LoginWindowEvents(sf::RenderWindow& window, LoginWindow* loginWindow, MainWindow* mainWindow, bool& login_screen, bool& main_screen, sf::Event& e, request& req) {
    if (e.type == sf::Event::TextEntered) {
        if (loginWindow->username_tbox.isSelected()) {
            loginWindow->username_tbox.typeOn(e);
        }
        if (loginWindow->password_tbox.isSelected()) {
            loginWindow->password_tbox.typeOn(e);
        }
    }
    if (e.type == sf::Event::MouseMoved) {
        if (loginWindow->login_btn.isMouseOver(window)) {
            loginWindow->login_btn.setBackColor(sf::Color(64, 156, 120));
            loginWindow->login_btn.setTextColor(sf::Color::White);
        }
        else {
            loginWindow->login_btn.setBackColor(sf::Color::White);
            loginWindow->login_btn.setTextColor(sf::Color::Black);
        }
    }
    if (e.type == sf::Event::MouseButtonPressed) {
        // click in username box
        if (loginWindow->username_tbox.isMouseOver(window)) {
            loginWindow->username_tbox.setSelected(true);
            loginWindow->password_tbox.setSelected(false);
        }
        else {
            loginWindow->username_tbox.setSelected(false);
        }

        // click in password box
        if (loginWindow->password_tbox.isMouseOver(window)) {
            loginWindow->password_tbox.setSelected(true);
            loginWindow->username_tbox.setSelected(false);
        }
        else {
            loginWindow->password_tbox.setSelected(false);
        }

        if (loginWindow->login_btn.isMouseOver(window)) {
            bool check = false;
            string username = loginWindow->username_tbox.getText();
            string password = loginWindow->password_tbox.getText();

            if (!username.empty() && !password.empty()){
                check = req.login(username, password);
                if (check){
                    
                    std::cout << "login successful" << std::endl;   

                    bool check2 = false;
                    check2 = req.get_total_time(username);
                    if(!check2){  //user does not have a total time counter so create one for them
                        req.total_time_create(username);
                    }
                    main_screen = true;
                    login_screen = false;
                }
                else{
                    std::cout << "login unsuccessful" << std::endl;
                    login_screen = true;
                    main_screen = false;
                }
            }
            else{
                std::cout << "login unsuccessful" << std::endl;
                    login_screen = true;
                    main_screen = false;
            }
        }
    }
}