#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"

class ProjectWindow {
public:
    sf::Texture back_img;
    sf::Sprite back_btn;
    Button sign_out_btn;
    Button proj_t_txt;
    Button proj_d_txt;
    sf::RectangleShape proj_bckgrnd;
    Button clockio_btn;
    Button time_txt;
    Button assign_user_btn;
    Button edit_btn;
    std::string proj_title = "TEST123";
    std::string proj_desc = "This is a test project.\nAssigned:\nAidan\nBrian\nAbigail\nAkeeb";

    ProjectWindow() { }
    ProjectWindow(sf::Font& font, std::string title, std::string description) {
        proj_title = title;
        proj_desc = description;

        back_img.loadFromFile("files/back.png"); // find it in a folder where you store images

        back_btn.setTexture(back_img);
        back_btn.setScale({0.15, 0.15});

        sign_out_btn = Button("Sign out", {90, 40}, 12, sf::Color::White, sf::Color::Black);
        sign_out_btn.setPosition({780, 30});
        sign_out_btn.setFont(font);

        proj_t_txt = Button("Project: " + proj_title, 30, sf::Color(64, 156, 120));
        proj_t_txt.setPosition({330, 110});
        proj_t_txt.setFont(font);

        proj_d_txt = Button(proj_desc, 20, sf::Color(64, 156, 120));
        proj_d_txt.setPosition({35, 160});
        proj_d_txt.setFont(font);

        proj_bckgrnd.setSize({800, 200});
        proj_bckgrnd.setPosition({30, 150});
        proj_bckgrnd.setFillColor(sf::Color(146, 176, 164));

        clockio_btn = Button("CLOCK-IN", {500, 100}, 50, sf::Color::White, sf::Color::Black);
        clockio_btn.setPosition({210, 400});
        clockio_btn.setFont(font);

        time_txt = Button("Time - 00:00:00", 40, sf::Color(64, 156, 120));
        time_txt.setPosition({280, 580});
        time_txt.setFont(font);

        assign_user_btn = Button("Assign User", {200, 40}, 20, sf::Color::White, sf::Color::Black);
        assign_user_btn.setPosition({220, 30});
        assign_user_btn.setFont(font);

        edit_btn = Button("Edit", {100, 40}, 20, sf::Color::White, sf::Color::Black);
        edit_btn.setPosition({480, 30});
        edit_btn.setFont(font);
    }
    ~ProjectWindow() { }

    void drawTo(sf::RenderWindow& window) {
        window.draw(proj_bckgrnd);
        window.draw(back_btn);
        sign_out_btn.drawTo(window);
        proj_t_txt.drawTo(window);
        proj_d_txt.drawTo(window);
        clockio_btn.drawTo(window);
        time_txt.drawTo(window);
        assign_user_btn.drawTo(window);
        edit_btn.drawTo(window);
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

void ProjectWindowEvents(sf::RenderWindow& window, ProjectWindow* projectWindow, bool& login_screen, bool& main_screen, bool& project_screen, sf::Event& e) {
    // highlight buttons when hovered over
    if (e.type == sf::Event::MouseMoved) {
        if (projectWindow->sign_out_btn.isMouseOver(window)) {
            projectWindow->sign_out_btn.setBackColor(sf::Color(64, 156, 120));
            projectWindow->sign_out_btn.setTextColor(sf::Color::White);
        }
        else {
            projectWindow->sign_out_btn.setBackColor(sf::Color::White);
            projectWindow->sign_out_btn.setTextColor(sf::Color::Black);
        }
        if (projectWindow->clockio_btn.isMouseOver(window)) {
            projectWindow->clockio_btn.setBackColor(sf::Color(64, 156, 120));
            projectWindow->clockio_btn.setTextColor(sf::Color::White);
        }
        else {
            projectWindow->clockio_btn.setBackColor(sf::Color::White);
            projectWindow->clockio_btn.setTextColor(sf::Color::Black);
        }
        if (projectWindow->assign_user_btn.isMouseOver(window)) {
            projectWindow->assign_user_btn.setBackColor(sf::Color(64, 156, 120));
            projectWindow->assign_user_btn.setTextColor(sf::Color::White);
        }
        else {
            projectWindow->assign_user_btn.setBackColor(sf::Color::White);
            projectWindow->assign_user_btn.setTextColor(sf::Color::Black);
        }
        if (projectWindow->edit_btn.isMouseOver(window)) {
            projectWindow->edit_btn.setBackColor(sf::Color(64, 156, 120));
            projectWindow->edit_btn.setTextColor(sf::Color::White);
        }
        else {
            projectWindow->edit_btn.setBackColor(sf::Color::White);
            projectWindow->edit_btn.setTextColor(sf::Color::Black);
        }
    }

    if (e.type == sf::Event::MouseButtonPressed) {
        if (projectWindow->sign_out_btn.isMouseOver(window)) {
            std::cout << "-> Login Screen" << std::endl;
            login_screen = true;
            project_screen = false;
        }
        if (projectWindow->clockio_btn.isMouseOver(window)) {
            if (projectWindow->clockio_btn.getText() == "CLOCK-IN") {
                projectWindow->clockio_btn.setText("CLOCK-OUT");
            }
            else {
                projectWindow->clockio_btn.setText("CLOCK-IN");
            }
        }
        if (projectWindow->assign_user_btn.isMouseOver(window)) {
            std::cout << "-> Assign User Pop-up" << std::endl;
            sf::RenderWindow assign_user_window(sf::VideoMode(400, 400), "Assign Users", sf::Style::Titlebar | sf::Style::Close);
            while (assign_user_window.isOpen()) {
                sf::Event event;
                while (assign_user_window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        assign_user_window.close();
                    }
                }
                assign_user_window.clear(sf::Color(230, 230, 230));
                assign_user_window.display();
            }
        }
        if (projectWindow->edit_btn.isMouseOver(window)) {
            std::cout << "-> Edit Project Pop-up" << std::endl;
            sf::RenderWindow edit_proj_window(sf::VideoMode(400, 400), "Edit Project", sf::Style::Titlebar | sf::Style::Close);
            while (edit_proj_window.isOpen()) {
                sf::Event event;
                while (edit_proj_window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        edit_proj_window.close();
                    }
                }
                edit_proj_window.clear(sf::Color(230, 230, 230));
                edit_proj_window.display();
            }
        }
        if (projectWindow->isMouseOverBack(window)) {
            std::cout << "-> Main Screen" << std::endl;
            main_screen = true;
            project_screen = false;
        }
    }

}