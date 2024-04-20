#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"


class TimesWindow {
public:
    sf::Texture img;
    sf::Sprite back_btn;
    Button sign_out_btn;
    Button time_logs_txt;
    sf::RectangleShape time_bckgrnd;
    Button employee_txt;
    sf::RectangleShape employee_bckgrnd;
    Button alternate_btn;
    std::string alternate = "Company";
    Button specific_txt;
    sf::RectangleShape specific_bckgrnd;

    TimesWindow() { }
    TimesWindow(sf::Font& font) {
        img.loadFromFile("files/back.png"); // find it in a folder where you store images
        back_btn.setTexture(img);
        back_btn.setScale({0.15, 0.15});
        sign_out_btn = Button("Sign out", {90, 40}, 12, sf::Color::White, sf::Color::Black);
        sign_out_btn.setPosition({780, 30});
        sign_out_btn.setFont(font);
        time_logs_txt = Button("Timelogs:", 30, sf::Color(64, 156, 120));
        time_logs_txt.setPosition({250, 100});
        time_logs_txt.setFont(font);
        time_bckgrnd.setSize({600, 400});
        time_bckgrnd.setPosition({30, 150});
        time_bckgrnd.setFillColor(sf::Color(146, 176, 164));
        employee_txt = Button("Employees:", 20, sf::Color(64, 156, 120));
        employee_txt.setPosition({30, 590});
        employee_txt.setFont(font);
        employee_bckgrnd.setSize({400, 200});
        employee_bckgrnd.setPosition({30, 630});
        employee_bckgrnd.setFillColor(sf::Color(146, 176, 164));
        alternate_btn = Button(alternate + " Times", {350, 50}, 25, sf::Color::White, sf::Color::Black);
        alternate_btn.setPosition({500, 650});
        alternate_btn.setFont(font);
        specific_txt = Button("Specific Project:", 18, sf::Color(64, 156, 120));
        specific_txt.setPosition({660, 120});
        specific_txt.setFont(font);
        specific_bckgrnd.setSize({175, 400});
        specific_bckgrnd.setPosition({660, 150});
        specific_bckgrnd.setFillColor(sf::Color(146, 176, 164));
    }
    ~TimesWindow() { }

    void drawTo(sf::RenderWindow& window) {
        window.draw(time_bckgrnd);
        window.draw(employee_bckgrnd);
        window.draw(specific_bckgrnd);
        window.draw(back_btn);
        sign_out_btn.drawTo(window);
        time_logs_txt.drawTo(window);
        employee_txt.drawTo(window);
        alternate_btn.drawTo(window);
        specific_txt.drawTo(window);
    }

    bool isMouseOverBack(sf::RenderWindow& window) {
        float mouse_x = sf::Mouse::getPosition(window).x;
        float mouse_y = sf::Mouse::getPosition(window).y;

        float btn_pos_x = back_btn.getPosition().x;
        float btn_pos_y = back_btn.getPosition().y;

        float btn_xpos_width = back_btn.getLocalBounds().width * 0.15;
        float btn_xpos_height = back_btn.getLocalBounds().height * 0.15;

        if (mouse_x < btn_xpos_width && mouse_x > btn_pos_x && mouse_y < btn_xpos_height && mouse_y > btn_pos_y) {
            return true;
        }
        return false;
    }
};


void TimesWindowEvents(sf::RenderWindow& window, TimesWindow* timesWindow, bool& login_screen, bool& main_screen, bool& time_logs_screen, sf::Event& e) {
    // highlight buttons when hovered over
    if (e.type == sf::Event::MouseMoved) {
        if (timesWindow->sign_out_btn.isMouseOver(window)) {
            timesWindow->sign_out_btn.setBackColor(sf::Color(64, 156, 120));
            timesWindow->sign_out_btn.setTextColor(sf::Color::White);
        }
        else {
            timesWindow->sign_out_btn.setBackColor(sf::Color::White);
            timesWindow->sign_out_btn.setTextColor(sf::Color::Black);
        }
        if (timesWindow->alternate_btn.isMouseOver(window)) {
            timesWindow->alternate_btn.setBackColor(sf::Color(64, 156, 120));
            timesWindow->alternate_btn.setTextColor(sf::Color::White);
        }
        else {
            timesWindow->alternate_btn.setBackColor(sf::Color::White);
            timesWindow->alternate_btn.setTextColor(sf::Color::Black);
        }
    }

    // action on click for buttons
    if (e.type == sf::Event::MouseButtonPressed) {
        if (timesWindow->sign_out_btn.isMouseOver(window)) {
            std::cout << "-> Login Screen" << std::endl;
            login_screen = true;
            time_logs_screen = false;
        }
        if (timesWindow->isMouseOverBack(window)) {
            std::cout << "-> Main Screen" << std::endl;
            main_screen = true;
            time_logs_screen = false;
        }
    }
}
