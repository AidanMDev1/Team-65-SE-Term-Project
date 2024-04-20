#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"


class MainWindow {
public:
    Button welcome_txt;
    Button sign_out_btn;
    Button projects_txt;
    sf::RectangleShape proj_bckgrnd;
    Button contact_btn;
    Button create_proj_btn;
    Button create_users_btn;
    Button achvmts_notif_btn;
    Button access_logs_btn;


    MainWindow() { }
    MainWindow(sf::Font& font) {
        welcome_txt = Button("WELCOME! Unlock Time's Potential with QuestClock!", 25, sf::Color(64, 156, 120));
        welcome_txt.setPosition({30, 30});
        welcome_txt.setFont(font);
        sign_out_btn = Button("Sign out", {90, 40}, 12, sf::Color::White, sf::Color::Black);
        sign_out_btn.setPosition({780, 30});
        sign_out_btn.setFont(font);
        projects_txt = Button("Project(s):", 20, sf::Color(64, 156, 120));
        projects_txt.setPosition({30, 110});
        projects_txt.setFont(font);
        proj_bckgrnd.setSize({800, 400});
        proj_bckgrnd.setPosition({30, 150});
        proj_bckgrnd.setFillColor(sf::Color(146, 176, 164));
        contact_btn = Button("Contact", {300, 50}, 25, sf::Color::White, sf::Color::Black);
        contact_btn.setPosition({30, 600});
        contact_btn.setFont(font);
        create_proj_btn = Button("Create Project", {300, 50}, 25, sf::Color::White, sf::Color::Black);
        create_proj_btn.setPosition({30, 670});
        create_proj_btn.setFont(font);
        create_users_btn = Button("Create User", {300, 50}, 25, sf::Color::White, sf::Color::Black);
        create_users_btn.setPosition({30, 750});
        create_users_btn.setFont(font);
        achvmts_notif_btn = Button("Achievments/\nNotifications", {300, 100}, 25, sf::Color::White, sf::Color::Black);
        achvmts_notif_btn.setPosition({550, 600});
        achvmts_notif_btn.setFont(font);
        access_logs_btn = Button("Access Timelogs", {350, 50}, 25, sf::Color::White, sf::Color::Black);
        access_logs_btn.setPosition({500, 720});
        access_logs_btn.setFont(font);
    }
    ~MainWindow() { }

    void drawTo(sf::RenderWindow& window) {
        window.draw(proj_bckgrnd);
        welcome_txt.drawTo(window);
        sign_out_btn.drawTo(window);
        projects_txt.drawTo(window);
        contact_btn.drawTo(window);
        create_proj_btn.drawTo(window);
        create_users_btn.drawTo(window);
        achvmts_notif_btn.drawTo(window);
        access_logs_btn.drawTo(window);
    }
};

void MainWindowEvents(sf::RenderWindow& window, MainWindow* mainWindow, bool& login_screen, bool& main_screen, bool& time_logs_screen, sf::Event& e) {
    // highlight buttons when hovered over
    if (e.type == sf::Event::MouseMoved) {
        if (mainWindow->sign_out_btn.isMouseOver(window)) {
            mainWindow->sign_out_btn.setBackColor(sf::Color(64, 156, 120));
            mainWindow->sign_out_btn.setTextColor(sf::Color::White);
        }
        else {
            mainWindow->sign_out_btn.setBackColor(sf::Color::White);
            mainWindow->sign_out_btn.setTextColor(sf::Color::Black);
        }
        if (mainWindow->contact_btn.isMouseOver(window)) {
            mainWindow->contact_btn.setBackColor(sf::Color(64, 156, 120));
            mainWindow->contact_btn.setTextColor(sf::Color::White);
        }
        else {
            mainWindow->contact_btn.setBackColor(sf::Color::White);
            mainWindow->contact_btn.setTextColor(sf::Color::Black);
        }
        if (mainWindow->create_proj_btn.isMouseOver(window)) {
            mainWindow->create_proj_btn.setBackColor(sf::Color(64, 156, 120));
            mainWindow->create_proj_btn.setTextColor(sf::Color::White);
        }
        else {
            mainWindow->create_proj_btn.setBackColor(sf::Color::White);
            mainWindow->create_proj_btn.setTextColor(sf::Color::Black);
        }
        if (mainWindow->create_users_btn.isMouseOver(window)) {
            mainWindow->create_users_btn.setBackColor(sf::Color(64, 156, 120));
            mainWindow->create_users_btn.setTextColor(sf::Color::White);
        }
        else {
            mainWindow->create_users_btn.setBackColor(sf::Color::White);
            mainWindow->create_users_btn.setTextColor(sf::Color::Black);
        }
        if (mainWindow->achvmts_notif_btn.isMouseOver(window)) {
            mainWindow->achvmts_notif_btn.setBackColor(sf::Color(64, 156, 120));
            mainWindow->achvmts_notif_btn.setTextColor(sf::Color::White);
        }
        else {
            mainWindow->achvmts_notif_btn.setBackColor(sf::Color::White);
            mainWindow->achvmts_notif_btn.setTextColor(sf::Color::Black);
        }
        if (mainWindow->access_logs_btn.isMouseOver(window)) {
            mainWindow->access_logs_btn.setBackColor(sf::Color(64, 156, 120));
            mainWindow->access_logs_btn.setTextColor(sf::Color::White);
        }
        else {
            mainWindow->access_logs_btn.setBackColor(sf::Color::White);
            mainWindow->access_logs_btn.setTextColor(sf::Color::Black);
        }
    }

    // action on click for buttons
    if (e.type == sf::Event::MouseButtonPressed) {
        if (mainWindow->sign_out_btn.isMouseOver(window)) {
            std::cout << "back to sign in" << std::endl;
            login_screen = true;
            main_screen = false;
        }
        if (mainWindow->access_logs_btn.isMouseOver(window)) {
            std::cout << "Timelog time" << std::endl;
            time_logs_screen = true;
            main_screen = false;
        }
    }
}